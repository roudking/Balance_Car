#ifndef _IIC_H
#define _IIC_H

#include "i2c.h"

void iic_send(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);  
void iic_receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);

//八位帧数据
void iic_mem_write8Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);
void iic_mem_read8Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);
//十六位帧数据
void iic_mem_write16Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);
void iic_mem_read16Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);


#endif
