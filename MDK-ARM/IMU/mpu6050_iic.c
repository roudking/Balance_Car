#include "mpu6050_iic.h"

void mpu_iicsend(MPU_CONFIG config ,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
   iic_mem_write8Bit(config.IIC_Port,config.ADDR,MemAddSize,pData,Size);
}

void mpu_iicgetdata(MPU_CONFIG config ,uint16_t MemAddSize, uint8_t *pData, uint16_t Size)
{
   iic_mem_read8Bit(config.IIC_Port,config.ADDR,MemAddSize,pData,Size);
}

