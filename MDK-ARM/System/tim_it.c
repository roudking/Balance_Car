#include "tim_it.h"

// 为每个外设实例注册回调
static TIM_Callback TIM1_Callback = NULL;
static TIM_Callback TIM2_Callback = NULL;
static TIM_Callback TIM3_Callback = NULL;
static TIM_Callback TIM4_Callback = NULL;
static TIM_Callback TIM5_Callback = NULL;
static TIM_Callback TIM6_Callback = NULL;
static TIM_Callback TIM7_Callback = NULL;

//使能中断
void tim_it_start(TIM_HandleTypeDef *htim)
{
	HAL_TIM_Base_Start_IT(htim);
}

// 在初始化时注册不同的回调函数
void tim_callbackregister(TIM_HandleTypeDef *htim,TIM_Callback callback_function) {
	if(htim->Instance == TIM7)
	{
     TIM7_Callback = callback_function;
	}
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM7 && TIM7_Callback) {
        TIM7_Callback();
    }
}
