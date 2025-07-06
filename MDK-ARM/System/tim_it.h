#ifndef _TIM_IT_H
#define _TIM_IT_H

#include "tim.h"

typedef void (*TIM_Callback)(void);

void tim_it_start(TIM_HandleTypeDef *htim);
void tim_callbackregister(TIM_HandleTypeDef *htim,TIM_Callback callback_function);


#endif
