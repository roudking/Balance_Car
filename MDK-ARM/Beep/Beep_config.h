#ifndef _BEEP_CONFIG_H
#define _BEEP_CONFIG_H

#include "my_gpio.h"

typedef struct {
    GPIO_TypeDef *gpio_port;  // GPIO port for the beep
    uint16_t gpio_pin;        // GPIO pin for the beep
} BEEP_CONFIG;

extern BEEP_CONFIG beep_config;

#endif
