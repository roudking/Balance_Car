#ifndef _PWM_H
#define _PWM_H

#include "tim.h"

void pwm_init(TIM_HandleTypeDef* tim,uint32_t TIM_CHANNEL);
void pwm_set(TIM_HandleTypeDef* tim,uint32_t TIM_CHANNEL,uint32_t pwm);

#endif
