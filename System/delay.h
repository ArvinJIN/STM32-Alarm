#ifndef __DELAY_H
#define __DELAY_H

#include "define.h"


void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u16 nms);


#endif
