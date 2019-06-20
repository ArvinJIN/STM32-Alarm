#include "define.h"
#include "delay.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "rtc.h"
#include "touch.h"
#include "key.h"
#include "usart.h"



long long int TimeMode = 1; ////时间增长模式，一次按键加减TimeMode秒，全局变量
u16 kbdSizeX = 210;
u16 kbdSizeY = 30;
const u8 *kb_str[6]={"  h-   min", "Add Alarm", "Add(1h)", "Sub(1h)", "Add(1min)", "Sub(1min)"};
static u32	AlarmTime;
static vu8 hour;
static vu8 min;
static vu8 sec;
static u32 AlarmClocks[10]={0};
static u8 AlarmCount=0;

void ShowDate();
//void MyRTC_SetCounter(u32 TimeStamp);
void Draw_UI(u16 x, u16 y);
void Show_ClockSetting(u16 x, u16 y);
void Key_StateSet(u16 x,u16 y,u8 keyx,u8 sta);
u8 Key_GetInput(u16 x, u16 y);
u8 Get_TimeMode();
void Set_Alarm(u16 x, u16 y);

int main(void)
{		
	u8 th=0;
	u8 tm=0;
	u8 ts=0;
	
	u32 CurrentTime;
	int i;
	
	Stm32_Clock_Init();//系统时钟设置
	uart_init(72,115200);	//串口初始化为115200
	delay_init(72);	  	//延时初始化
	LED_Init();		  	//初始化与LED连接的硬件接口
	BEEP_Init();
	KEY_Init();
	RTC_Init();
	LCD_Init();				//初始化LCD
	
	//RTC_Set(2019,4,30,14,04,30);
	
	GT9147_Init();
	POINT_COLOR=RED;//设置字体为红色 
	LCD_ShowString(60,70,200,16,16,"Alarm_Arvin");	
	LCD_ShowString(60,90,200,16,16,"Embedded experiment");
	LCD_ShowString(60,110,200,16,16,"2019/6");	
	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60,130,200,16,16,"    -  -  ");	   
	LCD_ShowString(60,162,200,16,16,"  :  :  ");
	LCD_ShowString(60,200,300,16,16,"Alarm list has been set");
	kbdSizeX=210;
	kbdSizeY=70;
	Draw_UI(30,520);
	hour = calendar.hour;//Alarm_hour
	min = calendar.min;//Alarm_min
	sec = calendar.sec;
	AlarmTime = RTC_GetCounter()-sec + 2;
	Show_ClockSetting(30,520);
	
	while(1)
	{		
		
		for(i=0;i<AlarmCount;i++){
			if(AlarmClocks[i] == RTC_GetCounter()){
				USART_SendStr(USART1, "**Alarm**");//向串口1发送数据
				while(1){
					Run_Beep();
					ShowDate();
					if(KEY_Scan()==1){   //1，KEY0按下//2，KEY1按下//3，KEY3按下WK_UP
						Stop_Beep();
						AlarmClocks[i] = AlarmClocks[i] + 3600;
						break;
					}
				}
			}
		}
		
		if(th!=calendar.hour)
		{
			th = calendar.hour;
			ShowDate();
		}
		if(tm!=calendar.min)
		{
			tm=calendar.min;
			LCD_ShowNum(84,165,calendar.min,2,16);
		}			
		if(ts!=calendar.sec)//每秒刷新一次时间
		{
			ts=calendar.sec;				  
			LCD_ShowNum(108,165,calendar.sec,2,16);
			LED0=!LED0;
			
		}	
		Set_Alarm(30, 520);
		
	} 
 }


void ShowDate(){   //显示时间
	LCD_ShowNum(60,130,calendar.w_year,4,16);									  
	LCD_ShowNum(100,130,calendar.w_month,2,16);									  
	LCD_ShowNum(124,130,calendar.w_date,2,16);	 
	LCD_ShowNum(60,165,calendar.hour,2,16);									  
	LCD_ShowNum(84,165,calendar.min,2,16);									  
	LCD_ShowNum(108,165,calendar.sec,2,16);
}

//加载键盘界面
//x,y:界面起始坐标
void Draw_UI(u16 x, u16 y){
	u16 i;
	POINT_COLOR=RED;
	LCD_DrawRectangle(x,y,x+kbdSizeX*2,y+kbdSizeY*3);						   
	LCD_DrawRectangle(x+kbdSizeX,y,x+kbdSizeX*2,y+kbdSizeY*3);						   
	LCD_DrawRectangle(x,y+kbdSizeY,x+kbdSizeX*2,y+kbdSizeY*2);
	POINT_COLOR=BLUE;
	for(i=0;i<6;i++)
	{
		Show_Str_Mid(x+(i%2)*kbdSizeX,y+16+kbdSizeY*(i/2),(u8*)kb_str[i],24,kbdSizeX);		
	}  
}	


void Show_ClockSetting(u16 x, u16 y){
	LCD_ShowNum(x+kbdSizeX/5,y+16,hour,2,24);									  
	LCD_ShowNum(x+kbdSizeX/2-5,y+16,min,2,24);									  
}


//按键状态设置
//x,y:键盘坐标
//key:键值（1~5）
//state:状态，0，松开；1，按下；
void Key_StateSet(u16 x,u16 y,u8 key,u8 state)
{		 
	if(key > 5||key < 1)return;
	if(state)
		LCD_Fill(x+(key%2)*kbdSizeX+1,y+(key/2)*kbdSizeY+1,x+(key%2)*kbdSizeX+kbdSizeX-1,y+(key/2)*kbdSizeY+kbdSizeY-1,BLUE);
	else 
		LCD_Fill(x+(key%2)*kbdSizeX+1,y+(key/2)*kbdSizeY+1,x+(key%2)*kbdSizeX+kbdSizeX-1,y+(key/2)*kbdSizeY+kbdSizeY-1,WHITE); 
	Show_Str_Mid(x+(key%2)*kbdSizeX,y+16+kbdSizeY*(key/2),(u8*)kb_str[key],24,kbdSizeX);		 
}


//得到触摸屏的输入
//x,y:键盘坐标
//返回值：按键键值（1~5有效；0,无效）
u8 Key_GetInput(u16 x, u16 y){
	u16 i, j;
	static u8 key1 = 0; //未按下任何键，key值为0无效，1~5有效
	u8 key_tmp=0;
	GT9147_Scan(0);
	if(tp_dev.sta&TP_PRES_DOWN){
		for(i=0;i<2;i++){
			for(j=0;j<3;j++){
				if(tp_dev.x[0]<(x+(i+1)*kbdSizeX) && tp_dev.x[0]>(x+i*kbdSizeX) && tp_dev.y[0] < (y+(j+1)*kbdSizeY) && tp_dev.y[0] > y+j*kbdSizeY){
					key_tmp = j*2 + i; //key2为按钮对应的value(0~5)
					break;
				}
			}
			if(key_tmp){
				if(key1 == key_tmp) key_tmp=0;
				else {
					Key_StateSet(x, y, key1, 0);//把原来按钮的位置取消高亮
					key1 = key_tmp;
					Key_StateSet(x, y, key1, 1);
				}
				break;
			}
		}
	}
	else if(key1){
		Key_StateSet(x, y, key1, 0);
		key1=0;
	}
	return key1;
}



//x, y 为键盘起始坐标点
void Set_Alarm(u16 x,u16 y){
	u8 key;
	u8 i;
	key = Key_GetInput(30,520);
	switch(key){
		case 1:
		//	LCD_ShowString(60,250,200,16,16,"DEBUG:case 1");
			if(AlarmTime < RTC_GetCounter())
			{
				AlarmTime = AlarmTime+3600*24;
			}
			
			for(i=0; i < AlarmCount; i++)
			{
				if(AlarmCount==10){
					LCD_ShowString(60,200+11*20,350,16,16,"The maximum number of alarm clocks is 10");
					return;
				}
				if(AlarmTime == AlarmClocks[i])
					return;
			}
			AlarmClocks[AlarmCount++]=AlarmTime;
			LCD_ShowString(60,200+AlarmCount*20,200,16,16,"  :  ");
			LCD_ShowNum(60,200+AlarmCount*20,hour,2,16);
			LCD_ShowNum(84,200+AlarmCount*20,min,2,16);
			break;
		case 2:
			if(hour == 23)
				return;
			AlarmTime = AlarmTime + 3600;
			hour = hour + 1;
			//LCD_ShowString(60,250,200,16,16,"DEBUG:case 2");
			break;
		case 3:
			if(hour == 0)
				return;
			AlarmTime = AlarmTime - 3600;
			hour = hour -1;
			//LCD_ShowString(60,250,200,16,16,"DEBUG:case 3");
			break;
		case 4:
			if(min == 59)
				return;
			AlarmTime = AlarmTime + 60;
			min = (min + 1)%60;
			//LCD_ShowString(60,250,200,16,16,"DEBUG:case 4");
			break;
		case 5:
			if(min==0)
				return;
			AlarmTime = AlarmTime - 60;
			min = (min +60 - 1)%60;
			//LCD_ShowString(60,250,200,16,16,"DEBUG:case 5");
			break;
		default:
			break;
	}
	Show_ClockSetting(x,y);
}

