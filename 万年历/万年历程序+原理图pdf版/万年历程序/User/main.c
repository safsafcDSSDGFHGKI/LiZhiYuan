/*-----------------------------------------------------------------------
΢�Ź��ں�        			 	: ���ĵ���

����                           	: ����ǿ
	
������                      		��LCD12864������-����ʱ�� V2.0.0
                                  
��д����                        	��2019��5��27��
����޸�����                  	��2019��6��1��
QQ                              ��1547791594
΢��                           	: wcq931224

QQȺ							: 760338114
΢�Ź��ں�                      	: ���ĵ���    ��ע���ںŻ�ȡ������Դ
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


uint8_t Z10BCD( uint8_t date);                                     // ʮ����תBCD��
uint8_t BCDTO10( uint8_t date );                                   // BCD��תʮ����
void Clock_Basic_Disp(void);                                       // ������������ʾ
void KEY_Timing(void);                                             // ������ʱ����
void LCD_Control_BK(void);                                         // �������Ʊ���
void Set_Alarm(void);                                              // �ж������Ƿ񵽺���

extern char *TianGan,*DiZhi,*ShengXiao,*RiLi,*YueLi;

uint8_t Time_Init[7]  = {0x00,0x23,0x10,0x05,0x28,0x05,0x19};       // �� �� ʱ ���� �� �� �� ��ʼ��   01��Ӧ������~07��Ӧ������
uint8_t Get_Time[7];                                                // ��ȡʱ������
uint8_t Get_Temp[2];                                                // ��ȡ�¶����� 
uint8_t Now_Time[3] ={0x00};                                        // ���ڴ�Ŷ�ȡ��ǰ��ʱ�����
uint8_t Now_Date[4];
uint8_t Alarm_State = 0;
uint8_t Alarm_Data[3];

                                            
uint8_t temperatureh,temperaturel;  	                              // ���DHT11�¶�ֵ  
uint8_t humidityh,humidityl;                                        // ���DHT11ʪ��ֵ 
uint8_t DHT11_N_P;                                                  // �ж�DHT11�������¶�ֵ���ڻ���С��0

uint8_t Alarm_Read[6];                                              // ����AT24C32���ݣ��������
uint8_t Alarm_Write[6] = {1,2,3,4,5,6};                             // д��AT24C32����
 
uint16_t time = 0;                                                  // ��ʱ��ʱ�����

int main(void)
{
	LCD12864_Init();                                                  // LCD12864��ʼ��
	DHT11_Init();                                                     // DHT11��ʼ�� 
	IIC_GPIO_Config();	                                              // IIC���ų�ʼ��

	LCD12864_LED_BACK();                                              // �����������
	LCD12864_KEY_Congigure();                                         // �������ó�ʼ��

	LED_BACK = 1;
	LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
	LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ	

	LCD12864_DrowPic(0,0,128,64,KaiJiDongHua);                        // ��ʾ��������
	
	Delay_ms(3000);                                                   // ��ʱ�����ڿ�����������ʾʱ��
 	LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
	LCD12864_Clear(); 
	
//	IIC_WriteMultiByte(Time_Init,0x00,7);                             // ���趨������д�뵽DS3231�� 
//	AT24C32_PageWrite(0x0000,Alarm_Write,6);
	
//	Exit_Configure();                                                 // �ⲿ�жϳ�ʼ��
//	NVIC_Configure();                                                 // NVIC����                (�ŵ�����ʼ����ֹ�ϵ��Ǳ�����ư���)
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
	NVIC_Configure();                                                 // �жϷ�����
	BasicTime_Init();                                                 // ��ʱ����ʼ��
	USART1_Init(115200);                    // ����1��ʼ��
	while(1)
	{
		DHT11_Read_Data(&temperatureh,&temperaturel,&humidityh,&humidityl,&DHT11_N_P);	// ��ȡ��ʪ��ֵ	
		IIC_ReadMultiByte(Get_Time,0x00,7);                                             // ��ȡDS3231��ʱ�������
		Clock_Basic_Disp();                                                             // ������������ʾ
		KEY_Timing();                                                                   // �жϰ���
		LCD_Control_BK();                                                     // �������
		Set_Alarm();
	}
}

/*-----------------------------------------------------------------------
Clock_Basic_Disp   				      �� ������������ʾ

�������                      		�� 
				    

��д����                        	��2019��1��29��
����޸�����                  		��2019��1��29��
-----------------------------------------------------------------------*/
void Clock_Basic_Disp(void)
{
	uint8_t Date[8];
	
	
	GetChinaCalendar(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4]),Date);       // �õ�ũ������
	Get_TianGan_DiZhi_ShengXiao(2000+Date[1],Date[2],Date[3]);                                        // ����Ҫ����ũ�����꣬��ȡ��ɣ���ַ����Ф������������

	
	LCD12864_Disp_Data(0,0,BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4]));	    // ��ʾ����	
	LCD12864_DisplayFlaotInt(2,6,BCDTO10(Get_Time[0]));                           // ��ʾ��
	LCD12864_DrowPicNum(64, 16, Get_Time[1]/16);                                  // ��ʾ��
	LCD12864_DrowPicNum(80, 16, Get_Time[1]%16);
	LCD12864_DrowPicNum(48, 16, 10);                                              // ��ʾð�ţ�
	LCD12864_DrowPicNum(16, 16, Get_Time[2]/16);                                  // ��ʾʱ
	LCD12864_DrowPicNum(32, 16, Get_Time[2]%16);

	switch(Judge_Week(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4])))              // switch����ж������ڼ�
	{
		case 1: LCD12864_DrowWeek(96, 0, 32, 16, 0);/*LCD12864_DisplayStrChin(1 ,6,"�Ҹ�");*/ break;
		case 2: LCD12864_DrowWeek(96, 0, 32, 16, 1);/*LCD12864_DisplayStrChin(1 ,6,"����");*/ break;
		case 3: LCD12864_DrowWeek(96, 0, 32, 16, 2);/*LCD12864_DisplayStrChin(1 ,6,"����");*/ break;
		case 4: LCD12864_DrowWeek(96, 0, 32, 16, 3);/*LCD12864_DisplayStrChin(1 ,6,"����");*/ break;
		case 5: LCD12864_DrowWeek(96, 0, 32, 16, 4);/*LCD12864_DisplayStrChin(1 ,6,"Ŭ��");*/ break;
		case 6: LCD12864_DrowWeek(96, 0, 32, 16, 5);/*LCD12864_DisplayStrChin(1 ,6,"�ܶ�");*/ break;
		case 7: LCD12864_DrowWeek(96, 0, 32, 16, 6);/*LCD12864_DisplayStrChin(1 ,6,"����");*/ break;
	}	

	if(Festival_Yearly(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4])) == 0)
	{
			if(BCDTO10(Get_Time[0]) % 6 < 3)                                              // ��ʪ�ȣ�ũ�����ڣ����� 3���л�һ��
			{
				LCD12864_Disp_Temp(3,4,temperatureh,DHT11_N_P);
				LCD12864_DisplayStrChin(3 ,0,TianGan); 
				LCD12864_DisplayStrChin(3 ,1,DiZhi);
				LCD12864_DisplayStrChin(3 ,2,ShengXiao);
				LCD12864_DisplayStrChin(3 ,3,"��");	
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
			if(BCDTO10(Get_Time[0]) % 9 < 3)                                              // ��ʪ��3���л�һ��
			{
				LCD12864_Disp_Temp(3,4,temperatureh,DHT11_N_P);
				LCD12864_DisplayStrChin(3 ,0,TianGan); 
				LCD12864_DisplayStrChin(3 ,1,DiZhi);
				LCD12864_DisplayStrChin(3 ,2,ShengXiao);
				LCD12864_DisplayStrChin(3 ,3,"��");	
			}
			else if(BCDTO10(Get_Time[0]) % 9 >= 6) 
			{
				Return_Festival(Festival_Yearly(2000+BCDTO10(Get_Time[6]),BCDTO10(Get_Time[5]),BCDTO10(Get_Time[4])));        // ����ֵ�ж�����һ������				
			}	
			else
			{
				LCD12864_Dis_humid(3,4,humidityh);
				LCD12864_DisplayStrChin(3 ,0,YueLi); 
				LCD12864_DisplayStrChin(3 ,2,RiLi);
			}
	}

}


uint8_t Z10BCD( uint8_t date)    //ʮ����תBCD��
{
   uint8_t i,j;
   i=date/10;
   j=date-(i*10);
    i=(i<<4)|j;  
   return (i);
}
uint8_t BCDTO10( uint8_t date )   //BCD��ת10����
{
 uint8_t i,j;
 i=(date & 0xf0)>>4 ;
 j=date & 0x0f ;
 i=i*10+j;
 return i;
}

uint8_t Menu = 0;                       // ����˵�����
uint8_t Sure_Flag = 0;                  // ȷ�������µı�־λ
uint8_t Time_Flag = 0;     
uint8_t Adjust_Sure = 0,Adjust_Choose = 0;        // ����ȷ�������˳���־
uint8_t Alarm_Flag = 0;                 // ���ӱ�־λ
uint8_t Adjust_Alarm = 0;                 // ȷ�����û�ͻ���������ӱ�־
uint8_t Count_Flag = 0;                   // ��������־λ
uint8_t Z_F_Count = 0;                    // �ж�����ʱ���Ǹ���ʱ
uint8_t Input_JS = 0;                     // �����ʱ��־λ
uint8_t JS_Time[3] = {0};                 // ����ʱ���ŵ������� JS_Time[2]:ʱ JS_Time[1]:�� JS_Time[0]:�� 
uint8_t ZJS_Status = 0;
uint8_t DJS_Flag = 0,DJS_Flag1 = 0,DJS_Flag2 = 0;                     // �ж��Ƿ���뵹��ʱ��־
uint8_t DJS_Rest = 0;
uint8_t DJS_RestAyyr[3];
uint8_t DJS_Stop = 0;
void KEY_Timing(void)
{
	/*
		ѡ�񰴼� 
	*/ 
	if(K_UP == 0 && Sure_Flag == 0 && Input_JS == 0 )
	{
		Delay_ms(20);
		if(K_UP == 0 && Sure_Flag == 0 && Input_JS == 0 )
		{
			while(K_UP == 0);                         // �ȴ������ɿ�
			Menu++;
			if(Menu==1){LCD12864_DrawClear();LCD12864_Clear();}
			if(Menu==5)
			{
				Menu = 0; 
				LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
				LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ	
				
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
			while(K_UP == 0);                         // �ȴ������ɿ�
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
			while(K_UP == 0);                         // �ȴ������ɿ�
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
			while(K_UP == 0);                         // �ȴ������ɿ�
			Count_Flag++;
			if(Count_Flag==3)
			{
				Count_Flag = 1;
			}
		}
	}	
	

	/*
		ȷ������
	*/
	if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0)                                            // && Menu !=0 ��Ϊ����������ʾ״̬�� ��ֹ���´˼�
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0)
		{
			while(K_Down == 0); 
			LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
			LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ	
			if(Sure_Flag == 0)
			{
				if(Menu == 1)
				{
					Sure_Flag = 1;
					IIC_ReadMultiByte(Now_Time,0x00,3);// ���Ҫ����ʱ�䣬��Ҫ�ѵ�ǰ��ʱ�������
					Now_Time[0] = BCDTO10(Now_Time[0]);Now_Time[1] = BCDTO10(Now_Time[1]);Now_Time[2] = BCDTO10(Now_Time[2]);
				}                
				if(Menu == 2)
				{
					Sure_Flag = 1;
					IIC_ReadMultiByte(Now_Date,0x03,4);// ���Ҫ�������ڣ���Ҫ�ѵ�ǰ�����ڶ�����
					Now_Date[0] = BCDTO10(Now_Date[0]);Now_Date[1] = BCDTO10(Now_Date[1]);Now_Date[2] = BCDTO10(Now_Date[2]);Now_Date[3] = BCDTO10(Now_Date[3]);
				}
				if(Menu == 3)
				{
					Sure_Flag = 2;                     // �������ӱ�־
					AT24C32_PageRead(0x0000,Alarm_Read,6);
				}
				if(Menu == 4)
				{
					Sure_Flag = 3;                     // �����ʱģʽ
				}
			}
	
		}
	}
	if(K_Down == 0 && Menu !=0 && Time_Flag == 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0 )                                            // && Menu !=0 ��Ϊ����������ʾ״̬�� ��ֹ���´˼�
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag == 4 && Alarm_Flag != 7 && Count_Flag == 0 && Input_JS == 0 )
		{
			while(K_Down == 0);
			
			/*
				ȷ����ʱ
			*/
			if(Adjust_Choose == 1)                                            
			{
				if(Adjust_Sure == 1)                                               // ���ѡ����ȷ����д�뵽DS3231ʱ���ڷ��ص���ʾ����
				{
					Now_Time[0] = Z10BCD(Now_Time[0]);Now_Time[1] = Z10BCD(Now_Time[1]);Now_Time[2] = Z10BCD(Now_Time[2]);
					IIC_WriteMultiByte(Now_Time,0x00,3);                              // д��ʱ�䵽DS3231�Ĵ���
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
					LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
					LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ	
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}
				}
				else                                                                // ���ѡ�����˳���ֱ�ӷ��ص���ʾ����
				{
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
					LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
					LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
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
				ȷ��������
			*/
			if(Adjust_Choose == 2)  
			{
				if(Adjust_Sure == 1)                                               // ���ѡ����ȷ����д�뵽DS3231ʱ���ڷ��ص���ʾ����
				{
					Now_Date[0] = Z10BCD(Now_Date[0]);Now_Date[1] = Z10BCD(Now_Date[1]);Now_Date[2] = Z10BCD(Now_Date[2]);Now_Date[3] = Z10BCD(Now_Date[3]);
					IIC_WriteMultiByte(Now_Date,0x03,4);                              // д��ʱ�䵽DS3231�Ĵ���
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
					LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
					LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ	
					if(AT24C32_ReadOneByte(0x0007) == 1)
					{
						LCD12864_DrowSet(96,16,32,16,23,0);
					}
					if(AT24C32_ReadOneByte(0x0007) == 0)
					{
						LCD12864_DrowSet(96,16,32,16,24,0);
					}
				}
				else                                                                // ���ѡ�����˳���ֱ�ӷ��ص���ʾ����
				{
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
					LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
					LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ		
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
	
	if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag == 7 && Count_Flag == 0 && Input_JS == 0)                                            // && Menu !=0 ��Ϊ����������ʾ״̬�� ��ֹ���´˼�
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag == 7 && Count_Flag == 0 && Input_JS == 0)
		{
			while(K_Down == 0);
			if(Adjust_Alarm == 0)                                                  // �ر�����
			{
				AT24C32_WriteOneByte(0x0007,0);
				Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
				LCD12864_DrawClear();                                                      // LCD12864���� ���㷽ʽ
				LCD12864_Clear();                                                          // LCD12864���� �ֿⷽʽ	
				if(AT24C32_ReadOneByte(0x0007) == 1)
				{
					LCD12864_DrowSet(96,16,32,16,23,0);
				}
				if(AT24C32_ReadOneByte(0x0007) == 0)
				{
					LCD12864_DrowSet(96,16,32,16,24,0);
				}			
			}
			else                                                                  // ��������
			{				
				AT24C32_WriteOneByte(0x0007,1);			                       // �����úõ�����д��AT24C32 
				Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
				LCD12864_DrawClear();                                                      // LCD12864���� ���㷽ʽ
				LCD12864_Clear();                                                          // LCD12864���� �ֿⷽʽ
				AT24C32_PageWrite(0x0000,Alarm_Read,7);	
				LCD12864_DrowSet(96,16,32,16,23,0);	
			}
		}
	}
	
	if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag != 0 && Input_JS == 0 )                                            // && Menu !=0 ��Ϊ����������ʾ״̬�� ��ֹ���´˼�
	{
		Delay_ms(20);
		if(K_Down == 0 && Menu !=0 && Time_Flag != 4 && Alarm_Flag != 7 && Count_Flag != 0 && Input_JS == 0)
		{
			while(K_Down == 0);
			if(Z_F_Count == 0)                                                  // �˳���ʱ 
			{
				Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
				LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
				LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
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
			else if(Z_F_Count == 1)                                             // ��������ʱ
			{				
				LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
				LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
				LCD12864_DrowSet(48,0,16,16,50,0);	LCD12864_DrowSet(64,0,16,16,51,0);	   // ��ʾ��ʱ
				LCD12864_DrowSet(32,48,64,16,53,0);	
				
				if(ZJS_Status == 0)
				{
					LCD12864_DrowSet(0,0,16,16,54,1);LCD12864_DrowSet(16,0,16,16,55,1);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				Input_JS = 1;
//				TIM_Cmd(TIMx,ENABLE);           								// ������ʱ��
			}
			else if(Z_F_Count == 2)                                             // ���뵹��ʱ
			{
				LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
				LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
				Input_JS = 2;
			}
		}
	}
	if(Input_JS == 2 )
	{
		if(DJS_Flag1 == 0 ){LCD12864_DrowSet(16,0,16,16,9,0);LCD12864_DrowSet(32,0,16,16,10,0);LCD12864_DrowSet(48,0,16,16,60,0);LCD12864_DrowSet(64,0,16,16,61,0);LCD12864_DrowSet(80,0,16,16,7,0);LCD12864_DrowSet(96,0,16,16,8,0);} // ���ö�ʱʱ��
		
		if(ZJS_Status == 0 && DJS_Flag1 == 0 )
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,1);                                  // ��ʾ��  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,1);
			LCD12864_DrowPicNum(32, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,0);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,0);
			LCD12864_DrowPicNum(80, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,0);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,0);
			
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
			LCD12864_DrowSet(32,48,64,16,40,0);                                             // ��ʾ/* <+  ->*/
		}
		if(ZJS_Status == 1 && DJS_Flag1 == 0)
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,0);                                  // ��ʾ��  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,0);
			LCD12864_DrowPicNum(32, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,1);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,1);
			LCD12864_DrowPicNum(80, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,0);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,0);
			
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
			LCD12864_DrowSet(32,48,64,16,40,0);                                             // ��ʾ/* <+  ->*/
		}
		if(ZJS_Status == 2 && DJS_Flag1 == 0)
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,0);                                  // ��ʾ��  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,0);
			LCD12864_DrowPicNum(32, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,0);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,0);
			LCD12864_DrowPicNum(80, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,1);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,1);
			
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
			LCD12864_DrowSet(32,48,64,16,40,0);                                             // ��ʾ/* <+  ->*/
		}
		if(ZJS_Status == 3 && DJS_Flag1 == 0)
		{
			LCD12864_DrowPicNumX(0, 16, JS_Time[2]/10,0);                                  // ��ʾ��  
			LCD12864_DrowPicNumX(16, 16, JS_Time[2]%10,0);
			LCD12864_DrowPicNum(32, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(48, 16, JS_Time[1]/10,0);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(64, 16, JS_Time[1]%10,0);
			LCD12864_DrowPicNum(80, 16, 10);                                              // ��ʾð�ţ�
			LCD12864_DrowPicNumX(96, 16, JS_Time[0]/10,0);                                  // ��ʾʱ
			LCD12864_DrowPicNumX(112, 16, JS_Time[0]%10,0);
			
//			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
//			LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
			LCD12864_DrowSet(32,48,64,16,39,0);                                             // ��ʾ/* <+��->*/
		}
		if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 0)
		{
			Delay_ms(20);
			if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 0)
			{
				while(K_UP == 0);                         // �ȴ������ɿ�
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
					LCD12864_DrowSet(0,48,16,16,29,1);LCD12864_DrowSet(16,48,16,16,30,1);           // ��ʾȷ��
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
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
					LCD12864_DrowSet(0,48,16,16,29,1);LCD12864_DrowSet(16,48,16,16,30,1);           // ��ʾȷ��
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
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
					LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
					LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);         // ��ʾ�˳�
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
						Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0; DJS_Flag = 0;ZJS_Status=0; // ������б�־λ
						LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
						LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
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
						LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
						LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
						LCD12864_DrowSet(48,0,16,16,50,0);	LCD12864_DrowSet(64,0,16,16,51,0);	   // ��ʾ��ʱ
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
				LCD12864_DrowPicNum(0, 16, JS_Time[2]/10);                                  // ��ʾ��  uint8_t DJS_Rest = 0;uint8_t DJS_RestAyyr[3];
				LCD12864_DrowPicNum(16, 16, JS_Time[2]%10);
				LCD12864_DrowPicNum(32, 16, 10);                                              // ��ʾð�ţ�
				LCD12864_DrowPicNum(48, 16, JS_Time[1]/10);                                  // ��ʾʱ
				LCD12864_DrowPicNum(64, 16, JS_Time[1]%10);
				LCD12864_DrowPicNum(80, 16, 10);                                              // ��ʾð�ţ�
				LCD12864_DrowPicNum(96, 16, JS_Time[0]/10);                                  // ��ʾʱ  
				LCD12864_DrowPicNum(112, 16, JS_Time[0]%10);	
				
				if(time > 999)                // 1�붨ʱʱ�䵽   
				{
					time = 0;
					
					if(JS_Time[0]==0)
					{
						JS_Time[0] = 60;
						if(JS_Time[1] == 0)
						{
							JS_Time[1] = 60; 
							if(JS_Time[2]==0 && JS_Time[1]==0 && JS_Time[0]== 0)         // ����ʱʱ�䵽
							{
								TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
							}
							JS_Time[2]--;
						}
						JS_Time[1]--;
					}	
					JS_Time[0]--;					
					if(JS_Time[2]==0 && JS_Time[1]==0 && JS_Time[0]== 0)         // ����ʱʱ�䵽
					{
						TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
						DJS_Stop = 1;
						LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
						LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
						LCD12864_DisplayStrChin(0,0,"����ʱʱ�䵽�ˣ�");
						Delay_ms(3000);                                                   // ��ʱ�����ڿ�����������ʾʱ��

						LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
						LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ	
						LCD12864_DrowSet(48,0,16,16,50,0);	LCD12864_DrowSet(64,0,16,16,51,0);	   // ��ʾ��ʱ
						LCD12864_DrowSet(32,48,64,16,53,0);	
					}
				}

				if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 1)
				{
					Delay_ms(20);
					if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 2 && DJS_Flag1 == 1)
					{
						while(K_UP == 0);                         // �ȴ������ɿ�
						DJS_Flag2++;
						if(DJS_Flag2 == 4)
						{
							DJS_Flag2 = 0;
						}
					}
				}
			
				if(DJS_Flag2 == 0)
				{
					LCD12864_DrowSet(0,0,16,16,54,1);LCD12864_DrowSet(16,0,16,16,55,1);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				if(DJS_Flag2 == 1)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,1);LCD12864_DrowSet(112,0,16,16,57,1);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				if(DJS_Flag2 == 2)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,1);LCD12864_DrowSet(16,48,16,16,59,1);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				if(DJS_Flag2 == 3)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);    // ��ʾ�˳�
				}
				
				if(K_Down == 0 &&  DJS_Flag1 == 1)
				{
					Delay_ms(20);
					if(K_Down == 0 &&  DJS_Flag1 == 1)
					{
						if(DJS_Flag2 == 0 && DJS_Stop == 0)
						{
							TIM_Cmd(TIMx,ENABLE);  // ������ʱ��
							time = 0;
						}
						if(DJS_Flag2 == 1)
						{
							TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
						}
						if(DJS_Flag2 == 2)
						{
							TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
							DJS_Stop = 0;
							time = 0;
							DJS_Rest = 0;
							JS_Time[2] = DJS_RestAyyr[2];JS_Time[1] = DJS_RestAyyr[1];JS_Time[0] = DJS_RestAyyr[0];
						}
						if(DJS_Flag2 == 3)
						{
							TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
							time = 0;
							Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;DJS_Flag1 = 0; DJS_Flag2 = 0; ZJS_Status = 0;DJS_Flag = 0;DJS_Stop = 0;DJS_Rest = 0;// ������б�־λ
							JS_Time[2] = 0;JS_Time[1] = 0;JS_Time[0] = 0;
							LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
							LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
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
		if(time > 999)                // 1�붨ʱʱ�䵽   
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
		LCD12864_DrowPicNum(0, 16, JS_Time[2]/10);                                  // ��ʾ��
		LCD12864_DrowPicNum(16, 16, JS_Time[2]%10);
		LCD12864_DrowPicNum(32, 16, 10);                                              // ��ʾð�ţ�
		LCD12864_DrowPicNum(48, 16, JS_Time[1]/10);                                  // ��ʾʱ
		LCD12864_DrowPicNum(64, 16, JS_Time[1]%10);
		LCD12864_DrowPicNum(80, 16, 10);                                              // ��ʾð�ţ�
		LCD12864_DrowPicNum(96, 16, JS_Time[0]/10);                                  // ��ʾʱ
		LCD12864_DrowPicNum(112, 16, JS_Time[0]%10);
		if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 1 )
		{
			Delay_ms(20);
			if(K_UP == 0 && Sure_Flag == 3 && Input_JS == 1)
			{
				while(K_UP == 0);                         // �ȴ������ɿ�
				ZJS_Status++;
				if(ZJS_Status==4)
				{
					ZJS_Status = 0;
				}
				if(ZJS_Status == 0)
				{
					LCD12864_DrowSet(0,0,16,16,54,1);LCD12864_DrowSet(16,0,16,16,55,1);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				if(ZJS_Status == 1)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,1);LCD12864_DrowSet(112,0,16,16,57,1);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				if(ZJS_Status == 2)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,1);LCD12864_DrowSet(16,48,16,16,59,1);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);    // ��ʾ�˳�
				}
				if(ZJS_Status == 3)
				{
					LCD12864_DrowSet(0,0,16,16,54,0);LCD12864_DrowSet(16,0,16,16,55,0);    // ��ʾ��ʼ
					LCD12864_DrowSet(96,0,16,16,56,0);LCD12864_DrowSet(112,0,16,16,57,0);    // ��ʾֹͣ
					
					LCD12864_DrowSet(0,48,16,16,58,0);LCD12864_DrowSet(16,48,16,16,59,0);    // ��ʾ��λ
					LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);    // ��ʾ�˳�
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
					TIM_Cmd(TIMx,ENABLE);  // ������ʱ��
					time = 0;
				}
				if(ZJS_Status == 1)
				{
					TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
				}
				if(ZJS_Status == 2)
				{
					TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
					time = 0;
					JS_Time[0] = 0;
					JS_Time[1] = 0;
					JS_Time[2] = 0;
				}
				if(ZJS_Status == 3)
				{
					TIM_Cmd(TIMx,DISABLE);  // �رն�ʱ��
					time = 0;
					Menu = 0;Sure_Flag = 0;Time_Flag = 0; Adjust_Sure = 0; Adjust_Alarm = 0;Alarm_Flag = 0;Z_F_Count = 0;Count_Flag = 0;Input_JS = 0;  // ������б�־λ
					JS_Time[2] = 0;JS_Time[1] = 0;JS_Time[0] = 0;
					LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
					LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ
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
		ѡ�����ʱ���Ƿֻ�����
	*/
	if(Time_Flag == 1&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"��");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");
		LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
		LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
		LCD12864_DrowSet(32,48,64,16,40,0);                                             // ��ʾ/* <+  ->*/
	}
	if(Time_Flag == 2&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"  ");LCD12864_DisplayStrChin(2,3,"��");LCD12864_DisplayStrChin(2,5,"  ");
		LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
		LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
		LCD12864_DrowSet(32,48,64,16,40,0);
	}
	if(Time_Flag == 3&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"  ");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"��");
		LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
		LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
		LCD12864_DrowSet(32,48,64,16,40,0);                                               
	}
	if(Time_Flag == 4&&(Menu == 1 || Menu == 2))
	{
		LCD12864_DisplayStrChin(2,1,"  ");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");
		LCD12864_DrowSet(32,48,64,16,39,0);                                             // ��ʾ/* <+��->*/
		if(K_Right == 0)                                                   // ѡ��ȷ��
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,48,16,16,29,1);LCD12864_DrowSet(16,48,16,16,30,1);           // ��ʾȷ��
				LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
				Adjust_Sure = 1;
			}
		}
		if(K_Left == 0)                                                   // ѡ���˳�
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
				LCD12864_DrowSet(96,48,16,16,31,1);LCD12864_DrowSet(112,48,16,16,32,1);         // ��ʾ�˳�
				Adjust_Sure = 0;
			}
		}
	}
	
	
	if(Menu == 1 && Sure_Flag == 1)                                                       
	{		
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,36,0);LCD12864_DrowSet(64,16,16,16,37,0);LCD12864_DrowSet(96,16,16,16,38,0);                              // ��ʾʱ����
		LCD12864_SetDispTime(1,1,Now_Time[2]);LCD12864_SetDispTime(1,3,Now_Time[1]);LCD12864_SetDispTime(1,5,Now_Time[0]); // ��������ʱ������ת��Ϊʮ����
		if(Time_Flag == 0)
		{
			LCD12864_DisplayStrChin(2,1,"��");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");Time_Flag = 1;
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
		  LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
			LCD12864_DrowSet(32,48,64,16,40,0);
		}
		/************��ʱ***************/
		if(Time_Flag == 1)                     // ��ʱ
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
		if(Time_Flag == 2)                     // ����
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
		if(Time_Flag == 3)                     // ����
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
		Adjust_Choose = 1;                                                                // �����ʱ Adjust_Choose = 1
	}
	if(Menu == 2 && Sure_Flag == 1)                                                      
	{
		LCD12864_DrowSet(32,0,16,16,11,0);LCD12864_DrowSet(48,0,16,16,12,0);LCD12864_DrowSet(64,0,16,16,13,0);LCD12864_DrowSet(80,0,16,16,14,0);
		LCD12864_DrowSet(32,16,16,16,33,0);LCD12864_DrowSet(64,16,16,16,34,0);LCD12864_DrowSet(96,16,16,16,35,0);                              // ��ʾ������
		LCD12864_SetDispTime(1,1,Now_Date[3]);LCD12864_SetDispTime(1,3,Now_Date[2]);LCD12864_SetDispTime(1,5,Now_Date[1]); // ��������ʱ������ת��Ϊʮ����
		if(Time_Flag == 0)
		{
			LCD12864_DisplayStrChin(2,1,"��");LCD12864_DisplayStrChin(2,3,"  ");LCD12864_DisplayStrChin(2,5,"  ");Time_Flag = 1;
			LCD12864_DrowSet(0,48,16,16,29,0);LCD12864_DrowSet(16,48,16,16,30,0);           // ��ʾȷ��
		  LCD12864_DrowSet(96,48,16,16,31,0);LCD12864_DrowSet(112,48,16,16,32,0);         // ��ʾ�˳�
			LCD12864_DrowSet(32,48,64,16,40,0);
		}
		/**********��������***********/
		if(Time_Flag == 1)                     // ����
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
		if(Time_Flag == 2)                     // ����
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
		if(Time_Flag == 3)                     // ����
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
		Adjust_Choose = 2;                                                                // ��������� Adjust_Choose = 2
	}
	
	if(Alarm_Flag == 1)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
		LCD12864_DrowSet(0,32,16,16,45,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 2)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,45,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 3)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,45,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 4)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
		LCD12864_DrowSet(0,32,16,16,46,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 5)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,46,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 6)
	{
		LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,46,0);
		LCD12864_DrowSet(112,16,16,32,44,0); 
	}
	if(Alarm_Flag == 7)
	{
		LCD12864_DrowSet(0,32,16,16,47,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);
		LCD12864_DrowSet(112,16,16,32,43,0);
		if(K_Right == 0)                                                   // ѡ��ȷ��
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(112,0,16,16,41,1);LCD12864_DrowSet(112,48,16,16,42,0);         // ��ʾ����
				Adjust_Alarm = 1;
			}
		}
		if(K_Left == 0)                                                   // ѡ���˳�
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,1);         // ��ʾ����
				Adjust_Alarm = 0;
			}
		}
	}
	if(Menu == 3 && Sure_Flag == 2)                                                     
	{
		LCD12864_DrowSet(32,0,16,16,15,0);LCD12864_DrowSet(48,0,16,16,16,0);LCD12864_DrowSet(64,0,16,16,17,0);LCD12864_DrowSet(80,0,16,16,18,0);    // ��ʾ����
		
		LCD12864_DrowSet(16,16,16,16,33,0);LCD12864_DrowSet(48,16,16,16,34,0);LCD12864_DrowSet(80,16,16,16,35,0);                              // ��ʾ������
		LCD12864_DrowSet(16,48,16,16,36,0);LCD12864_DrowSet(48,48,16,16,37,0);LCD12864_DrowSet(80,48,16,16,38,0);                              // ��ʾʱ����
		
		LCD12864_SetDispTime(1,0,Alarm_Read[5]);LCD12864_SetDispTime(1,2,Alarm_Read[4]);LCD12864_SetDispTime(1,4,Alarm_Read[3]); // ��������ʱ������ת��Ϊʮ����
		LCD12864_SetDispTime(3,0,Alarm_Read[2]);LCD12864_SetDispTime(3,2,Alarm_Read[1]);LCD12864_SetDispTime(3,4,Alarm_Read[0]); // ��������ʱ������ת��Ϊʮ����
		if(Alarm_Flag == 0)
		{
			LCD12864_DrowSet(112,0,16,16,41,0);LCD12864_DrowSet(112,48,16,16,42,0); // ��ʾ����
			LCD12864_DrowSet(0,32,16,16,45,0);LCD12864_DrowSet(32,32,16,16,47,0);LCD12864_DrowSet(64,32,16,16,47,0);			
			Alarm_Flag = 1;
		}
		if(Alarm_Flag == 1)                    // ����
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
		if(Alarm_Flag == 2)                    // ����
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
		if(Alarm_Flag == 3)                    // ����
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
		if(Alarm_Flag == 4)                    // ��ʱ
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
		if(Alarm_Flag == 5)                    // ����
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
		if(Alarm_Flag == 6)                    // ����
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
		LCD12864_DrowPic(0,0,128,16,JustLoveWen);                        // ��ʾ��������
		
		if(Count_Flag == 0)
		{
			LCD12864_DrowSet(32,16,16,16,52,1);LCD12864_DrowSet(48,16,16,16,48,1);LCD12864_DrowSet(64,16,16,16,50,1);LCD12864_DrowSet(80,16,16,16,51,1);  // ��ʾ����ʱ		
			LCD12864_DrowSet(32,32,16,16,52,0);LCD12864_DrowSet(48,32,16,16,49,0);LCD12864_DrowSet(64,32,16,16,50,0);LCD12864_DrowSet(80,32,16,16,51,0);  // ��ʾ����ʱ
			
			LCD12864_DrowSet(0,16,16,16,41,0);
			LCD12864_DrowSet(112,16,16,16,42,0);         // ��ʾ����
			
			LCD12864_DrowSet(0,32,16,16,41,0);
			LCD12864_DrowSet(112,32,16,16,42,0);         // ��ʾ����
			
			Count_Flag = 1;
		}
		LCD12864_DrowSet(32,48,64,16,40,0);
	}

	if(Count_Flag == 1 && Input_JS == 0)
	{
		LCD12864_DrowSet(32,16,16,16,52,1);LCD12864_DrowSet(48,16,16,16,48,1);LCD12864_DrowSet(64,16,16,16,50,1);LCD12864_DrowSet(80,16,16,16,51,1);  // ��ʾ����ʱ		
		LCD12864_DrowSet(32,32,16,16,52,0);LCD12864_DrowSet(48,32,16,16,49,0);LCD12864_DrowSet(64,32,16,16,50,0);LCD12864_DrowSet(80,32,16,16,51,0);  // ��ʾ����ʱ
		LCD12864_DrowSet(0,32,16,16,41,0);
		LCD12864_DrowSet(112,32,16,16,42,0);         // ��ʾ����
		if(K_Right == 0)                                                   // ѡ��ȷ��
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,1);
				LCD12864_DrowSet(112,16,16,16,42,0);         // ��ʾ����
				
				LCD12864_DrowSet(0,32,16,16,41,0);
				LCD12864_DrowSet(112,32,16,16,42,0);         // ��ʾ����
				
				Z_F_Count = 1;                               // ��������ʱ��־
			}
		}
		if(K_Left == 0)                                                   // ѡ���˳�
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,0);
				LCD12864_DrowSet(112,16,16,16,42,1);         // ��ʾ����
				
				LCD12864_DrowSet(0,32,16,16,41,0);
				LCD12864_DrowSet(112,32,16,16,42,0);         // ��ʾ����	
				
				Z_F_Count = 0;                                // �˳���ʱģʽ
			}
		}
	}
	if(Count_Flag == 2 && Input_JS == 0)
	{
		LCD12864_DrowSet(32,16,16,16,52,0);LCD12864_DrowSet(48,16,16,16,48,0);LCD12864_DrowSet(64,16,16,16,50,0);LCD12864_DrowSet(80,16,16,16,51,0);  // ��ʾ����ʱ		
		LCD12864_DrowSet(32,32,16,16,52,1);LCD12864_DrowSet(48,32,16,16,49,1);LCD12864_DrowSet(64,32,16,16,50,1);LCD12864_DrowSet(80,32,16,16,51,1);  // ��ʾ����ʱ
		LCD12864_DrowSet(0,16,16,16,41,0);
		LCD12864_DrowSet(112,16,16,16,42,0);         // ��ʾ����
		if(K_Right == 0)                                                   // ѡ��ȷ��
		{
			Delay_ms(20);
			if(K_Right == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,0);
				LCD12864_DrowSet(112,16,16,16,42,0);         // ��ʾ����
				
				LCD12864_DrowSet(0,32,16,16,41,1);
				LCD12864_DrowSet(112,32,16,16,42,0);         // ��ʾ����
				
				Z_F_Count = 2;                               // ��������ʱ��־
			}
		}
		if(K_Left == 0)                                                   // ѡ���˳�
		{
			Delay_ms(20);
			if(K_Left == 0)
			{
				while(K_Right == 0);
				LCD12864_DrowSet(0,16,16,16,41,0);
				LCD12864_DrowSet(112,16,16,16,42,0);         // ��ʾ����
				
				LCD12864_DrowSet(0,32,16,16,41,0);
				LCD12864_DrowSet(112,32,16,16,42,1);         // ��ʾ����	
				
				Z_F_Count = 0;                                // �˳���ʱģʽ
			}
		}
	}	
	/*
		�˵���ʾ
	*/
	if(Menu == 0 && Sure_Flag == 0) Clock_Basic_Disp();                                   // ����������ʾ
	if(Menu == 1 && Sure_Flag == 0)                                                       // ʱ�����÷��� ,����������ʾ
	{
		LCD12864_DisplayStrChin(0,0,"��");LCD12864_DisplayStrChin(0,7,"��");
		LCD12864_DisplayStrChin(3,0,"��");LCD12864_DisplayStrChin(3,7,"��");
		LCD12864_DisplayStrChin(1,0,"��");LCD12864_DisplayStrChin(2,0,"��");
		LCD12864_DisplayStrChin(1,7,"��");LCD12864_DisplayStrChin(2,7,"��");
		LCD12864_DrowSet(32,0,16,16,7,1);LCD12864_DrowSet(48,0,16,16,8,1);LCD12864_DrowSet(64,0,16,16,9,1);LCD12864_DrowSet(80,0,16,16,10,1);
		LCD12864_DrowSet(32,16,16,16,11,0);LCD12864_DrowSet(48,16,16,16,12,0);LCD12864_DrowSet(64,16,16,16,13,0);LCD12864_DrowSet(80,16,16,16,14,0);
		LCD12864_DrowSet(32,32,16,16,15,0);LCD12864_DrowSet(48,32,16,16,16,0);LCD12864_DrowSet(64,32,16,16,17,0);LCD12864_DrowSet(80,32,16,16,18,0);
		LCD12864_DrowSet(32,48,16,16,19,0);LCD12864_DrowSet(48,48,16,16,20,0);LCD12864_DrowSet(64,48,16,16,21,0);LCD12864_DrowSet(80,48,16,16,22,0);
	}
	if(Menu == 2 && Sure_Flag == 0)                                                      // �������÷��� ,����������ʾ
	{
		LCD12864_DisplayStrChin(0,0,"��");LCD12864_DisplayStrChin(0,7,"��");
		LCD12864_DisplayStrChin(3,0,"��");LCD12864_DisplayStrChin(3,7,"��");
		LCD12864_DisplayStrChin(1,0,"��");LCD12864_DisplayStrChin(2,0,"��");
		LCD12864_DisplayStrChin(1,7,"��");LCD12864_DisplayStrChin(2,7,"��");
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,11,1);LCD12864_DrowSet(48,16,16,16,12,1);LCD12864_DrowSet(64,16,16,16,13,1);LCD12864_DrowSet(80,16,16,16,14,1);
		LCD12864_DrowSet(32,32,16,16,15,0);LCD12864_DrowSet(48,32,16,16,16,0);LCD12864_DrowSet(64,32,16,16,17,0);LCD12864_DrowSet(80,32,16,16,18,0);
		LCD12864_DrowSet(32,48,16,16,19,0);LCD12864_DrowSet(48,48,16,16,20,0);LCD12864_DrowSet(64,48,16,16,21,0);LCD12864_DrowSet(80,48,16,16,22,0);
	}
	if(Menu == 3 && Sure_Flag == 0)                                                      // �������÷��� ,����������ʾ
	{
		LCD12864_DisplayStrChin(0,0,"��");LCD12864_DisplayStrChin(0,7,"��");
		LCD12864_DisplayStrChin(3,0,"��");LCD12864_DisplayStrChin(3,7,"��");
		LCD12864_DisplayStrChin(1,0,"��");LCD12864_DisplayStrChin(2,0,"��");
		LCD12864_DisplayStrChin(1,7,"��");LCD12864_DisplayStrChin(2,7,"��");
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,11,0);LCD12864_DrowSet(48,16,16,16,12,0);LCD12864_DrowSet(64,16,16,16,13,0);LCD12864_DrowSet(80,16,16,16,14,0);
		LCD12864_DrowSet(32,32,16,16,15,1);LCD12864_DrowSet(48,32,16,16,16,1);LCD12864_DrowSet(64,32,16,16,17,1);LCD12864_DrowSet(80,32,16,16,18,1);
		LCD12864_DrowSet(32,48,16,16,19,0);LCD12864_DrowSet(48,48,16,16,20,0);LCD12864_DrowSet(64,48,16,16,21,0);LCD12864_DrowSet(80,48,16,16,22,0);
	}
	
	if(Menu == 4 && Sure_Flag == 0)                                                     // �������÷��� ,����������ʾ
	{
		LCD12864_DisplayStrChin(0,0,"��");LCD12864_DisplayStrChin(0,7,"��");
		LCD12864_DisplayStrChin(3,0,"��");LCD12864_DisplayStrChin(3,7,"��");
		LCD12864_DisplayStrChin(1,0,"��");LCD12864_DisplayStrChin(2,0,"��");
		LCD12864_DisplayStrChin(1,7,"��");LCD12864_DisplayStrChin(2,7,"��");
		LCD12864_DrowSet(32,0,16,16,7,0);LCD12864_DrowSet(48,0,16,16,8,0);LCD12864_DrowSet(64,0,16,16,9,0);LCD12864_DrowSet(80,0,16,16,10,0);
		LCD12864_DrowSet(32,16,16,16,11,0);LCD12864_DrowSet(48,16,16,16,12,0);LCD12864_DrowSet(64,16,16,16,13,0);LCD12864_DrowSet(80,16,16,16,14,0);
		LCD12864_DrowSet(32,32,16,16,15,0);LCD12864_DrowSet(48,32,16,16,16,0);LCD12864_DrowSet(64,32,16,16,17,0);LCD12864_DrowSet(80,32,16,16,18,0);
		LCD12864_DrowSet(32,48,16,16,19,1);LCD12864_DrowSet(48,48,16,16,20,1);LCD12864_DrowSet(64,48,16,16,21,1);LCD12864_DrowSet(80,48,16,16,22,1);
	}
}

/*
	����LCD���ⰴ��
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
	�ж������Ƿ�ʱ�����Ӻ���
*/
void Set_Alarm(void)
{
	// ��ʾ����ʱ�䵽
	if(Z10BCD(Alarm_Read[5])==Get_Time[6] && Z10BCD(Alarm_Read[4])==Get_Time[5] && Z10BCD(Alarm_Read[3])==Get_Time[4] && Z10BCD(Alarm_Read[2])==Get_Time[2] && Z10BCD(Alarm_Read[1])==Get_Time[1] && Z10BCD(Alarm_Read[0])==Get_Time[0])  
	{
		/*
			�������д����ʱ�䵽��ִ�к���
		*/
		AT24C32_WriteOneByte(0x0007,0);	                                  // �Զ��ر�����
		LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
		LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ		
		
		LCD12864_DisplayStrChin(0,0,"    ʱ�䵽��    ");
		Delay_ms(3000);                                                   // ��ʱ�����ڿ�����������ʾʱ��

		LCD12864_DrawClear();                                             // LCD12864���� ���㷽ʽ
		LCD12864_Clear();                                                 // LCD12864���� �ֿⷽʽ		
		
		LCD12864_DrowSet(96,16,32,16,24,0);
	}
}












