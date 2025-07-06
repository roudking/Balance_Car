#ifndef _MPU6050_H
#define _MPU6050_H

#include "mpu6050_iic.h"
#include "serial.h"
#include "my_delay.h"
#include "arm_math.h"

typedef struct
{
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x,  gyro_y,  gyro_z;
}MPU_RAW;

typedef struct
{
    float ax, ay, az;     // ��λ��g
    float gx, gy, gz;     // ��λ����/s
}MPU_DATA;

typedef struct {
    float Q_angle;
    float Q_bias;
    float R_measure;
    float angle;
    float bias;
    float P[2][2];
} KALMAN;

typedef struct
{
		 MPU_CONFIG config;
		 KALMAN kalmanx;
	   KALMAN kalmany;
	
     MPU_DATA mpu_data;
	   MPU_RAW  mpu_raw;
	   float pitch;
     float roll;
}MPU;

int Mpu_test_who_am_i(MPU *mpu);

void Mpu_creat(MPU *mpu,MPU_CONFIG config_struct,KALMAN Kalmanx,KALMAN Kalmany);
void Mpu_init(MPU *mpu);
uint8_t Mpu_clearinterrupt(MPU *mpu);
void Mpu_getdata(MPU *mpu);
void Mpu_getKalmandata(MPU *mpu);

extern KALMAN KalmanX;
extern KALMAN KalmanY;

#endif
