#include "drivers/uart.h"

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

static uint16_t uart_calc_ubrr(uint32_t baud)
{
    return (uint16_t)((F_CPU / 16UL / baud) - 1UL);
}

void uart_init(uint32_t baud)
{
    uint16_t ubrr = uart_calc_ubrr(baud);
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    UCSR0B = (1U << TXEN0);
    UCSR0C = (1U << UCSZ01) | (1U << UCSZ00); // 8N1
}

void uart_write_char(char c)
{
    while (!(UCSR0A & (1U << UDRE0))) {
    }
    UDR0 = (uint8_t)c;
}

void uart_write_str(const char *s)
{
    while (*s != '\0') {
        uart_write_char(*s++);
    }
}

void uart_write_u16(uint16_t value)
{
    char buf[6];
    uint8_t i = 0;

    if (value == 0U) {
        uart_write_char('0');
        return;
    }

    while (value > 0U && i < sizeof(buf)) {
        buf[i++] = (char)('0' + (value % 10U));
        value /= 10U;
    }

    while (i > 0U) {
        uart_write_char(buf[--i]);
    }
}
