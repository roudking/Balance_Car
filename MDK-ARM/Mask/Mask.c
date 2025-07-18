#include "Mask.h"

static void Mask_EXTIcallback(void);

CAR car;
const float machine_zerovalue = 1.0;

void Mask_start(void) {
    //电机初始化
    Driver_creatmotor(&(car.motor1), pidL, leftdriver);
    Driver_creatmotor(&(car.motor2), pidR, rightdriver);
    Driver_init(&(car.motor1));
    Driver_init(&(car.motor2));
	
    //mpu6050初始化
    Mpu_creat(&(car.mpu),mpu_config,KalmanX,KalmanY);
	  Mpu_init(&(car.mpu));

    //设置平衡角度
    Car_setBalanceAngle(&car, machine_zerovalue);
    //设置速度目标
    Car_setSpeedTarget(&car, 0.0);

    //设置平衡PID
    Car_setBalancePID(&car, pidbalance);

    //设置速度PID
    Car_setSpeedPID(&car, pidspeed);

    //注册任务回调函数
    exti_register_callback(MASK_EXTI_PIN, Mask_EXTIcallback);

}

static void Mask_EXTIcallback(void) {
	

    //获取电机转速
    Driver_getmotor_currentspeed(&(car.motor1));
    Driver_getmotor_currentspeed(&(car.motor2));

    //获取各种角度
     Mpu_getKalmandata(&(car.mpu));
	
    //平衡控制
    Car_balance(&car);

    //清除MPU中断标志位
    Mpu_clearinterrupt(&(car.mpu));	

}


      //调试信息输出
//	  Debugger_printf("left:%.3f,%d,%d\n", car.mpu.pitch,car.motor1.currentspeed,car.motor2.currentspeed);	
//    Debugger_printf("gx: %.3f\n", car.mpu.mpu_data.gx);
//	  Debugger_printf("pitch:%.3f\n", car.mpu.pitch);
//    Debugger_printf("%.3f,%.3f\n", car.balance_pid.outvalue,car.speed_pid.outvalue);

