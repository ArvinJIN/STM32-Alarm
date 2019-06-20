#ifndef __BEEP_H
#define __BEEP_H	 
#include "define.h"

#define BEEP PBout(8)	// BEEP,蜂鸣器接口		   
void BEEP_Init(void);	//蜂鸣器初始化函数	 				    

void Run_Beep();
void Stop_Beep();


#endif
