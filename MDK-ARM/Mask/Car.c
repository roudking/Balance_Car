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
   .kp = 1200.0 * 0.6,
//    .ki = 0.0,
   .kd = -72.0 * 0.6,  //敏感型数据
};

//TODO: 调试速度PID
//不敏感数据
const double p = 850.0;
PID pidspeed = 
{
    .kp = p,
    .ki = p/200.0,
    .kd = 0.0,
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
    car->speed_pid.integral += target; //更新积分
}

//死区处理
int dead_zone_comp(int pwm, int dz){
    if (abs(pwm) < dz) return 0;
    // 衔接平滑：减去死区大小
    return pwm > 0 ? pwm - dz : pwm + dz;
}

int Balance_PD(CAR *car) {
     static float last_pitch = 0.0,last_gx = 0.0; //上次角度
    
    float pitch_filter = 0.85; //滤波系数
    float current_pitch = car->mpu.pitch;
    current_pitch = pitch_filter * current_pitch + (1 - pitch_filter) * last_pitch; //滤波公式
    last_pitch = current_pitch; //更新上次角度

    float gx_filter = 0.75; //滤波系数
    float current_gx = car->mpu.mpu_data.gx;
    current_gx = gx_filter * current_gx + (1 - gx_filter) * last_gx; //滤波公式
    last_gx = current_gx; //更新上次角度

    return (int)position_divAPI_PID_Cal(car->target_angle, current_pitch, current_gx, &(car->balance_pid));
}

int Speed_PI(CAR *car) {
    //对输入速度进行低通滤波
     static float last_speed = 0.0; //上次速度
     float alpha = 0.80; //滤波系数
      float current_speed = (car->motor1.currentspeed + car->motor2.currentspeed) / 2.0; //平均速度
     current_speed = alpha * current_speed + (1 - alpha) * last_speed; //滤波公式
     last_speed = current_speed; //更新上次速度   
    //速度PID
    return positionPid_Cal(0.0, current_speed, &car->speed_pid);
}

void Car_balance(CAR *car) {
    int balance_pwm,speed_pwm,total_pwm;
    //保护
    if(car->mpu.pitch > -35.0 && car->mpu.pitch < 35.0) {
    //平衡PID
    balance_pwm = -Balance_PD(car);
    //速度PID
    speed_pwm = -Speed_PI(car);

    } else {
        balance_pwm = 0;
        speed_pwm = 0;
        total_pwm = 0;
        pidmemory_clear(&(car->balance_pid)); //清除平衡PID的积分
        pidmemory_clear(&(car->speed_pid)); //清除速度PID的积分
    }
   
    total_pwm = balance_pwm + speed_pwm; //总PWM

     //TODO: 删除死区		
    total_pwm = dead_zone_comp(total_pwm,400); 

    total_pwm = xianfu(total_pwm, -7200, 7200); // 限幅



    //电机控制
    Driver_setmotorpwm(&(car->motor1), total_pwm,&(car->motor2), total_pwm);
}