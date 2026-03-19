#ifndef APP_CONTROL_H
#define APP_CONTROL_H

#include <stdint.h>

void app_control_init(void);
void app_control_update(void);
uint16_t app_get_last_temp_c(void);
uint8_t app_get_last_duty(void);

#endif
