#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(uint32_t baud);
void uart_write_char(char c);
void uart_write_str(const char *s);
void uart_write_u16(uint16_t value);

#endif
