/*-----------------------------------------------------------------------
微信公众号        			 	: 爱文电子

作者                           	: 王传强
	
程序名                      		：LCD12864万年历-电子时钟 V2.0.0
                                  
编写日期                        	：2019年5月27日
最后修改日期                  	：2019年6月1日
QQ                              ：1547791594
微信                           	: wcq931224

QQ群							: 760338114
微信公众号                      	: 爱文电子    关注公众号获取更多资源
-----------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "GPIO_Bit_Config.h"
#include "delay.h"
#include "gpio.h"
#include "nvic.h"
#include "exit.h"
#include "lcd12864.h"
#include "usart.h"
#include "picture.h"
#include "math.h"
#include "iic.h"
#include "ds3231.h"
#include "at24c32.h"
#include "calendar.h"
#include<string.h>
#include "festival.h"
#include "dht11.h"
#include "time.h"


uint8_t Z10BCD( uint8_t date);                                     // 十进制转BCD码
uint8_t BCDTO10( uint8_t date );                                   // BCD码转十进制
void Clock_Basic_Disp(void);                                       // 万年历基本显示
void KEY_Timing(void);                                             // 按键调时功能
void LCD_Control_BK(void);                                         // 按键控制背光
void Set_Alarm(void);                                              // 判断闹钟是否到函数

extern char *TianGan,*DiZhi,*ShengXiao,*RiLi,*YueLi;

uint8_t Time_Init[7]  = {0x00,0x23,0x10,0x05,0x28,0x05,0x19};       // 秒 分 时 星期 日 月 年 初始化   01对应星期天~07对应星期六
uint8_t Get_Time[7];                                                // 获取时间数组
uint8_t Get_Temp[2];                                                // 获取温度数组 
uint8_t Now_Time[3] ={0x00};                                        // 用于存放读取当前的时间参数
uint8_t Now_Date[4];
uint8_t Alarm_State = 0;
uint8_t Alarm_Data[3];

                                            
uint8_t temperatureh,temperaturel;  	                              // 存放DHT11温度值  
uint8_t humidityh,humidityl;                                        // 存放DHT11湿度值 
uint8_t DHT11_N_P;                                                  // 判断DHT11测量的温度值大于还是小于0

uint8_t Alarm_Read[6];                                              // 读出AT24C32数据，存放数组
uint8_t Alarm_Write[6] = {1,2,3,4,5,6};                             // 写入AT24C32数据
 
uint16_t time = 0;                                                  // 定时器时间参数

int main(void)
{
	LCD12864_Init();                                                  // LCD12864初始化
	DHT11_Init();                                                     // DHT11初始化 
	IIC_GPIO_Config();	                                              // IIC引脚初始化

	LCD12864_LED_BACK();                                              // 背光控制引脚
	LCD12864_KEY_Congigure();                                         // 按键配置初始化

	LED_BACK = 1;
	LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
	LCD12864_Clear();                                                 // LCD12864清屏 字库方式	

	LCD12864_DrowPic(0,0,128,64,KaiJiDongHua);                        // 显示开机动画
	
	Delay_ms(3000);                                                   // 延时，用于开机动画的显示时间
 	LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
	LCD12864_Clear(); 
	
//	IIC_WriteMultiByte(Time_Init,0x00,7);                             // 把设定的日期写入到DS3231中 
//	AT24C32_PageWrite(0x0000,Alarm_Write,6);
	
//	Exit_Configure();                                                 // 外部中断初始化
//	NVIC_Configure();                                                 // NVIC配置                (放到最后初始化防止上电是背光控制按下)
//	AT24C32_WriteOneByte(0x0007,1);
//	Delay_ms(10);                                                       
	if(AT24C32_ReadOneByte(0x0007) == 1)
	{
		LCD12864_DrowSet(96,16,32,16,23,0);
	}
	if(AT24C32_ReadOneByte(0x0007) == 0)
	{
		LCD12864_DrowSet(96,16,32,16,24,0);
	}
	NVIC_Configure();                                                 // 中断服务函数
	BasicTime_Init();                                                 // 定时器初始化
	USART1_Init(115200);                    // 串口1初始化
	while(1)
	{
		DHT11_Read_Data(&temperatureh,&temperaturel,&humidityh,&humidityl,&DHT11_N_P);	// 读取温湿度值	
		IIC_ReadMultiByte(Get_Time,0x00,7);                                             // 读取DS3231的时间和日期
		Clock_Basic_Disp();                                                             // 万年历基本显示
		KEY_Timing();                                                                   // 判断按键
		LCD_Control_BK();                                                     // 背光控制
		Set_Alarm();
	}
}

/*-----------------------------------------------------------------------
Clock_Basic_Disp   				      ： 万年历基本显示

输入参数                      		： 
				    

编写日期                        	：2019年1月29日
最后修改日期                  		：2019年1月29日
-----------------------------------------------------------------------*/
void Clock_Basic_Disp(void)
{
	uint8_t Date[8];
	
	
	GetChinaCalendar(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4]),Date);       // 得到农历的年
	Get_TianGan_DiZhi_ShengXiao(2000+Date[1],Date[2],Date[3]);                                        // 必须要输入农历的年，获取天干，地址和生肖，月历和日历

	
	LCD12864_Disp_Data(0,0,BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4]));	    // 显示日期	
	LCD12864_DisplayFlaotInt(2,6,BCDTO10(Get_Time[0]));                           // 显示秒
	LCD12864_DrowPicNum(64, 16, Get_Time[1]/16);                                  // 显示分
	LCD12864_DrowPicNum(80, 16, Get_Time[1]%16);
	LCD12864_DrowPicNum(48, 16, 10);                                              // 显示冒号：
	LCD12864_DrowPicNum(16, 16, Get_Time[2]/16);                                  // 显示时
	LCD12864_DrowPicNum(32, 16, Get_Time[2]%16);

	switch(Judge_Week(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4])))              // switch语句判断是星期几
	{
		case 1: LCD12864_DrowWeek(96, 0, 32, 16, 0);/*LCD12864_DisplayStrChin(1 ,6,"幸福");*/ break;
		case 2: LCD12864_DrowWeek(96, 0, 32, 16, 1);/*LCD12864_DisplayStrChin(1 ,6,"美满");*/ break;
		case 3: LCD12864_DrowWeek(96, 0, 32, 16, 2);/*LCD12864_DisplayStrChin(1 ,6,"开心");*/ break;
		case 4: LCD12864_DrowWeek(96, 0, 32, 16, 3);/*LCD12864_DisplayStrChin(1 ,6,"快乐");*/ break;
		case 5: LCD12864_DrowWeek(96, 0, 32, 16, 4);/*LCD12864_DisplayStrChin(1 ,6,"努力");*/ break;
		case 6: LCD12864_DrowWeek(96, 0, 32, 16, 5);/*LCD12864_DisplayStrChin(1 ,6,"奋斗");*/ break;
		case 7: LCD12864_DrowWeek(96, 0, 32, 16, 6);/*LCD12864_DisplayStrChin(1 ,6,"发财");*/ break;
	}	

	if(Festival_Yearly(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4])) == 0)
	{
			if(BCDTO10(Get_Time[0]) % 6 < 3)                                              // 温湿度，农历日期，节日 3秒切换一次
			{
				LCD12864_Disp_Temp(3,4,temperatureh,DHT11_N_P);
				LCD12864_DisplayStrChin(3 ,0,TianGan); 
				LCD12864_DisplayStrChin(3 ,1,DiZhi);
				LCD12864_DisplayStrChin(3 ,2,ShengXiao);
				LCD12864_DisplayStrChin(3 ,3,"年");	
			}
			else
			{
				LCD12864_Dis_humid(3,4,humidityh);
				LCD12864_DisplayStrChin(3 ,0,YueLi); 
				LCD12864_DisplayStrChin(3 ,2,RiLi);
			}
	}
	
	else
	{
			if(BCDTO10(Get_Time[0]) % 9 < 3)                                              // 温湿度3秒切换一次
			{
				LCD12864_Disp_Temp(3,4,temperatureh,DHT11_N_P);
				LCD12864_DisplayStrChin(3 ,0,TianGan); 
				LCD12864_DisplayStrChin(3 ,1,DiZhi);
				LCD12864_DisplayStrChin(3 ,2,ShengXiao);
				LCD12864_DisplayStrChin(3 ,3,"年");	
			}
			else if(BCDTO10(Get_Time[0]) % 9 >= 6) 
			{
				Return_Festival(Festival_Yearly(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4])));        // 返回值判断是哪一个节日				
			}	
			else
			{
				LCD12864_Dis_humid(3,4,humidityh);
				LCD12864_DisplayStrChin(3 ,0,YueLi); 
				LCD12864_DisplayStrChin(3 ,2,RiLi);
			}
	}

}


uint8_t Z10BCD( uint8_t date)    //十进制转BCD码
{
   uint8_t i,j;
   i=date/10;
   j=date-(i*10);
    i=(i<<4)|j;  
   return (i);
}
uint8_t BCDTO10( uint8_t date )   //BCD码转10进制
{
 uint8_t i,j;
 i=(date & 0xf0)>>4 ;
 j=date & 0x0f ;
 i=i*10+j;
 return i;
}

uint8_t Menu = 0;                       // 定义菜单变量
uint8_t Sure_Flag = 0;                  // 确定键按下的标志位
uint8_t Time_Flag = 0;     
uint8_t Adjust_Sure = 0,Adjust_Choose = 0;        // 调整确定或者退出标志
uint8_t Alarm_Flag = 0;                 // 闹钟标志位
uint8_t Adjust_Alarm = 0;                 // 确定设置或突出设置闹钟标志
uint8_t Count_Flag = 0;                   // 计数器标志位
uint8_t Z_F_Count = 0;                    // 判断正计时还是负计时
uint8_t Input_JS = 0;                     // 进入计时标志位
uint8_t JS_Time[3] = {0};                 // 计数时间存放到数组内 JS_Time[2]:时 JS_Time[1]:分 JS_Time[0]:秒 
uint8_t ZJS_Status = 0;
uint8_t DJS_Flag = 0,DJS_Flag1 = 0,DJS_Flag2 = 0;                     // 判断是否进入倒计时标志
uint8_t DJS_Rest = 0;
uint8_t DJS_RestAyyr[3];
uint8_t DJS_Stop = 0;
void KEY_Timing(void)
{
	/*
		选择按键 
	*/ 
	if(K_UP == 0 && Sure_Flag == 0 && Input_JS == 0 )
	{
		Delay_ms(20);
		if(K_UP == 0 && Sure_Flag == 0 && Input_JS == 0 )
		{
			while(K_UP == 0);                         // 等待按键松开
			Menu++;
			if(Menu==1){LCD12864_DrawClear();LCD12864_Clear();}
			if(Menu==5)
			{
				Menu = 0; 
				LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
				LCD12864_Clear();                                                 // LCD12864清屏 字库方式	
				
				if(AT24C32_ReadOneByte(0x0007) == 1)
				{
					LCD12864_DrowSet(96,16,32,16,23,0);
				}
				if(AT24C32_ReadOneByte(0x0007) == 0)
				{
					LCD12864_DrowSet(96,16,32,16,24,0);
				}
			}
		}
	}
	if(K_UP == 0 && Sure_Flag == 1 && Input_JS == 0 )
	{
		Delay_ms(20);
		if(K_UP == 0 && Sure_Flag == 1 && Input_JS == 0 )
		{
			while(K_UP == 0);                         // 等待按键松开
			Time_Flag++;
			if(Time_Flag==5)
			{
				Time_Flag = 1;
			}
		}
	}
	
	if(K_UP == 0 && Sure_Flag == 2 && Input_JS == 0 )
	{
		Delay_ms(20);
		if(K_UP == 0 && Sure_Flag == 2 && Input_JS == 0)
		{
			while(K_UP == 0);                         // 等待按键松开
			Alarm_Flag++;
			if(Alarm_Flag==8)
			{
				Alarm_Flag = 1;
			}
		}
	}
	
	if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 0)
	{
		Delay_ms(20);
		if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 0)
		{
			while(K_UP == 0);                         // 等待按键松开
			Count_Flag++;
			if(Count_Flag==3)
			{
				Count_Flag = 1;
			}
		}
	}	
	

	/*
		确定按键
	*/
	if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0)                                            // && Menu !=0 是为了在正常显示状态下 防止误按下此键
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0)
		{
			while(K_Down == 0); 
			LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
			LCD12864_Clear();                                                 // LCD12864清屏 字库方式	
			if(Sure_Flag == 0)
			{
				if(Menu == 1)
				{
					Sure_Flag = 1;
					IIC_ReadMultiByte(Now_Time,0x00,3);// 如果要设置时间，就要把当前的时间读出来
					Now_Time[0] = BCDTO10(Now_Time[0]);Now_Time[1] = BCDTO10(Now_Time[1]);Now_Time[2] = BCDTO10(Now_Time[2]);
				}                
				if(Menu == 2)
				{
					Sure_Flag = 1;
					IIC_ReadMultiByte(Now_Date,0x03,4);// 如果要设置日期，就要把当前的日期读出来
					Now_Date[0] = BCDTO10(Now_Date[0]);Now_Date[1] = BCDTO10(Now_Date[1]);Now_Date[2] = BCDTO10(Now_Date[2]);Now_Date[3] = BCDTO10(Now_Date[3]);
				}
				if(Menu == 3)
				{
					Sure_Flag = 2;                     // 进入闹钟标志
					AT24C32_PageRead(0x0000,Alarm_Read,6);
				}
				if(Menu == 4)
				{
					Sure_Flag = 3;                     // 进入计时模式
				}
			}
	
		}
	}
	if(K_Down == 0 && Menu !=0 && Time_Flag == 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0 )                                            // && Menu !=0 是为了在正常显示状态下 防止误按下此键
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag == 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0 )
		{
			while(K_Down == 0);
			
			/*
				确定调时
			*/
			if(Adjust_Choose == 1)                                            
			{
				if(Adjust_Sure == 1)                                               // 如果选择了确定，写入到DS3231时间在返回到显示界面
				{
					Now_Time[0] = Z10BCD(Now_Time[0]);Now_Time[1] = Z10BCD(Now_Time[1]);Now_Time[2] = Z10BCD(Now_Time[2]);
					IIC_WriteMultiByte(Now_Time,0x00,3);                              // 写入时间到DS3231寄存器
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
					LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
					LCD12864_Clear();                                                 // LCD12864清屏 字库方式	
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}
				}
				else                                                                // 如果选择了退出，直接返回到显示界面
				{
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
					LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
					LCD12864_Clear();                                                 // LCD12864清屏 字库方式
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}					
				}
			}
			/*
				确定调日期
			*/
			if(Adjust_Choose == 2)  
			{
				if(Adjust_Sure == 1)                                               // 如果选择了确定，写入到DS3231时间在返回到显示界面
				{
					Now_Date[0] = Z10BCD(Now_Date[0]);Now_Date[1] = Z10BCD(Now_Date[1]);Now_Date[2] = Z10BCD(Now_Date[2]);Now_Date[3] = Z10BCD(Now_Date[3]);
					IIC_WriteMultiByte(Now_Date,0x03,4);                              // 写入时间到DS3231寄存器
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
					LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
					LCD12864_Clear();                                                 // LCD12864清屏 字库方式	
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}
				}
				else                                                                // 如果选择了退出，直接返回到显示界面
				{
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
					LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
					LCD12864_Clear();                                                 // LCD12864清屏 字库方式		
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}					
				}
			}
		}
	}
	
	if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag == 7 && Count_Flag == 0 && Input_JS == 0)                                            // && Menu !=0 是为了在正常显示状态下 防止误按下此键
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag == 7 && Count_Flag == 0 && Input_JS == 0)
		{
			while(K_Down == 0);
			if(Adjust_Alarm == 0)                                                  // 关闭闹钟
			{
				AT24C32_WriteOneByte(0x0007,0);
				Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
				LCD12864_DrawClear();                                                      // LCD12864清屏 画点方式
				LCD12864_Clear();                                                          // LCD12864清屏 字库方式	
				if(AT24C32_ReadOneByte(0x0007) == 1)
				{
					LCD12864_DrowSet(96,16,32,16,23,0);
				}
				if(AT24C32_ReadOneByte(0x0007) == 0)
				{
					LCD12864_DrowSet(96,16,32,16,24,0);
				}			
			}
			else                                                                  // 开启闹钟
			{				
				AT24C32_WriteOneByte(0x0007,1);			                       // 把设置好的数据写入AT24C32 
				Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
				LCD12864_DrawClear();                                                      // LCD12864清屏 画点方式
				LCD12864_Clear();                                                          // LCD12864清屏 字库方式
				AT24C32_PageWrite(0x0000,Alarm_Read,7);	
				LCD12864_DrowSet(96,16,32,16,23,0);	
			}
		}
	}
	
	if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag != 0 && Input_JS == 0 )                                            // && Menu !=0 是为了在正常显示状态下 防止误按下此键
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag != 0 && Input_JS == 0)
		{
			while(K_Down == 0);
			if(Z_F_Count == 0)                                                  // 退出计时 
			{
				Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
				LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
				LCD12864_Clear();                                                 // LCD12864清屏 字库方式
//				LCD12864_DrowSet(96,16,32,16,24,0);	
				if(AT24C32_ReadOneByte(0x0007) == 1)
				{
					LCD12864_DrowSet(96,16,32,16,23,0);
				}
				if(AT24C32_ReadOneByte(0x0007) == 0)
				{
					LCD12864_DrowSet(96,16,32,16,24,0);
				}
			}
			else if(Z_F_Count == 1)                                             // 进入正计时
			{				
				LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
				LCD12864_Clear();                                                 // LCD12864清屏 字库方式
				LCD12864_DrowSet(48,0,16,16,50,0);	LCD12864_DrowSet(64,0,16,16,51,0);	   // 显示计时
				LCD12864_DrowSet(32,48,64,16,53,0);	
				
				if(ZJS_Status == 0)
				{
					LCD12864_DrowSet(0,0,16,16,54,1);LCD12864_DrowSet(16,0,16,16,55,1);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				Input_JS = 1;
//				TIM_Cmd(TIMx,ENABLE);           								// 开启定时器
			}
			else if(Z_F_Count == 2)                                             // 进入倒计时
			{
				LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
				LCD12864_Clear();                                                 // LCD12864清屏 字库方式
				Input_JS = 2;
			}
		}
	}
	if(Input_JS == 2 )
	{
		if(DJS_Flag1 == 0 ){LCD12864_DrowSet(16,0,16,16,9,0);LCD12864_DrowSet(32,0,16,16,10,0);LCD12864_DrowSet(48,0,16,16,60,0);LCD12864_DrowSet(64,0,16,16,61,0);LCD12864_DrowSet(80,0,16,16,7,0);LCD12864_DrowSet(96,0,16,16,8,0);} // 设置定时时间
		
		if(ZJS_Status == 0 && DJS_Flag1 == 0 )
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,1);                                  // 显示分  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,1);
			LCD12864_DrowPicNum(32, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,0);                                  // 显示时
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,0);
			LCD12864_DrowPicNum(80, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,0);                                  // 显示时
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,0);
			
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
			LCD12864_DrowSet(32,48,64,16,40,0);                                             // 显示/* <+  ->*/
		}
		if(ZJS_Status == 1 && DJS_Flag1 == 0)
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,0);                                  // 显示分  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,0);
			LCD12864_DrowPicNum(32, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,1);                                  // 显示时
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,1);
			LCD12864_DrowPicNum(80, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,0);                                  // 显示时
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,0);
			
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
			LCD12864_DrowSet(32,48,64,16,40,0);                                             // 显示/* <+  ->*/
		}
		if(ZJS_Status == 2 && DJS_Flag1 == 0)
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,0);                                  // 显示分  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,0);
			LCD12864_DrowPicNum(32, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,0);                                  // 显示时
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,0);
			LCD12864_DrowPicNum(80, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,1);                                  // 显示时
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,1);
			
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
			LCD12864_DrowSet(32,48,64,16,40,0);                                             // 显示/* <+  ->*/
		}
		if(ZJS_Status == 3 && DJS_Flag1 == 0)
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,0);                                  // 显示分  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,0);
			LCD12864_DrowPicNum(32, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,0);                                  // 显示时
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,0);
			LCD12864_DrowPicNum(80, 16, 10);                                              // 显示冒号：
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,0);                                  // 显示时
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,0);
			
//			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
//			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
			LCD12864_DrowSet(32,48,64,16,39,0);                                             // 显示/* <+♂->*/
		}
		if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 0)
		{
			Delay_ms(20);
			if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 0)
			{
				while(K_UP == 0);                         // 等待按键松开
				ZJS_Status++;
				if(ZJS_Status == 4)
				{
					ZJS_Status = 0;
				}
			}
		}
		if(ZJS_Status == 0)
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					JS_Time[2] ++;
					if(JS_Time[2] > 23) JS_Time[2] = 0;
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					if(JS_Time[2] == 0) JS_Time[2] = 24;
					JS_Time[2] -- ;
				}
			}
		}

		if(ZJS_Status == 1)
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					JS_Time[1] ++;
					if(JS_Time[1] > 59) JS_Time[1] = 0;
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					if(JS_Time[1] == 0) JS_Time[1] = 60;
					JS_Time[1] -- ;
				}
			}
		}

		if(ZJS_Status == 2)
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					JS_Time[0] ++;
					if(JS_Time[0] > 59) JS_Time[0] = 0;
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					if(JS_Time[0] == 0) JS_Time[0] = 60;
					JS_Time[0] -- ;
				}
			}
		}
		if(ZJS_Status == 2)
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					LCD12864_DrowSet(0,48,16,16,29,1);LCD12864_DrowSet(16,48,16,16,30,1);           // 显示确定
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
				}
			}	
		}
		if(ZJS_Status == 3)
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					LCD12864_DrowSet(0,48,16,16,29,1);LCD12864_DrowSet(16,48,16,16,30,1);           // 显示确定
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
					DJS_Flag = 1;
					DJS_Flag1 = 0;
				}
			}
			if(K_Left == 0)                     // +
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
					LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);         // 显示退出
					DJS_Flag = 0;
					DJS_Flag1 = 0;
				}
			}	
			if(K_Down == 0 && ZJS_Status == 3 && DJS_Flag1 == 0)
			{
				Delay_ms(20);
				if(K_Down == 0 && ZJS_Status == 3 && DJS_Flag1 == 0)
				{
					if(DJS_Flag == 0)
					{
						Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0; DJS_Flag = 0;ZJS_Status=0; // 清除所有标志位
						LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
						LCD12864_Clear();                                                 // LCD12864清屏 字库方式
						if(AT24C32_ReadOneByte(0x0007) == 1)
						{
							LCD12864_DrowSet(96,16,32,16,23,0);
						}
						if(AT24C32_ReadOneByte(0x0007) == 0)
						{
							LCD12864_DrowSet(96,16,32,16,24,0);
						}						
					}
					else
					{
						DJS_Flag1 = 1;
						LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
						LCD12864_Clear();                                                 // LCD12864清屏 字库方式
						LCD12864_DrowSet(48,0,16,16,50,0);	LCD12864_DrowSet(64,0,16,16,51,0);	   // 显示计时
						LCD12864_DrowSet(32,48,64,16,53,0);	
					}
				}
			}
			if(DJS_Flag1 == 1)
			{
				if(DJS_Rest == 0)
				{
					DJS_Rest = 1;
					DJS_RestAyyr[2] = JS_Time[2];DJS_RestAyyr[1] = JS_Time[1];DJS_RestAyyr[0] = JS_Time[0];
				}
				LCD12864_DrowPicNum(0, 16, JS_Time[2]/10);                                  // 显示分  uint8_t DJS_Rest = 0;uint8_t DJS_RestAyyr[3];
				LCD12864_DrowPicNum(16, 16, JS_Time[2]%10);
				LCD12864_DrowPicNum(32, 16, 10);                                              // 显示冒号：
				LCD12864_DrowPicNum(48, 16, JS_Time[1]/10);                                  // 显示时
				LCD12864_DrowPicNum(64, 16, JS_Time[1]%10);
				LCD12864_DrowPicNum(80, 16, 10);                                              // 显示冒号：
				LCD12864_DrowPicNum(96, 16, JS_Time[0]/10);                                  // 显示时  
				LCD12864_DrowPicNum(112, 16, JS_Time[0]%10);	
				
				if(time > 999)                // 1秒定时时间到   
				{
					time = 0;
					
					if(JS_Time[0]==0)
					{
						JS_Time[0] = 60;
						if(JS_Time[1] == 0)
						{
							JS_Time[1] = 60; 
							if(JS_Time[2]==0 && JS_Time[1]==0 && JS_Time[0]== 0)         // 倒计时时间到
							{
								TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
							}
							JS_Time[2]--;
						}
						JS_Time[1]--;
					}	
					JS_Time[0]--;					
					if(JS_Time[2]==0 && JS_Time[1]==0 && JS_Time[0]== 0)         // 倒计时时间到
					{
						TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
						DJS_Stop = 1;
						LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
						LCD12864_Clear();                                                 // LCD12864清屏 字库方式
						LCD12864_DisplayStrChin(0,0,"倒计时时间到了！");
						Delay_ms(3000);                                                   // 延时，用于开机动画的显示时间

						LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
						LCD12864_Clear();                                                 // LCD12864清屏 字库方式	
						LCD12864_DrowSet(48,0,16,16,50,0);	LCD12864_DrowSet(64,0,16,16,51,0);	   // 显示计时
						LCD12864_DrowSet(32,48,64,16,53,0);	
					}
				}

				if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 1)
				{
					Delay_ms(20);
					if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 1)
					{
						while(K_UP == 0);                         // 等待按键松开
						DJS_Flag2++;
						if(DJS_Flag2 == 4)
						{
							DJS_Flag2 = 0;
						}
					}
				}
			
				if(DJS_Flag2 == 0)
				{
					LCD12864_DrowSet(0,0,16,16,54,1);LCD12864_DrowSet(16,0,16,16,55,1);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				if(DJS_Flag2 == 1)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,1);LCD12864_DrowSet(112,0,16,16,57,1);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				if(DJS_Flag2 == 2)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,1);LCD12864_DrowSet(16,48,16,16,59,1);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				if(DJS_Flag2 == 3)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);    // 显示退出
				}
				
				if(K_Down == 0 &&  DJS_Flag1 == 1)
				{
					Delay_ms(20);
					if(K_Down == 0 &&  DJS_Flag1 == 1)
					{
						if(DJS_Flag2 == 0 && DJS_Stop == 0)
						{
							TIM_Cmd(TIMx,ENABLE);  // 开启定时器
							time = 0;
						}
						if(DJS_Flag2 == 1)
						{
							TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
						}
						if(DJS_Flag2 == 2)
						{
							TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
							DJS_Stop = 0;
							time = 0;
							DJS_Rest = 0;
							JS_Time[2] = DJS_RestAyyr[2];JS_Time[1] = DJS_RestAyyr[1];JS_Time[0] = DJS_RestAyyr[0];
						}
						if(DJS_Flag2 == 3)
						{
							TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
							time = 0;
							Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;DJS_Flag1 = 0; DJS_Flag2 = 0; ZJS_Status = 0;DJS_Flag = 0;DJS_Stop = 0;DJS_Rest = 0;// 清除所有标志位
							JS_Time[2] = 0;JS_Time[1] = 0;JS_Time[0] = 0;
							LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
							LCD12864_Clear();                                                 // LCD12864清屏 字库方式
							if(AT24C32_ReadOneByte(0x0007) == 1)
							{
								LCD12864_DrowSet(96,16,32,16,23,0);
							}
							if(AT24C32_ReadOneByte(0x0007) == 0)
							{
								LCD12864_DrowSet(96,16,32,16,24,0);
							}
						}						
					}
				}
			}			
		}		
	}
	if(Input_JS == 1)
	{		
		if(time > 999)                // 1秒定时时间到   
		{
			time = 0;
			JS_Time[0]++;
			if(JS_Time[0]>59)
			{
				JS_Time[0] = 0;JS_Time[1]++;
				if(JS_Time[1] > 59)
				{
					JS_Time[1] = 0; JS_Time[2]++;
					if(JS_Time[2]>23) JS_Time[2] = 0;
				}
			}	
			
		}
		LCD12864_DrowPicNum(0, 16, JS_Time[2]/10);                                  // 显示分
		LCD12864_DrowPicNum(16, 16, JS_Time[2]%10);
		LCD12864_DrowPicNum(32, 16, 10);                                              // 显示冒号：
		LCD12864_DrowPicNum(48, 16, JS_Time[1]/10);                                  // 显示时
		LCD12864_DrowPicNum(64, 16, JS_Time[1]%10);
		LCD12864_DrowPicNum(80, 16, 10);                                              // 显示冒号：
		LCD12864_DrowPicNum(96, 16, JS_Time[0]/10);                                  // 显示时
		LCD12864_DrowPicNum(112, 16, JS_Time[0]%10);
		if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 1 )
		{
			Delay_ms(20);
			if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 1)
			{
				while(K_UP == 0);                         // 等待按键松开
				ZJS_Status++;
				if(ZJS_Status==4)
				{
					ZJS_Status = 0;
				}
				if(ZJS_Status == 0)
				{
					LCD12864_DrowSet(0,0,16,16,54,1);LCD12864_DrowSet(16,0,16,16,55,1);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				if(ZJS_Status == 1)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,1);LCD12864_DrowSet(112,0,16,16,57,1);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				if(ZJS_Status == 2)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,1);LCD12864_DrowSet(16,48,16,16,59,1);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // 显示退出
				}
				if(ZJS_Status == 3)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // 显示开始
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // 显示停止
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // 显示复位
					LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);    // 显示退出
				}
			}
		}
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag != 0 && Input_JS != 0)
		{
			Delay_ms(20);
			if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag != 0 && Input_JS != 0)
			{
				if(ZJS_Status == 0)
				{
					TIM_Cmd(TIMx,ENABLE);  // 开启定时器
					time = 0;
				}
				if(ZJS_Status == 1)
				{
					TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
				}
				if(ZJS_Status == 2)
				{
					TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
					time = 0;
					JS_Time[0] = 0;
					JS_Time[1] = 0;
					JS_Time[2] = 0;
				}
				if(ZJS_Status == 3)
				{
					TIM_Cmd(TIMx,DISABLE);  // 关闭定时器
					time = 0;
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // 清除所有标志位
					JS_Time[2] = 0;JS_Time[1] = 0;JS_Time[0] = 0;
					LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
					LCD12864_Clear();                                                 // LCD12864清屏 字库方式
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}
				}
			}
		}			
	}
	/*
		选择调整时还是分还是秒
	*/
	if(Time_Flag == 1&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"♂");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");
		LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
		LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
		LCD12864_DrowSet(32,48,64,16,40,0);                                             // 显示/* <+  ->*/
	}
	if(Time_Flag == 2&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"  ");LCD12864_DisplayStrChin(2,3,"♂");LCD12864_DisplayStrChin(2,5,"  ");
		LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
		LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
		LCD12864_DrowSet(32,48,64,16,40,0);
	}
	if(Time_Flag == 3&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"  ");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"♂");
		LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
		LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
		LCD12864_DrowSet(32,48,64,16,40,0);                                               
	}
	if(Time_Flag == 4&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"  ");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");
		LCD12864_DrowSet(32,48,64,16,39,0);                                             // 显示/* <+♂->*/
		if(K_Right == 0)                                                   // 选择确定
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,48,16,16,29,1);LCD12864_DrowSet(16,48,16,16,30,1);           // 显示确定
				LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
				Adjust_Sure = 1;
			}
		}
		if(K_Left == 0)                                                   // 选择退出
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
				LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);         // 显示退出
				Adjust_Sure = 0;
			}
		}
	}
	
	
	if(Menu == 1 && Sure_Flag == 1)                                                       
	{		
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,36,0);LCD12864_DrowSet(64,16,16,16,37,0);LCD12864_DrowSet(96,16,16,16,38,0);                              // 显示时分秒
		LCD12864_SetDispTime(1,1,Now_Time[2]);LCD12864_SetDispTime(1,3,Now_Time[1]);LCD12864_SetDispTime(1,5,Now_Time[0]); // 将读到的时间数据转化为十进制
		if(Time_Flag == 0)
		{
			LCD12864_DisplayStrChin(2,1,"♂");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");Time_Flag = 1;
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
		  LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
			LCD12864_DrowSet(32,48,64,16,40,0);
		}
		/************调时***************/
		if(Time_Flag == 1)                     // 调时
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Now_Time[2] ++;
					if(Z10BCD(Now_Time[2])>0x23){Now_Time[2] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Z10BCD(Now_Time[2])==0){Now_Time[2] = BCDTO10(0x24);}
					Now_Time[2] -- ;
				}
			}
		}
		if(Time_Flag == 2)                     // 调分
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Now_Time[1] ++;
					if(Z10BCD(Now_Time[1])>0x59){Now_Time[1] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Z10BCD(Now_Time[1])==0){Now_Time[1] = BCDTO10(0x60);}
					Now_Time[1] -- ;
				}
			}			
		}
		if(Time_Flag == 3)                     // 调秒
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Now_Time[0] ++;
					if(Z10BCD(Now_Time[0])>0x59){Now_Time[0] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Z10BCD(Now_Time[0])==0){Now_Time[0] = BCDTO10(0x60);}
					Now_Time[0] -- ;
				}
			}			
		}
		/******************************/
		Adjust_Choose = 1;                                                                // 如果调时 Adjust_Choose = 1
	}
	if(Menu == 2 && Sure_Flag == 1)                                                      
	{
		LCD12864_DrowSet(32,0,16,16,11,0);LCD12864_DrowSet(48,0,16,16,12,0);LCD12864_DrowSet(64,0,16,16,13,0);LCD12864_DrowSet(80,0,16,16,14,0);
		LCD12864_DrowSet(32,16,16,16,33,0);LCD12864_DrowSet(64,16,16,16,34,0);LCD12864_DrowSet(96,16,16,16,35,0);                              // 显示年月日
		LCD12864_SetDispTime(1,1,Now_Date[3]);LCD12864_SetDispTime(1,3,Now_Date[2]);LCD12864_SetDispTime(1,5,Now_Date[1]); // 将读到的时间数据转化为十进制
		if(Time_Flag == 0)
		{
			LCD12864_DisplayStrChin(2,1,"♂");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");Time_Flag = 1;
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // 显示确定
		  LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // 显示退出
			LCD12864_DrowSet(32,48,64,16,40,0);
		}
		/**********调年月日***********/
		if(Time_Flag == 1)                     // 调年
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Now_Date[3] ++;
					if(Z10BCD(Now_Date[3])>0x99){Now_Date[3] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Z10BCD(Now_Date[3])==0){Now_Date[3] = BCDTO10(0x99);}
					Now_Date[3] -- ;
				}
			}
		}
		if(Time_Flag == 2)                     // 调月
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Now_Date[2] ++;
					if(Z10BCD(Now_Date[2])>0x12){Now_Date[2] = 1;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					Now_Date[2] -- ;
					if(Z10BCD(Now_Date[2])==0){Now_Date[2] = BCDTO10(0x12);}		
				}
			}
		}
		if(Time_Flag == 3)                     // 调日
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Now_Date[1] ++;
					if(Z10BCD(Now_Date[1])>0x31){Now_Date[1] = 1;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					Now_Date[1] -- ;
					if(Z10BCD(Now_Date[1])==0){Now_Date[1] = BCDTO10(0x31);}	
				}
			}
		}
		/****************************/
		Adjust_Choose = 2;                                                                // 如果调日期 Adjust_Choose = 2
	}
	
	if(Alarm_Flag == 1)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
		LCD12864_DrowSet(0,32,16,16,45,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 2)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,45,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 3)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,45,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 4)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
		LCD12864_DrowSet(0,32,16,16,46,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 5)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,46,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 6)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,46,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 7)
	{
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,43,0);
		if(K_Right == 0)                                                   // 选择确定
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(112,0,16,16,41,1);LCD12864_DrowSet(112,48,16,16,42,0);         // 显示开关
				Adjust_Alarm = 1;
			}
		}
		if(K_Left == 0)                                                   // 选择退出
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,1);         // 显示开关
				Adjust_Alarm = 0;
			}
		}
	}
	if(Menu == 3 && Sure_Flag == 2)                                                     
	{
		LCD12864_DrowSet(32,0,16,16,15,0);LCD12864_DrowSet(48,0,16,16,16,0);LCD12864_DrowSet(64,0,16,16,17,0);LCD12864_DrowSet(80,0,16,16,18,0);    // 显示闹钟
		
		LCD12864_DrowSet(16,16,16,16,33,0);LCD12864_DrowSet(48,16,16,16,34,0);LCD12864_DrowSet(80,16,16,16,35,0);                              // 显示年月日
		LCD12864_DrowSet(16,48,16,16,36,0);LCD12864_DrowSet(48,48,16,16,37,0);LCD12864_DrowSet(80,48,16,16,38,0);                              // 显示时分秒
		
		LCD12864_SetDispTime(1,0,Alarm_Read[5]);LCD12864_SetDispTime(1,2,Alarm_Read[4]);LCD12864_SetDispTime(1,4,Alarm_Read[3]); // 将读到的时间数据转化为十进制
		LCD12864_SetDispTime(3,0,Alarm_Read[2]);LCD12864_SetDispTime(3,2,Alarm_Read[1]);LCD12864_SetDispTime(3,4,Alarm_Read[0]); // 将读到的时间数据转化为十进制
		if(Alarm_Flag == 0)
		{
			LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0); // 显示开关
			LCD12864_DrowSet(0,32,16,16,45,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);			
			Alarm_Flag = 1;
		}
		if(Alarm_Flag == 1)                    // 调年
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Alarm_Read[5]++;
					if(Alarm_Read[5]>99) {Alarm_Read[5] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Alarm_Read[5]==0) {Alarm_Read[5] = 99;}
					Alarm_Read[5]--;
				}
			}
		}
		if(Alarm_Flag == 2)                    // 调月
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Alarm_Read[4]++;
					if(Alarm_Read[4]>12) {Alarm_Read[4] = 1;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					Alarm_Read[4]--;
					if(Alarm_Read[4]==0) {Alarm_Read[4] = 12;}					
				}
			}
		}
		if(Alarm_Flag == 3)                    // 调日
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Alarm_Read[3]++;
					if(Alarm_Read[3]>31) {Alarm_Read[3] = 1;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					Alarm_Read[3]--;
					if(Alarm_Read[3]==0) {Alarm_Read[3] = 31;}					
				}
			}
		}
		if(Alarm_Flag == 4)                    // 调时
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Alarm_Read[2]++;
					if(Alarm_Read[2]>23) {Alarm_Read[2] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Alarm_Read[2]==0) {Alarm_Read[2] = 24;}
					Alarm_Read[2]--;
				}
			}
		}
		if(Alarm_Flag == 5)                    // 调分
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Alarm_Read[1]++;
					if(Alarm_Read[1]>59) {Alarm_Read[1] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Alarm_Read[1]==0) {Alarm_Read[1] = 60;}
					Alarm_Read[1]--;
				}
			}
		}		
		if(Alarm_Flag == 6)                    // 调分
		{
			if(K_Right == 0)                     // +
			{
				Delay_ms(20);
				if(K_Right == 0)
				{
					while(K_Right == 0);
					Alarm_Read[0]++;
					if(Alarm_Read[0]>59) {Alarm_Read[0] = 0;}
				}
			}
			if(K_Left == 0)                     // -
			{
				Delay_ms(20);
				if(K_Left == 0)
				{
					while(K_Left == 0);
					if(Alarm_Read[0]==0) {Alarm_Read[0] = 60;}
					Alarm_Read[0]--;
				}
			}
		}		
	}
	
	if(Menu == 4 && Sure_Flag == 3 && Input_JS == 0) 
	{
		LCD12864_DrowPic(0,0,128,16,JustLoveWen);                        // 显示开机动画
		
		if(Count_Flag == 0)
		{
			LCD12864_DrowSet(32,16,16,16,52,1);LCD12864_DrowSet(48,16,16,16,48,1);LCD12864_DrowSet(64,16,16,16,50,1);LCD12864_DrowSet(80,16,16,16,51,1);  // 显示正计时		
			LCD12864_DrowSet(32,32,16,16,52,0);LCD12864_DrowSet(48,32,16,16,49,0);LCD12864_DrowSet(64,32,16,16,50,0);LCD12864_DrowSet(80,32,16,16,51,0);  // 显示倒计时
			
			LCD12864_DrowSet(0,16,16,16,41,0);
			LCD12864_DrowSet(112,16,16,16,42,0);         // 显示开关
			
			LCD12864_DrowSet(0,32,16,16,41,0);
			LCD12864_DrowSet(112,32,16,16,42,0);         // 显示开关
			
			Count_Flag = 1;
		}
		LCD12864_DrowSet(32,48,64,16,40,0);
	}

	if(Count_Flag == 1 && Input_JS == 0)
	{
		LCD12864_DrowSet(32,16,16,16,52,1);LCD12864_DrowSet(48,16,16,16,48,1);LCD12864_DrowSet(64,16,16,16,50,1);LCD12864_DrowSet(80,16,16,16,51,1);  // 显示正计时		
		LCD12864_DrowSet(32,32,16,16,52,0);LCD12864_DrowSet(48,32,16,16,49,0);LCD12864_DrowSet(64,32,16,16,50,0);LCD12864_DrowSet(80,32,16,16,51,0);  // 显示倒计时
		LCD12864_DrowSet(0,32,16,16,41,0);
		LCD12864_DrowSet(112,32,16,16,42,0);         // 显示开关
		if(K_Right == 0)                                                   // 选择确定
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,1);
				LCD12864_DrowSet(112,16,16,16,42,0);         // 显示开关
				
				LCD12864_DrowSet(0,32,16,16,41,0);
				LCD12864_DrowSet(112,32,16,16,42,0);         // 显示开关
				
				Z_F_Count = 1;                               // 开启正计时标志
			}
		}
		if(K_Left == 0)                                                   // 选择退出
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,0);
				LCD12864_DrowSet(112,16,16,16,42,1);         // 显示开关
				
				LCD12864_DrowSet(0,32,16,16,41,0);
				LCD12864_DrowSet(112,32,16,16,42,0);         // 显示开关	
				
				Z_F_Count = 0;                                // 退出计时模式
			}
		}
	}
	if(Count_Flag == 2 && Input_JS == 0)
	{
		LCD12864_DrowSet(32,16,16,16,52,0);LCD12864_DrowSet(48,16,16,16,48,0);LCD12864_DrowSet(64,16,16,16,50,0);LCD12864_DrowSet(80,16,16,16,51,0);  // 显示正计时		
		LCD12864_DrowSet(32,32,16,16,52,1);LCD12864_DrowSet(48,32,16,16,49,1);LCD12864_DrowSet(64,32,16,16,50,1);LCD12864_DrowSet(80,32,16,16,51,1);  // 显示倒计时
		LCD12864_DrowSet(0,16,16,16,41,0);
		LCD12864_DrowSet(112,16,16,16,42,0);         // 显示开关
		if(K_Right == 0)                                                   // 选择确定
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,0);
				LCD12864_DrowSet(112,16,16,16,42,0);         // 显示开关
				
				LCD12864_DrowSet(0,32,16,16,41,1);
				LCD12864_DrowSet(112,32,16,16,42,0);         // 显示开关
				
				Z_F_Count = 2;                               // 开启正计时标志
			}
		}
		if(K_Left == 0)                                                   // 选择退出
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,0);
				LCD12864_DrowSet(112,16,16,16,42,0);         // 显示开关
				
				LCD12864_DrowSet(0,32,16,16,41,0);
				LCD12864_DrowSet(112,32,16,16,42,1);         // 显示开关	
				
				Z_F_Count = 0;                                // 退出计时模式
			}
		}
	}	
	/*
		菜单显示
	*/
	if(Menu == 0 && Sure_Flag == 0) Clock_Basic_Disp();                                   // 做基本的显示
	if(Menu == 1 && Sure_Flag == 0)                                                       // 时间设置反显 ,其余正常显示
	{
		LCD12864_DisplayStrChin(0,0,"●");LCD12864_DisplayStrChin(0,7,"●");
		LCD12864_DisplayStrChin(3,0,"●");LCD12864_DisplayStrChin(3,7,"●");
		LCD12864_DisplayStrChin(1,0,"功");LCD12864_DisplayStrChin(2,0,"能");
		LCD12864_DisplayStrChin(1,7,"设");LCD12864_DisplayStrChin(2,7,"置");
		LCD12864_DrowSet(32,0,16,16,7,1);LCD12864_DrowSet(48,0,16,16,8,1);LCD12864_DrowSet(64,0,16,16,9,1);LCD12864_DrowSet(80,0,16,16,10,1);
		LCD12864_DrowSet(32,16,16,16,11,0);LCD12864_DrowSet(48,16,16,16,12,0);LCD12864_DrowSet(64,16,16,16,13,0);LCD12864_DrowSet(80,16,16,16,14,0);
		LCD12864_DrowSet(32,32,16,16,15,0);LCD12864_DrowSet(48,32,16,16,16,0);LCD12864_DrowSet(64,32,16,16,17,0);LCD12864_DrowSet(80,32,16,16,18,0);
		LCD12864_DrowSet(32,48,16,16,19,0);LCD12864_DrowSet(48,48,16,16,20,0);LCD12864_DrowSet(64,48,16,16,21,0);LCD12864_DrowSet(80,48,16,16,22,0);
	}
	if(Menu == 2 && Sure_Flag == 0)                                                      // 日期设置反显 ,其余正常显示
	{
		LCD12864_DisplayStrChin(0,0,"●");LCD12864_DisplayStrChin(0,7,"●");
		LCD12864_DisplayStrChin(3,0,"●");LCD12864_DisplayStrChin(3,7,"●");
		LCD12864_DisplayStrChin(1,0,"功");LCD12864_DisplayStrChin(2,0,"能");
		LCD12864_DisplayStrChin(1,7,"设");LCD12864_DisplayStrChin(2,7,"置");
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,11,1);LCD12864_DrowSet(48,16,16,16,12,1);LCD12864_DrowSet(64,16,16,16,13,1);LCD12864_DrowSet(80,16,16,16,14,1);
		LCD12864_DrowSet(32,32,16,16,15,0);LCD12864_DrowSet(48,32,16,16,16,0);LCD12864_DrowSet(64,32,16,16,17,0);LCD12864_DrowSet(80,32,16,16,18,0);
		LCD12864_DrowSet(32,48,16,16,19,0);LCD12864_DrowSet(48,48,16,16,20,0);LCD12864_DrowSet(64,48,16,16,21,0);LCD12864_DrowSet(80,48,16,16,22,0);
	}
	if(Menu == 3 && Sure_Flag == 0)                                                      // 闹钟设置反显 ,其余正常显示
	{
		LCD12864_DisplayStrChin(0,0,"●");LCD12864_DisplayStrChin(0,7,"●");
		LCD12864_DisplayStrChin(3,0,"●");LCD12864_DisplayStrChin(3,7,"●");
		LCD12864_DisplayStrChin(1,0,"功");LCD12864_DisplayStrChin(2,0,"能");
		LCD12864_DisplayStrChin(1,7,"设");LCD12864_DisplayStrChin(2,7,"置");
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,11,0);LCD12864_DrowSet(48,16,16,16,12,0);LCD12864_DrowSet(64,16,16,16,13,0);LCD12864_DrowSet(80,16,16,16,14,0);
		LCD12864_DrowSet(32,32,16,16,15,1);LCD12864_DrowSet(48,32,16,16,16,1);LCD12864_DrowSet(64,32,16,16,17,1);LCD12864_DrowSet(80,32,16,16,18,1);
		LCD12864_DrowSet(32,48,16,16,19,0);LCD12864_DrowSet(48,48,16,16,20,0);LCD12864_DrowSet(64,48,16,16,21,0);LCD12864_DrowSet(80,48,16,16,22,0);
	}
	
	if(Menu == 4 && Sure_Flag == 0)                                                     // 闹钟设置反显 ,其余正常显示
	{
		LCD12864_DisplayStrChin(0,0,"●");LCD12864_DisplayStrChin(0,7,"●");
		LCD12864_DisplayStrChin(3,0,"●");LCD12864_DisplayStrChin(3,7,"●");
		LCD12864_DisplayStrChin(1,0,"功");LCD12864_DisplayStrChin(2,0,"能");
		LCD12864_DisplayStrChin(1,7,"设");LCD12864_DisplayStrChin(2,7,"置");
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,11,0);LCD12864_DrowSet(48,16,16,16,12,0);LCD12864_DrowSet(64,16,16,16,13,0);LCD12864_DrowSet(80,16,16,16,14,0);
		LCD12864_DrowSet(32,32,16,16,15,0);LCD12864_DrowSet(48,32,16,16,16,0);LCD12864_DrowSet(64,32,16,16,17,0);LCD12864_DrowSet(80,32,16,16,18,0);
		LCD12864_DrowSet(32,48,16,16,19,1);LCD12864_DrowSet(48,48,16,16,20,1);LCD12864_DrowSet(64,48,16,16,21,1);LCD12864_DrowSet(80,48,16,16,22,1);
	}
}

/*
	控制LCD背光按键
*/
void LCD_Control_BK(void)
{
		if(K_Bk == 0)
		{
			Delay_ms(20);
			if(K_Bk == 0)
			{
				while(K_Bk == 0);
				LED_BACK = ~LED_BACK;
			}
		}
}

/*
	判断闹钟是否到时间闹钟函数
*/
void Set_Alarm(void)
{
	// 表示闹钟时间到
	if(Z10BCD(Alarm_Read[5])==Get_Time[6] && Z10BCD(Alarm_Read[4])==Get_Time[5] && Z10BCD(Alarm_Read[3])==Get_Time[4] && Z10BCD(Alarm_Read[2])==Get_Time[2] && Z10BCD(Alarm_Read[1])==Get_Time[1] && Z10BCD(Alarm_Read[0])==Get_Time[0])  
	{
		/*
			这里可以写闹钟时间到的执行函数
		*/
		AT24C32_WriteOneByte(0x0007,0);	                                  // 自动关闭闹钟
		LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
		LCD12864_Clear();                                                 // LCD12864清屏 字库方式		
		
		LCD12864_DisplayStrChin(0,0,"    时间到了    ");
		Delay_ms(3000);                                                   // 延时，用于开机动画的显示时间

		LCD12864_DrawClear();                                             // LCD12864清屏 画点方式
		LCD12864_Clear();                                                 // LCD12864清屏 字库方式		
		
		LCD12864_DrowSet(96,16,32,16,24,0);
	}
}












