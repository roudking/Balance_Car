#include "Car.h"


//已整定pid
PID pidL =
{
//    .kp = 200.0,
//    .ki = 21.0,
//    .kd = 0.0,
//	  .out_xianfu = 7200.0
};

PID pidR =
{
//    .kp = 200.0,
//    .ki = 21.0,
//    .kd = 0.0,
//	  .out_xianfu = 7200.0
};


//重新调试
PID pidbalance = 
{
   .kp = 2300.0 * 0.6,
   .ki = 0.0,
   .kd = -280.0 * 0.6,  //敏感型数据
   .out_xianfu = 7200.0
};

//不敏感数据
PID pidspeed = 
{
    .kp = 3500.0,
    .ki = 17.5,
    .kd = 0.0,
	  .integrate_xianfu = 2000.0,
	   .out_xianfu = 7200.0
};


void Car_setBalancePID(CAR *car, PID pid) {
    car->balance_pid = pid;
}

void Car_setSpeedPID(CAR *car, PID pid) {
    car->speed_pid = pid;
}

void Car_setBalanceAngle(CAR *car, float angle) {
    car->target_angle = angle;
}

void Car_setSpeedTarget(CAR *car, float target) {
    car->target_speed = target;
}

//死区处理
int dead_zone(float value, float deadzone,float dead_value) {
    if(value > deadzone)  return value + dead_value;
    else if(value < -deadzone)  return value - dead_value;
    else return 0;
}

int Balance_PD(CAR *car) {
    return (int)position_divAPI_PID_Cal(car->target_angle, car->mpu.pitch, car->mpu.mpu_data.gx, &(car->balance_pid));
}   

int Speed_PI(CAR *car) {
    //对输入速度进行低通滤波
     static float last_speed = 0.0; //上次速度
     float alpha = 0.85; //滤波系数
      float current_speed = (car->motor1.currentspeed + car->motor2.currentspeed) / 2.0; //平均速度
     current_speed = alpha * car->motor1.currentspeed + (1 - alpha) * last_speed; //滤波公式
     last_speed = current_speed; //更新上次速度   
    //速度PID
    return positionPid_Cal(car->target_speed, current_speed, &car->speed_pid);
}

void Car_balance(CAR *car) {
    int balance_pwm,speed_pwm,total_pwm;
    //保护
    if(car->mpu.pitch > -35.0 && car->mpu.pitch < 35.0) {
    //平衡PID
    balance_pwm = -Balance_PD(car);
    //速度PID
    speed_pwm = -Speed_PI(car);

     //死区处理
    // total_pwm = dead_zone(total_pwm,300,300);

    } else {
        balance_pwm = 0;
        speed_pwm = 0;
        total_pwm = 0;
        pidmemory_clear(&(car->balance_pid)); //清除平衡PID的积分
        pidmemory_clear(&(car->speed_pid)); //清除速度PID的积分
    }
   


    total_pwm = balance_pwm + speed_pwm; //总PWM
    total_pwm = xianfu(total_pwm, -7200, 7200); // 限幅

    //电机控制
    Driver_setmotorpwm(&(car->motor1), total_pwm,&(car->motor2), total_pwm);
}