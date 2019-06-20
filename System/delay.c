#include "delay.h"

static u8 	fac_us=0;  //us延时倍乘数
static u16 	fac_ms=0;	 //ms延时倍乘数



//外部晶振为 8M，然后倍频到 72M，SysTick 的时钟源自 HCLK 的 8 分频，SysTick 的时钟即为 9Mhz

void delay_init(u8 SYSCLK){
	SysTick->CTRL &=~(1<<2);//SYSTICK使用外部时钟源
	fac_us=SYSCLK/8;
	fac_ms=(u16)fac_us*1000;
}


/*	先把要延时的 us 数换算成 SysTick 的时钟数，然后写入 LOAD 寄存器。
*		然后清空当前寄存器 VAL 的内容，再开启倒数功能。
*		等到倒数结束，即延时了nus。最后关闭SysTick，清空VAL的值。
*		实现一次延时nus的操作，temp&0x01，这一句是用来判断systick定时器
*		是否还处于开启状态，可以防止systick被意外关闭导致的死循环。
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
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           			//清空计数器
	SysTick->CTRL=0x01 ;          			//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//等待时间到达   
	SysTick->CTRL=0x00;      	 			//关闭计数器
	SysTick->VAL =0X00;       				//清空计数器	 
}