#include "my_gpio.h"

int gpio_readpin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if(HAL_GPIO_ReadPin(GPIOx,GPIO_Pin) == GPIO_PIN_SET)
	{
	  return 1;
	}
	else
	{
		return 0;
	} 
	
}

void gpio_setpin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_SET);
}

void gpio_resetpin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  HAL_GPIO_WritePin(GPIOx,GPIO_Pin,GPIO_PIN_RESET);
}

