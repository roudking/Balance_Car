#ifndef _GPIO_IT_H
#define _GPIO_IT_H

#include "gpio.h"

typedef void (*EXTI_Callback)(void);

void exti_register_callback(uint16_t GPIO_Pin, EXTI_Callback callback_function);

#endif