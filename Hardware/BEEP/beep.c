#include "beep.h"

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��		    
//��������ʼ��
void BEEP_Init(void)
{
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��	   	  
	GPIOB->CRH&=0XFFFFFFF0; 
	GPIOB->CRH|=0X00000003;	//PB.8 �������    
	BEEP=0;					//�رշ��������
}


void Run_Beep(){
		BEEP=0;		  
		delay_ms(300);//��ʱ300ms  
		BEEP=1;  
		delay_ms(300);//��ʱ300ms
}

void Stop_Beep(){
	BEEP = 0;
}