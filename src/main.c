#include "app/control.h"
#include "drivers/adc.h"
#include "drivers/pwm.h"
#include "drivers/uart.h"

#include <util/delay.h>

#ifndef BAUD
#define BAUD 9600UL
#endif

static void log_status(void)
{
    uart_write_str("TEMP=");
    uart_write_u16(app_get_last_temp_c());
    uart_write_str("C, DUTY=");
    uart_write_u16(app_get_last_duty());
    uart_write_str("/255\r\n");
}

int main(void)
{
    adc_init();
    pwm_init();
    uart_init(BAUD);
    app_control_init();

    uart_write_str("Smart Cooling Controller Start\r\n");

    while (1) {
        app_control_update();
        log_status();
        _delay_ms(500);
    }
}
