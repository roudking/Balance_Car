#include "pwm.h"

void pwm_init(TIM_HandleTypeDef* tim,uint32_t TIM_CHANNEL)
{
  HAL_TIM_PWM_Start(tim, TIM_CHANNEL);
}

void pwm_set(TIM_HandleTypeDef* tim,uint32_t TIM_CHANNEL,uint32_t pwm)
{
   __HAL_TIM_SET_COMPARE(tim, TIM_CHANNEL, pwm);
}

