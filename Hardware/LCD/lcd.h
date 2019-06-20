#ifndef __LCD_H
#define __LCD_H	
#include "define.h"
#include "stdlib.h"


typedef struct{
	u16 width;		//LCD 宽度
	u16 height;		//LCD 高度
	u16 id;				//LCD ID
	u8  dir;			//横屏还是竖屏控制：0，竖屏；1，横屏。	
	u16	wramcmd;	//开始写gram指令
	u16  setxcmd;	//设置x坐标指令
	u16  setycmd;	//设置y坐标指令 
}_lcd_dev;

//LCD参数
extern _lcd_dev lcddev;	//管理LCD重要参数

//LCD的画笔颜色和背景色	   
extern u16  POINT_COLOR;//默认红色    
extern u16  BACK_COLOR; //背景颜色.默认为白色

#define LCD_LED PBout(0)

typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;


//使用NOR/SRAM的 Bank1.sector4,地址位HADDR[27,26]=11 A10作为数据命令区分线 
//STM32内部会右移一位对齐
//Bank1.sector4 从地址 0X6C000000 开始，而 0X000007FE，则是 A10 的偏移量
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)


//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define DFT_SCAN_DIR  L2R_U2D  //默认的扫描方向


//画笔颜色
#define WHITE         0xFFFF
#define BLACK         0x0000	  
#define BLUE          0x001F  
#define RED           0xF800



void LCD_Init(void);													   	//初始化
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//设置光标
void LCD_Clear(u16 Color);	 												//清屏

void LCD_DrawPoint(u16 x,u16 y);											//画点
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//画点指定颜色
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//画矩形

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//填充单色

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);	//显示一个字符
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);		//显示一个数字
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);	//显示一个字符串,12/16字体
void Show_Str_Mid(u16 x,u16 y,u8*str,u8 size,u8 len);




#endif
