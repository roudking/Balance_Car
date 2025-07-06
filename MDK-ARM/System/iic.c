#include "iic.h"

void iic_send(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  HAL_I2C_Master_Transmit(hi2c,DevAddress,pData,Size,HAL_MAX_DELAY);
}                  

void iic_receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size)
{
  HAL_I2C_Master_Receive(hi2c,DevAddress,pData,Size,HAL_MAX_DELAY);
}

//八位帧数据
void iic_mem_write8Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
    HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

void iic_mem_read8Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
    HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress, I2C_MEMADD_SIZE_8BIT, pData, Size, HAL_MAX_DELAY);
}

//十六位帧数据
void iic_mem_write16Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
    HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pData, Size, HAL_MAX_DELAY);
}

void iic_mem_read16Bit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size)
{
    HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pData, Size, HAL_MAX_DELAY);
}