#include "app/control.h"

#include "config.h"
#include "drivers/adc.h"
#include "drivers/pwm.h"

#include <avr/io.h>
#include <util/delay.h>

static uint16_t g_last_temp_c = 0U;
static uint8_t g_last_duty = 0U;
static uint8_t g_force_max_mode = 0U;

static uint16_t adc_to_temp_c(uint16_t adc)
{
    // LM35: 10mV/¡ÆC, ADC reference 5V, 10-bit ADC
    // Temp = (adc * 500) / 1023
    return (uint16_t)((adc * 500UL) / 1023UL);
}

static uint8_t temp_to_duty(uint16_t temp_c)
{
    if (temp_c <= TEMP_LOW_C) {
        return FAN_PWM_MIN_DUTY;
    }
    if (temp_c >= TEMP_HIGH_C) {
        return FAN_PWM_MAX_DUTY;
    }

    uint16_t span_temp = (uint16_t)(TEMP_HIGH_C - TEMP_LOW_C);
    uint16_t offset = (uint16_t)(temp_c - TEMP_LOW_C);
    uint16_t span_duty = (uint16_t)(FAN_PWM_MAX_DUTY - FAN_PWM_MIN_DUTY);

    return (uint8_t)(FAN_PWM_MIN_DUTY + ((offset * span_duty) / span_temp));
}

static void button_init(void)
{
    BUTTON_DDR &= (uint8_t)~(1U << BUTTON_PIN);
    BUTTON_PORT |= (1U << BUTTON_PIN); // pull-up
}

static uint8_t button_pressed(void)
{
    if (!(BUTTON_PIN_REG & (1U << BUTTON_PIN))) {
        _delay_ms(20);
        if (!(BUTTON_PIN_REG & (1U << BUTTON_PIN))) {
            while (!(BUTTON_PIN_REG & (1U << BUTTON_PIN))) {
            }
            return 1U;
        }
    }
    return 0U;
}

void app_control_init(void)
{
    button_init();

    STATUS_LED_DDR |= (1U << STATUS_LED_PIN);
    STATUS_LED_PORT &= (uint8_t)~(1U << STATUS_LED_PIN);

    g_last_temp_c = 0U;
    g_last_duty = 0U;
    g_force_max_mode = 0U;
}

void app_control_update(void)
{
    uint16_t adc = adc_read(TEMP_ADC_CHANNEL);
    g_last_temp_c = adc_to_temp_c(adc);

    if (button_pressed()) {
        g_force_max_mode ^= 1U;
    }

    if (g_force_max_mode) {
        g_last_duty = FAN_PWM_MAX_DUTY;
        STATUS_LED_PORT |= (1U << STATUS_LED_PIN);
    } else {
        g_last_duty = temp_to_duty(g_last_temp_c);
        STATUS_LED_PORT &= (uint8_t)~(1U << STATUS_LED_PIN);
    }

    pwm_set_duty(g_last_duty);
}

uint16_t app_get_last_temp_c(void)
{
    return g_last_temp_c;
}

uint8_t app_get_last_duty(void)
{
    return g_last_duty;
}
