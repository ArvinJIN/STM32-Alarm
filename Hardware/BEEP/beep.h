#ifndef __BEEP_H
#define __BEEP_H	 
#include "define.h"

#define BEEP PBout(8)	// BEEP,�������ӿ�		   
void BEEP_Init(void);	//��������ʼ������	 				    

void Run_Beep();
void Stop_Beep();


#endif
