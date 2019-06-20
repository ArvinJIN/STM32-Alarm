#include "key.h"
#include "delay.h"

//������ʼ������
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	GPIOA->CRL&=0XFFFFFFF0;	//PA0���ó����룬Ĭ������	  
	GPIOA->CRL|=0X00000008; 
	  
	GPIOE->CRL&=0XFFF00FFF;	//PE3/4���ó�����	  
	GPIOE->CRL|=0X00088000; 				   
	GPIOE->ODR|=3<<3;	   	//PE3/4 ����
} 


//����������
//���ذ���ֵ
//0��û���κΰ�������
//1��KEY0����
//KEY0 �ǵ͵�ƽ��Ч��
u8 KEY_Scan()
{	 
	if(KEY0==0)
		return 1;
	return 0;
}
