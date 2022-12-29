#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "bsp_lcd.h"
#include <stdio.h>
#include "bsp_calendar.h"
#include "bsp_beep.h"
#define LEDBLUE_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_1)
#define LEDBLUE_OFF		GPIO_SetBits( GPIOB, GPIO_Pin_1)
#define LEDBLUE_CPL		GPIO_WriteBit( GPIOB , GPIO_Pin_1 , !GPIO_ReadOutputDataBit( GPIOB, GPIO_Pin_1 ) )
#define LEDGREEN_ON		GPIO_ResetBits(GPIOB, GPIO_Pin_0)
#define LEDGREEN_OFF	GPIO_SetBits(GPIOB, GPIO_Pin_0)
#define LEDGREEN_CPL	GPIO_WriteBit( GPIOB , GPIO_Pin_0 , !GPIO_ReadOutputDataBit( GPIOB, GPIO_Pin_0 ) )
#define LEDRED_ON			GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define LEDRED_OFF		GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define LEDRED_CPL		GPIO_WriteBit( GPIOB , GPIO_Pin_5 , !GPIO_ReadOutputDataBit( GPIOB, GPIO_Pin_5 ) )


//ʱ�ӽṹ��
typedef struct{
	u16 Year;
	u8 Day;
	u8 Month;
	u8 Date;
	u8 Hour;
	u8 Min;
	u8 Sec;
}TimeStruct;

//�����ṹ��
typedef struct{
	u16 Year;
	u8	Month;
	u8	Date;
}CalendarStruct;
//����ʱ
typedef struct{
	u8  MiaoB_hour;
	u8	MiaoB_min;
	u8	MiaoB_sec;
	u8  MiaoB_s;
}Miao_Biao;
extern u32 Counter_miao_biao;
/*******************************  ȫ�ֱ�������  *******************************/
extern	u16	 		KeyNum;													//��ֵ
extern	u32			KeyCnt,KeyUpCnt;								//����ʱ�䣨��λ10ms��,�����ͷ�ʱ�䣨��λ10ms��
extern	u8			UICnt,UIRep;										//����ָ�룬����ָ�뱸��
extern	TimeStruct 		RealTime;									//ʱ��
extern	CalendarStruct	Calendar,LunarCalendar;	//������ũ��
extern	Miao_Biao 		miao_biao;	
/*****************************  ȫ�ֱ����������  *****************************/


/************  ϵͳ���ú���  ************/
void SystemConfiguration( void );
void GPIO_Configuration( void );
void NVIC_Configuration( void );
void TIM6_Configuration( void );
void TIM7_Configuration( void );
void TIM1_Configuration( void );
void TIM2_Configuration( void );
void Flash_TouchCalibrate ( void );
void RTC_Configuration( void );

/**************  ���ܺ���  **************/
void Delay(u32 Cnt);
u16	 KeyScan( void );
void Alarm( u8 cmd );

/**************  �������ܺ���  **************/
u8 Is_LeapYear( u16 year );
u8 Get_Week( u16 Year , u8 Month , u8 Date );
u8 Get_DateMax(u16 Year,u8 Month);
u8 Set_RTCTime( TimeStruct *Time );
void Read_RTCTime( TimeStruct *Time );
void DrawCalendar(unsigned int Year,unsigned int Month,unsigned int CurrentDate,unsigned int SelectDate);
/**************  ������ƺ���  **************/
void UI00( void );
void UI01( void );
void UI02( void );
void UI03( void );
void UI04( void );
void UI05( void );
void UI06( void );
void UI10( void );
void UI11( void );
void UI12( void );
void UI20( void );


/**************  ����ɨ�躯��  **************/
u16 Get_TouchKey( void );
void  change_year(void);
void  change_month(void);
void  change_day(void);
void  nao_change_min(void);
void  nao_change_sec(void);
void  change_hour(void);
void  change_min(void);
void  change_sec(void);
#endif
