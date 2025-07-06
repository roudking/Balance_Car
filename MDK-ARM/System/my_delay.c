#include "my_delay.h"

void delay_us(uint32_t i)
{
	uint16_t differ = 0xffff- i - 5;//65535-5-i��������ֵ���������������65535�պü���us�Σ�
									//Ҳ��ʵ����n us��ʱ

	__HAL_TIM_SET_COUNTER(&DELAY_TIMER, differ);	//���ü���ֵ

	HAL_TIM_Base_Start(&DELAY_TIMER);	//������ʱ��

	while(differ < 0xffff-6)
	{
		differ = __HAL_TIM_GET_COUNTER(&DELAY_TIMER); //��ȡ��ǰ����ֵ
	}

	HAL_TIM_Base_Stop(&DELAY_TIMER);//ֹͣ��ʱ��
}

void delay_ms(uint32_t nms)
{
    for (uint32_t i = 0; i < nms; i++) {
        delay_us(1000);  // ��ʱ 1 ms
    }
}
