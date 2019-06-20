#include "usart.h"	  


//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率 
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//计算USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; //得到USARTDIV
	
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟，IO端口A时钟开启
	RCC->APB2ENR|=1<<14;  //使能串口时钟，USART1时钟使能
	
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置，GPIO端口输入输出模式设置 
	
	RCC->APB2RSTR|=1<<14;   //复位USART1
	RCC->APB2RSTR&=~(1<<14);//停止复位	 
	
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //USART模块使能，使能发送，使能接收
	//使能接收中断 
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能。	    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
	
}


void USART_PutChar(USART_TypeDef *USARTx, uint8_t Data){
	//数据寄存器，DR[8:0]：数据值 (Data value) 
	USARTx->DR = (Data & (uint16_t)0x01FF);
  while((USART1->SR&0X40)==0);//1：发送完成
}


void USART_SendStr(USART_TypeDef *USARTx, uint8_t *str){
	while(0 != *str){
		USART_PutChar(USARTx, *str);
		str++;
	}

}