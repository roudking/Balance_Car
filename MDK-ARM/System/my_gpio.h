#ifndef _MY_GPIO_H
#define _MY_GPIO_H

#include "gpio.h"

int gpio_readpin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void gpio_resetpin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void gpio_setpin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif