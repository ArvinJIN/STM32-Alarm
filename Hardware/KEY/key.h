#ifndef __KEY_H
#define __KEY_H	 
#include "define.h"

#define KEY0	PEin(4) //PE4
 
#define KEY0_PRES 1	//KEY0按下


void KEY_Init(void);	//IO初始化
u8 KEY_Scan();  		//按键扫描函数		

#endif
