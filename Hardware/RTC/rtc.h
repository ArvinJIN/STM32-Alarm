#ifndef __RTC_H__
#define __RTC_H__
#include "define.h"

//ʱ��ṹ��
typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//������������
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;	
}_calendar_obj;

extern _calendar_obj calendar;				//�����ṹ��

u8 RTC_Init(void);        					//��ʼ��RTC,����0,ʧ��;1,�ɹ�;
u8 Is_Leap_Year(u16 year);					//ƽ��,�����ж�
u8 RTC_Get(void);         					//��ȡʱ��   
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);		//����ʱ��	

uint32_t RTC_GetCounter();
void RTC_SetCounter(uint32_t CounterValue);

#endif