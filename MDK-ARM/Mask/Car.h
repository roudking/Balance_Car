#ifndef CAR_H
#define CAR_H

#include "Driver.h"
#include "mpu6050.h"
#include "serial.h"

typedef struct
{
    MOTOR motor1;
    MOTOR motor2;
	MPU mpu;

    PID balance_pid;
    PID speed_pid;
        
    float target_angle;
    float target_speed;

}CAR;

extern PID pidbalance, pidspeed, pidL, pidR;


void Car_setBalancePID(CAR *car, PID pid);
void Car_setSpeedPID(CAR *car, PID pid);
void Car_setBalanceAngle(CAR *car, float angle);
void Car_setSpeedTarget(CAR *car, float target);

void Car_balance(CAR *car);


#endif