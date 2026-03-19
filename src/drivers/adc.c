#include "drivers/adc.h"

#include <avr/io.h>

void adc_init(void)
{
    ADMUX = (1U << REFS0); // AVcc reference
    ADCSRA = (1U << ADEN)  // ADC enable
           | (1U << ADPS2) | (1U << ADPS1) | (1U << ADPS0); // 128 prescaler
}

uint16_t adc_read(uint8_t channel)
{
    channel &= 0x0FU;
    ADMUX = (ADMUX & 0xF0U) | channel;

    ADCSRA |= (1U << ADSC);
    while (ADCSRA & (1U << ADSC)) {
    }

    return ADC;
}
