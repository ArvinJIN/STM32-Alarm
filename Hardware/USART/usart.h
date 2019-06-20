#ifndef __USART_H
#define __USART_H
#include "define.h"
#include "stdio.h"

	  	

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 pclk2,u32 bound);

void USART_PutChar(USART_TypeDef *USARTx, uint8_t Data);
void USART_SendStr(USART_TypeDef *USARTx, uint8_t *str);

#endif	   

