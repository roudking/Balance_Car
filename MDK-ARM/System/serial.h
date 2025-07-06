#ifndef _SERIAL_H
#define _SERIAL_H

#include "usart.h"
#include "string.h"
#include "stdarg.h"
#include "stdio.h"


// 在某个公共头文件里（或 Debugger_printf 前面）加上：
#define Debugger_UART huart2
#define Debugger_printf(fmt, ...)  usart_printf(&Debugger_UART, fmt, ##__VA_ARGS__)



typedef void (*UART_Callback)(void);

void usart_printf(UART_HandleTypeDef *huart,char *fmt, ...);
void usart_rx_it_start(UART_HandleTypeDef *huart,uint8_t *pData);
void usart_rx_it_stop(UART_HandleTypeDef *huart);
void usart_transmit(UART_HandleTypeDef *huart,unsigned char *p_data, unsigned int uiSize);
void usart_callbackregister(UART_HandleTypeDef *huart,UART_Callback callback_function);


#endif
