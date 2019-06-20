#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "define.h"

#define TP_PRES_DOWN 0x80  		//����������	  
#define TP_CATH_PRES 0x40  		//�а��������� 
#define CT_MAX_TOUCH  5    		//������֧�ֵĵ���

//������������
typedef struct {
	
	u16 x[CT_MAX_TOUCH]; 		//��ǰ����
	u16 y[CT_MAX_TOUCH];		//�����������5������,����������x[0],y[0]����:�˴�ɨ��ʱ,����������,��
								//x[4],y[4]�洢��һ�ΰ���ʱ������. 
	u8  sta;				//�ʵ�״̬ 		
	u8 touchtype;		
}_m_tp_dev;


extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��


//оƬ��������	   

#define DOUT 				  PBin(2)   	//PB2  MISO
#define TCLK 				  PBout(1)  	//PB1  SCLK
#define IIC_SCL   	  PBout(6) 		//SCL
#define IIC_SDA   	  PBout(7) 		//SDA	 
#define READ_SDA  	  PBin(7) 	 	//??SDA 
#define CT_READ_SDA   PFin(9)  		//����SDA
#define TDIN 					PFout(9)  	//PF9  MOSI�ź�
#define TCS  					PFout(11)  	//PF11  CS�ź� 
#define PEN  					PFin(10)  	//PF10 INT


//I2C��д����	
#define GT_CMD_WR 		0X28     	//д����
#define GT_CMD_RD 		0X29		//������

//GT9147 ���ּĴ������� 
#define GT_CTRL_REG 	0X8040   	//GT9147���ƼĴ���
#define GT_CFGS_REG 	0X8047   	//GT9147������ʼ��ַ�Ĵ���
#define GT_CHECK_REG 	0X80FF   	//GT9147У��ͼĴ���
#define GT_PID_REG 		0X8140   	//GT9147��ƷID�Ĵ���

#define GT_GSTID_REG 	0X814E   	//GT9147��ǰ��⵽�Ĵ������
#define GT_TP1_REG 		0X8150  	//��һ�����������ݵ�ַ
#define GT_TP2_REG 		0X8158		//�ڶ������������ݵ�ַ
#define GT_TP3_REG 		0X8160		//���������������ݵ�ַ
#define GT_TP4_REG 		0X8168		//���ĸ����������ݵ�ַ
#define GT_TP5_REG 		0X8170		//��������������ݵ�ַ  


//IO��������
#define CT_SDA_IN()  {GPIOF->CRH&=0XFFFFFF0F;GPIOF->CRH|=8<<4;}
#define CT_SDA_OUT() {GPIOF->CRH&=0XFFFFFF0F;GPIOF->CRH|=3<<4;}
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO��������	 



u8 TP_Init(void);
u8 GT9147_Scan(u8 mode);
void TP_Adjust();
u8 GT9147_Init(void);



#endif