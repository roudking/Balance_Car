#ifndef _DRIVER_H
#define _DRIVER_H

#include "Driver_Encoder.h"
#include "Driver_pwm.h"
#include "pid.h"
#include "stdlib.h"

extern PID pidL;
extern PID pidR;


typedef struct
{
	DRIVER_CONFIG config;
	int targetspeed;
	int currentspeed;
	int flitspeed;
	int lastspeed;
	PID pid;

}MOTOR;

void Driver_creatmotor(MOTOR *mymotor,PID pid,DRIVER_CONFIG driver);

void Driver_init(MOTOR *motor);

void Driver_setmotor_targetspeed(MOTOR *motor,int target_speed);

void Driver_getmotor_currentspeed(MOTOR *motor);

void Driver_setmotorpwm(MOTOR *motor1,int pwm1, MOTOR *motor2,int pwm2);

void Driver_setspeed(MOTOR *motor1,MOTOR *motor2);

void Driver_setspeedwithfliter(MOTOR *motor1,MOTOR *motor2);



#endif
