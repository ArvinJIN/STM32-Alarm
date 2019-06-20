#ifndef __LCD_H
#define __LCD_H	
#include "define.h"
#include "stdlib.h"


typedef struct{
	u16 width;		//LCD ���
	u16 height;		//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	wramcmd;	//��ʼдgramָ��
	u16  setxcmd;	//����x����ָ��
	u16  setycmd;	//����y����ָ�� 
}_lcd_dev;

//LCD����
extern _lcd_dev lcddev;	//����LCD��Ҫ����

//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

#define LCD_LED PBout(0)

typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;


//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//STM32�ڲ�������һλ����
//Bank1.sector4 �ӵ�ַ 0X6C000000 ��ʼ���� 0X000007FE������ A10 ��ƫ����
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)


//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��


//������ɫ
#define WHITE         0xFFFF
#define BLACK         0x0000	  
#define BLUE          0x001F  
#define RED           0xF800



void LCD_Init(void);													   	//��ʼ��
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//���ù��
void LCD_Clear(u16 Color);	 												//����

void LCD_DrawPoint(u16 x,u16 y);											//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color);								//����ָ����ɫ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//������

void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);		   				//��䵥ɫ

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);	//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);		//��ʾһ������
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);	//��ʾһ���ַ���,12/16����
void Show_Str_Mid(u16 x,u16 y,u8*str,u8 size,u8 len);




#endif
