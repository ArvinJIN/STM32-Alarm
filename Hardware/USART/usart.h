#ifndef __USART_H
#define __USART_H
#include "define.h"
#include "stdio.h"

	  	

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 pclk2,u32 bound);

void USART_PutChar(USART_TypeDef *USARTx, uint8_t Data);
void USART_SendStr(USART_TypeDef *USARTx, uint8_t *str);

#endif	   

