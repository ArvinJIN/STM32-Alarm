#include "delay.h"

static u8 	fac_us=0;  //us��ʱ������
static u16 	fac_ms=0;	 //ms��ʱ������



//�ⲿ����Ϊ 8M��Ȼ��Ƶ�� 72M��SysTick ��ʱ��Դ�� HCLK �� 8 ��Ƶ��SysTick ��ʱ�Ӽ�Ϊ 9Mhz

void delay_init(u8 SYSCLK){
	SysTick->CTRL &=~(1<<2);//SYSTICKʹ���ⲿʱ��Դ
	fac_us=SYSCLK/8;
	fac_ms=(u16)fac_us*1000;
}


/*	�Ȱ�Ҫ��ʱ�� us ������� SysTick ��ʱ������Ȼ��д�� LOAD �Ĵ�����
*		Ȼ����յ�ǰ�Ĵ��� VAL �����ݣ��ٿ����������ܡ�
*		�ȵ���������������ʱ��nus�����ر�SysTick�����VAL��ֵ��
*		ʵ��һ����ʱnus�Ĳ�����temp&0x01����һ���������ж�systick��ʱ��
*		�Ƿ񻹴��ڿ���״̬�����Է�ֹsystick������رյ��µ���ѭ����
*/
void delay_us(u32 nus){
	u32 temp;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0x00;
	SysTick->CTRL=0x01;
	do{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL=0x00;
	SysTick->VAL=0x00;
}


void delay_ms(u16 nms){
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           			//��ռ�����
	SysTick->CTRL=0x01 ;          			//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;      	 			//�رռ�����
	SysTick->VAL =0X00;       				//��ռ�����	 
}