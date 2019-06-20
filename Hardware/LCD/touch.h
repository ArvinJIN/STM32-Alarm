#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "define.h"

#define TP_PRES_DOWN 0x80  		//触屏被按下	  
#define TP_CATH_PRES 0x40  		//有按键按下了 
#define CT_MAX_TOUCH  5    		//电容屏支持的点数

//触摸屏控制器
typedef struct {
	
	u16 x[CT_MAX_TOUCH]; 		//当前坐标
	u16 y[CT_MAX_TOUCH];		//电容屏有最多5组坐标,电阻屏则用x[0],y[0]代表:此次扫描时,触屏的坐标,用
								//x[4],y[4]存储第一次按下时的坐标. 
	u8  sta;				//笔的状态 		
	u8 touchtype;		
}_m_tp_dev;


extern _m_tp_dev tp_dev;	 	//触屏控制器在touch.c里面定义


//芯片连接引脚	   

#define DOUT 				  PBin(2)   	//PB2  MISO
#define TCLK 				  PBout(1)  	//PB1  SCLK
#define IIC_SCL   	  PBout(6) 		//SCL
#define IIC_SDA   	  PBout(7) 		//SDA	 
#define READ_SDA  	  PBin(7) 	 	//??SDA 
#define CT_READ_SDA   PFin(9)  		//输入SDA
#define TDIN 					PFout(9)  	//PF9  MOSI信号
#define TCS  					PFout(11)  	//PF11  CS信号 
#define PEN  					PFin(10)  	//PF10 INT


//I2C读写命令	
#define GT_CMD_WR 		0X28     	//写命令
#define GT_CMD_RD 		0X29		//读命令

//GT9147 部分寄存器定义 
#define GT_CTRL_REG 	0X8040   	//GT9147控制寄存器
#define GT_CFGS_REG 	0X8047   	//GT9147配置起始地址寄存器
#define GT_CHECK_REG 	0X80FF   	//GT9147校验和寄存器
#define GT_PID_REG 		0X8140   	//GT9147产品ID寄存器

#define GT_GSTID_REG 	0X814E   	//GT9147当前检测到的触摸情况
#define GT_TP1_REG 		0X8150  	//第一个触摸点数据地址
#define GT_TP2_REG 		0X8158		//第二个触摸点数据地址
#define GT_TP3_REG 		0X8160		//第三个触摸点数据地址
#define GT_TP4_REG 		0X8168		//第四个触摸点数据地址
#define GT_TP5_REG 		0X8170		//第五个触摸点数据地址  


//IO方向设置
#define CT_SDA_IN()  {GPIOF->CRH&=0XFFFFFF0F;GPIOF->CRH|=8<<4;}
#define CT_SDA_OUT() {GPIOF->CRH&=0XFFFFFF0F;GPIOF->CRH|=3<<4;}
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数	 



u8 TP_Init(void);
u8 GT9147_Scan(u8 mode);
void TP_Adjust();
u8 GT9147_Init(void);



#endif