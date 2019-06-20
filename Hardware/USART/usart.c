#include "usart.h"	  


//��ʼ��IO ����1
//pclk2:PCLK2ʱ��Ƶ��(Mhz)
//bound:������ 
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//����USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; //�õ�USARTDIV
	
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ�ӣ�IO�˿�Aʱ�ӿ���
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�ӣ�USART1ʱ��ʹ��
	
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬���ã�GPIO�˿��������ģʽ���� 
	
	RCC->APB2RSTR|=1<<14;   //��λUSART1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	 
	
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //USARTģ��ʹ�ܣ�ʹ�ܷ��ͣ�ʹ�ܽ���
	//ʹ�ܽ����ж� 
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ�ܡ�	    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
	
}


void USART_PutChar(USART_TypeDef *USARTx, uint8_t Data){
	//���ݼĴ�����DR[8:0]������ֵ (Data value) 
	USARTx->DR = (Data & (uint16_t)0x01FF);
  while((USART1->SR&0X40)==0);//1���������
}


void USART_SendStr(USART_TypeDef *USARTx, uint8_t *str){
	while(0 != *str){
		USART_PutChar(USARTx, *str);
		str++;
	}

}