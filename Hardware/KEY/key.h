#ifndef __KEY_H
#define __KEY_H	 
#include "define.h"

#define KEY0	PEin(4) //PE4
 
#define KEY0_PRES 1	//KEY0����


void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan();  		//����ɨ�躯��		

#endif
