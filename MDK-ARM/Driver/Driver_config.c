#include "Driver_config.h"

DRIVER_CONFIG leftdriver = {
	.Encoder_PORT = &LeftDriver_Encoder_Timer,

	.DriverPWM_PORT = &LeftDriver_Timer,
	.DriverPWMTimer_autoreload = LeftDriver_Timer_autoreload,
	.Channel[0] = LeftDriver_TIM_channel_1,
	.Channel[1] = LeftDriver_TIM_channel_2,
	.Encoder_polarity = 1,
	.Pwm_polarity = 1

};

DRIVER_CONFIG rightdriver = {
	.Encoder_PORT = &RightDriver_Encoder_Timer,

	.DriverPWM_PORT = &RightDriver_Timer,
	.DriverPWMTimer_autoreload = RightDriver_Timer_autoreload,
	.Channel[0] = RightDriver_TIM_channel_1,
	.Channel[1] = RightDriver_TIM_channel_2,
	.Encoder_polarity = 0,
	.Pwm_polarity = 0
};