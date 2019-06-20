#include "key.h"
#include "delay.h"

//按键初始化函数
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	RCC->APB2ENR|=1<<6;     //使能PORTE时钟
	GPIOA->CRL&=0XFFFFFFF0;	//PA0设置成输入，默认下拉	  
	GPIOA->CRL|=0X00000008; 
	  
	GPIOE->CRL&=0XFFF00FFF;	//PE3/4设置成输入	  
	GPIOE->CRL|=0X00088000; 				   
	GPIOE->ODR|=3<<3;	   	//PE3/4 上拉
} 


//按键处理函数
//返回按键值
//0，没有任何按键按下
//1，KEY0按下
//KEY0 是低电平有效的
u8 KEY_Scan()
{	 
	if(KEY0==0)
		return 1;
	return 0;
}
