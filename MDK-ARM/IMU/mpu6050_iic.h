#ifndef _MPU6050_IIC_H
#define _MPU6050_IIC_H

#include "mpu6050_config.h"

void mpu_iicsend(MPU_CONFIG config ,uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
void mpu_iicgetdata(MPU_CONFIG config ,uint16_t MemAddSize, uint8_t *pData, uint16_t Size);  //����DLFPΪ0�ӳ٣�ͬʱ�����������Ϊ8Khz

#endif
