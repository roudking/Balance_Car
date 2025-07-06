#ifndef _ENCODER_H
#define _ENCODER_H

#include "tim.h"

void encoder_init(TIM_HandleTypeDef* tim);
int16_t encoder_getcounter(TIM_HandleTypeDef* tim);

#endif 
