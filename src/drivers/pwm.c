#include "drivers/pwm.h"

#include <avr/io.h>

void pwm_init(void)
{
    DDRB |= (1U << PB1); // OC1A output

    TCCR1A = (1U << COM1A1) | (1U << WGM10); // Fast PWM 8-bit
    TCCR1B = (1U << WGM12) | (1U << CS11);   // prescaler 8

    OCR1A = 0U;
}

void pwm_set_duty(uint8_t duty)
{
    OCR1A = duty;
}
