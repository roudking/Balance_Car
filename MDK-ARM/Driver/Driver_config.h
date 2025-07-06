#ifndef _DRIVER_CONFIG
#define _DRIVER_CONFIG

#include "encoder.h"
#include "pwm.h"

typedef struct {
	int DriverPWMTimer_autoreload;
	TIM_HandleTypeDef *Encoder_PORT;
	TIM_HandleTypeDef *DriverPWM_PORT;
	int Channel[2];
	int Encoder_polarity;
	int Pwm_polarity;
} DRIVER_CONFIG;

extern DRIVER_CONFIG leftdriver;
extern DRIVER_CONFIG rightdriver;

//电机编码器设置
#define LeftDriver_Encoder_Timer  htim3
#define RightDriver_Encoder_Timer htim4

//电机PWM端口设置
#define LeftDriver_Timer htim8
#define LeftDriver_TIM_channel_1 TIM_CHANNEL_1
#define LeftDriver_TIM_channel_2 TIM_CHANNEL_2

#define RightDriver_Timer htim8
#define RightDriver_TIM_channel_1 TIM_CHANNEL_3
#define RightDriver_TIM_channel_2 TIM_CHANNEL_4


#define LeftDriver_Timer_autoreload 7200
#define RightDriver_Timer_autoreload 7200

#endif
