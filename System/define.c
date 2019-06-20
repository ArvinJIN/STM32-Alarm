#include "define.h"




//设置NVIC分组
//NVIC_Group:NVIC分组 0~4 总共5组 		   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//取后三位
	temp1<<=8;
	temp=SCB->AIRCR;  //读取先前的设置
	temp&=0X0000F8FF; //清空先前分组
	temp|=0X05FA0000; //写入钥匙
	temp|=temp1;	   
	SCB->AIRCR=temp;  //设置分组	    	  				   
}


//设置NVIC 
//NVIC_PreemptionPriority:抢占优先级
//NVIC_SubPriority       :响应优先级
//NVIC_Channel           :中断编号
//NVIC_Group             :中断分组 0~4
//注意优先级不能超过设定的组的范围!否则会有意想不到的错误
//组划分:
//组0:0位抢占优先级,4位响应优先级
//组1:1位抢占优先级,3位响应优先级
//组2:2位抢占优先级,2位响应优先级
//组3:3位抢占优先级,1位响应优先级
//组4:4位抢占优先级,0位响应优先级
//NVIC_SubPriority和NVIC_PreemptionPriority的原则是,数值越小,越优先	   
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//设置分组
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;								//取低四位  
	NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//使能中断位
//stm32最多有200多个中断吧，NVIC_Channl代表的其中一个，
//例如USART2_IRQn = 38。这些中断由8个32位寄存器使之使能，
//就拿USART2_IRQn来说，38/32 =1,38%32=6，所以要使USART2中断使能的话，
//必须设置NVIC->ISER[1]第六位为1(看看下面的寄存器)	
	NVIC->IP[NVIC_Channel]|=temp<<4;		//设置响应优先级和抢断优先级   	    	  				   
} 




//			必须在使能每个PLL之前完成PLL的配置(选择时钟源、预分频系数和倍频系数等)，同时应
//      该在它们的输入时钟稳定(就绪位)后才能使能。一旦使能了PLL，这些参数将不能再被改变。
//			当改变主PLL的输入时钟源时，必须在选中了新的时钟源(通过时钟配置寄存器(RCC_CFGR)
//			的 PLLSRC位)之后才能关闭原来的时钟源。

//系统时钟初始化函数
//pll:选择的倍频数，从2开始，最大值为16	
void Stm32_Clock_Init(){
	u8 PLL = 9;
	unsigned char temp = 0;
	
	//把所有时钟寄存器复位
	
	//APB1 外设复位寄存器(RCC_APB1RSTR)
	RCC->APB1RSTR = 0x00000000;//复位结束	
	RCC->APB2RSTR = 0x00000000;
	
	//AHB外设时钟使能寄存器 (RCC_AHBENR)
	RCC->AHBENR = 0x00000014;  //睡眠模式闪存和SRAM时钟使能.其他关闭.	 
	
	//APB2 外设时钟使能寄存器(RCC_APB2ENR)
  RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
  RCC->APB1ENR = 0x00000000; 
	
	
	//时钟控制寄存器(RCC_CR)
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION	 		
	
  //时钟配置寄存器(RCC_CFGR)，PLL2时钟输出，	
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]			
	
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
	
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	
	//时钟中断寄存器(RCC_CIR)
	RCC->CIR = 0x00000000;     //关闭所有中断		
	
//配置中断向量表基址和偏移量，决定是在那个区域
//基址：0x08000000
//偏移量	：0x0
//STM32的总内存大小为512Kb,0x80000000-----0x80080000
	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);
	
	
	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON
	
	while(!(RCC->CR>>17));//等待外部时钟就绪
	
	RCC->CFGR=0X00000400; //APB1=2分频;APB2=1分频;AHB=1分频;
	PLL-=2;				  //抵消2个单位（因为是从2开始的，设置0就是2）
	
	RCC->CFGR|=PLL<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	
	FLASH->ACR|=0x32;	  //FLASH 2个延时周期
	
	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	
	RCC->CFGR|=0x00000002;//PLL输出作为系统时钟	 
	while(temp!=0x02)     //等待PLL作为系统时钟设置成功
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		    
