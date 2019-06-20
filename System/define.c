#include "define.h"




//����NVIC����
//NVIC_Group:NVIC���� 0~4 �ܹ�5�� 		   
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//ȡ����λ
	temp1<<=8;
	temp=SCB->AIRCR;  //��ȡ��ǰ������
	temp&=0X0000F8FF; //�����ǰ����
	temp|=0X05FA0000; //д��Կ��
	temp|=temp1;	   
	SCB->AIRCR=temp;  //���÷���	    	  				   
}


//����NVIC 
//NVIC_PreemptionPriority:��ռ���ȼ�
//NVIC_SubPriority       :��Ӧ���ȼ�
//NVIC_Channel           :�жϱ��
//NVIC_Group             :�жϷ��� 0~4
//ע�����ȼ����ܳ����趨����ķ�Χ!����������벻���Ĵ���
//�黮��:
//��0:0λ��ռ���ȼ�,4λ��Ӧ���ȼ�
//��1:1λ��ռ���ȼ�,3λ��Ӧ���ȼ�
//��2:2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
//��3:3λ��ռ���ȼ�,1λ��Ӧ���ȼ�
//��4:4λ��ռ���ȼ�,0λ��Ӧ���ȼ�
//NVIC_SubPriority��NVIC_PreemptionPriority��ԭ����,��ֵԽС,Խ����	   
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	MY_NVIC_PriorityGroupConfig(NVIC_Group);//���÷���
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;								//ȡ����λ  
	NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//ʹ���ж�λ
//stm32�����200����жϰɣ�NVIC_Channl���������һ����
//����USART2_IRQn = 38����Щ�ж���8��32λ�Ĵ���ʹ֮ʹ�ܣ�
//����USART2_IRQn��˵��38/32 =1,38%32=6������ҪʹUSART2�ж�ʹ�ܵĻ���
//��������NVIC->ISER[1]����λΪ1(��������ļĴ���)	
	NVIC->IP[NVIC_Channel]|=temp<<4;		//������Ӧ���ȼ����������ȼ�   	    	  				   
} 




//			������ʹ��ÿ��PLL֮ǰ���PLL������(ѡ��ʱ��Դ��Ԥ��Ƶϵ���ͱ�Ƶϵ����)��ͬʱӦ
//      �������ǵ�����ʱ���ȶ�(����λ)�����ʹ�ܡ�һ��ʹ����PLL����Щ�����������ٱ��ı䡣
//			���ı���PLL������ʱ��Դʱ��������ѡ�����µ�ʱ��Դ(ͨ��ʱ�����üĴ���(RCC_CFGR)
//			�� PLLSRCλ)֮����ܹر�ԭ����ʱ��Դ��

//ϵͳʱ�ӳ�ʼ������
//pll:ѡ��ı�Ƶ������2��ʼ�����ֵΪ16	
void Stm32_Clock_Init(){
	u8 PLL = 9;
	unsigned char temp = 0;
	
	//������ʱ�ӼĴ�����λ
	
	//APB1 ���踴λ�Ĵ���(RCC_APB1RSTR)
	RCC->APB1RSTR = 0x00000000;//��λ����	
	RCC->APB2RSTR = 0x00000000;
	
	//AHB����ʱ��ʹ�ܼĴ��� (RCC_AHBENR)
	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	 
	
	//APB2 ����ʱ��ʹ�ܼĴ���(RCC_APB2ENR)
  RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  RCC->APB1ENR = 0x00000000; 
	
	
	//ʱ�ӿ��ƼĴ���(RCC_CR)
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION	 		
	
  //ʱ�����üĴ���(RCC_CFGR)��PLL2ʱ�������	
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]			
	
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	
	//ʱ���жϼĴ���(RCC_CIR)
	RCC->CIR = 0x00000000;     //�ر������ж�		
	
//�����ж��������ַ��ƫ���������������Ǹ�����
//��ַ��0x08000000
//ƫ����	��0x0
//STM32�����ڴ��СΪ512Kb,0x80000000-----0x80080000
	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);
	
	
	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	
	while(!(RCC->CR>>17));//�ȴ��ⲿʱ�Ӿ���
	
	RCC->CFGR=0X00000400; //APB1=2��Ƶ;APB2=1��Ƶ;AHB=1��Ƶ;
	PLL-=2;				  //����2����λ����Ϊ�Ǵ�2��ʼ�ģ�����0����2��
	
	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	
	FLASH->ACR|=0x32;	  //FLASH 2����ʱ����
	
	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	
	RCC->CFGR|=0x00000002;//PLL�����Ϊϵͳʱ��	 
	while(temp!=0x02)     //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		    
