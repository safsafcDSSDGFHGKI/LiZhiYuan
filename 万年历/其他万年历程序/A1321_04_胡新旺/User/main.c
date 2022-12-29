#include "main.h"
#include "clock.h"
#include "math.h"
/*******************************  ȫ�ֱ�������  *******************************/
u32                 Counter_miao_biao;                     //���
u16	 		        KeyNum;												//��ֵ
u32			        KeyCnt,KeyUpCnt;								    //����ʱ�䣨��λ10ms��,�����ͷ�ʱ�䣨��λ10ms��
u8			        UICnt,UIRep;										//����ָ�룬����ָ�뱸��
TimeStruct 			RealTime;								            //ʱ��
TimeStruct 			SetTime;                                             //set time 
CalendarStruct	    Calendar,LunarCalendar;	                             //������ũ��
Miao_Biao 	     	miao_biao;                                           //���
u16                 Last_Ui;                                             //��������������һ��ui����
u16                 num1,num2;
/*****************************  ȫ�ֱ����������  *****************************/

/*12-11 ��������ƣ����   12-13 �������߼������     12-16 �����Ʊ��棬ppt�����     */
#define  PROTECTION_TIME  1*1000// ��������ʱ�� 10s

int main(void)
{
	SystemConfiguration();
	
	ILI9341_Clear( 0 , 0 , 240 , 320 , macWHITE );
	
	RealTime.Year = 2016;
	RealTime.Month = 12;
	RealTime.Date = 11;
	RealTime.Hour = 21;
	RealTime.Min = 40;
	RealTime.Sec = 50;
	Set_RTCTime( &RealTime );
	
	Calendar.Year = RealTime.Year;
	Calendar.Month = RealTime.Month;
	Calendar.Date = 0;

	UICnt = 0x00;	
	Last_Ui = 0x00;
	while(1)
	{
		switch(UICnt)
		{
			case	0x00:	UI00();	break; // ʱ�ӽ���
			case	0x01:	UI01();	break; // ���ӽ���
			case	0x02:	UI02();	break; // ������
			case	0x03:	UI03();	break; // ��������
			case	0x04:	UI04();	break; // ʱ�����ý���
			case	0x05:	UI05();	break; // 
			case	0x06:	UI06();	break; // ���� ���� ����
			case	0x10:	UI10();	break; //��������

			default:	break;
		}
	}
}


/*******************************  ���ݱ��  *******************************/
//������ʾ�ַ���(Ӣ��)
const char DayTab[7][4] = {
	"Sun\0","Mon\0","Tue\0","Wed\0","Thu\0","Fri\0","Sat\0",
};

//������ʾ�ַ���(����)
const char DayTab_Han[7][3] = {
	"��\0","һ\0","��\0","��\0","��\0","��\0","��\0",
};

//��������ڱ�
const unsigned char DateMaxTab[13] = {
	0,31,28,31,30,31,30,31,31,30,31,30,31,
};

//ũ�����ڱ�
const unsigned char LunarDateName[][5]=   {
	"  \0","��һ\0","����\0","����\0","����\0","����\0","����\0","����\0","����\0","����\0","��ʮ\0",
	"ʮһ\0","ʮ��\0","ʮ��\0","ʮ��\0","ʮ��\0","ʮ��\0","ʮ��\0","ʮ��\0","ʮ��\0","��ʮ\0",
	"إһ\0","إ��\0","إ��\0","إ��\0","إ��\0","إ��\0","إ��\0","إ��\0","إ��\0","��ʮ\0"
};

//ũ���·ݱ�
const unsigned char LunarMonthName[][5]=   {
	"  \0","����\0","����\0","����\0","����\0","����\0","����\0","����\0","����\0","����\0","ʮ��\0","����\0","����\0",
};


/*******************************  ϵͳ���ú���  *******************************/
void SystemConfiguration( void )
{
	GPIO_Configuration();
	LCD_Init();	
	RTC_Configuration();
	FLASH_SPI_initialize();
	Flash_TouchCalibrate();
	TIM6_Configuration();
	TIM7_Configuration();
	TIM1_Configuration();
	TIM2_Configuration();
	NVIC_Configuration();
	Beep_Init();
}


void GPIO_Configuration()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//�����ȿ���ʱ������������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC ,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	LEDBLUE_OFF;LEDGREEN_OFF;LEDRED_OFF;
}



void NVIC_Configuration()
{
	NVIC_InitTypeDef NVIC_InitStructure;  

	
	//����TIM2�ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	//����TIM6�ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	//����TIM7�ж�
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	//����RTC�ж�
	//1����ռʽ���ȼ�,0�������ȼ�,ʹ��������Ϊ�ж�Դ
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}



/****************************************************************************
* ��    �ƣ�void TIM1_Configuration(void)
* ��    �ܣ�TIM1��ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// ����Ƚ�ͨ�� GPIO ��ʼ��
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1 , ENABLE );
		
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit( TIM1 , &TIM_TimeBaseStructure);

	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;// ����ΪPWMģʽ1	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;// ���ʹ��	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 500;// ����ռ�ձȴ�С	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;// ��Ч��ƽΪ��
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	//��������͵�ƽ
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init( TIM1 , &TIM_OCInitStructure );
	TIM_OC1PreloadConfig( TIM1 , TIM_OCPreload_Enable );//ʹ��TIM1 �� CCR1 �ϵ�Ԥװ�ؼĴ���
	
	// ʹ�ܼ�����
//	TIM_Cmd( TIM1 , ENABLE );	
	// �����ʹ�ܣ���ʹ�õ���ͨ�ö�ʱ��ʱ����䲻��Ҫ
//	TIM_CtrlPWMOutputs( TIM1 , ENABLE );
}

/****************************************************************************
* ��    �ƣ�void TIM2_Configuration(void)
* ��    �ܣ�TIM2��ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    �������ö�ʱ��T2ÿ10ms�ж�һ��
* ���÷������� 
****************************************************************************/ 
void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_DeInit(TIM2);
	
	TIM_TimeBaseStructure.TIM_Period = 99;
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);	

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);   
//	TIM_Cmd(TIM2, ENABLE);
}


/****************************************************************************
* ��    �ƣ�void TIM6_Configuration(void)
* ��    �ܣ�TIM6��ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    �������ö�ʱ��T6ÿ10ms�ж�һ��
* ���÷������� 
****************************************************************************/ 
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_DeInit(TIM6);
	
	TIM_TimeBaseStructure.TIM_Period = 99; 							//��ʱ10ms
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);   
	TIM_Cmd(TIM6, ENABLE);
}

/****************************************************************************
* ��    �ƣ�void TIM7_Configuration(void)
* ��    �ܣ�TIM7��ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    �������ö�ʱ��T7ÿ80ms�ж�һ��,�������Ӷ�ʱ
* ���÷������� 
****************************************************************************/ 
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_DeInit(TIM7);
	
	TIM_TimeBaseStructure.TIM_Period = 799; 							//��ʱ80ms
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);	

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);   
//	TIM_Cmd(TIM7, ENABLE);
}


 /**
  * @brief  LCD������У׼����ⲿflash��ȡУ׼ϵ��
  * @param  ��
  * @retval ��
  */	
void Flash_TouchCalibrate ( void )
{
	uint8_t ucStoreFlag;                            //LCD������У׼ϵ���洢��־
	
	SPI_FLASH_ReadDeviceID();                       // Get SPI Flash Device ID */
	
	SPI_FLASH_BufferRead ( & ucStoreFlag, 0, 1 );   //���ⲿflash����LCD������У׼ϵ���洢��־
	
	if ( ucStoreFlag == 0x52 )                                                                         //�Ѵ洢��LCD������У׼ϵ��
		SPI_FLASH_BufferRead ( ( void * )  & strXPT2046_TouchPara, 1, sizeof ( strXPT2046_TouchPara ) ); //������ȡLCD������У׼ϵ��
		
	else                                          //��δ�洢��LCD������У׼ϵ��
	{
		while( ! XPT2046_Touch_Calibrate () );      //�ȴ�������У�����

		/* �洢LCD������У׼ϵ���ͱ�־ */
		ucStoreFlag = 0x52;
		SPI_FLASH_SectorErase ( 0 );
		SPI_FLASH_BufferWrite ( & ucStoreFlag, 0, 1 );     
		SPI_FLASH_BufferWrite ( ( void * )  & strXPT2046_TouchPara, 1, sizeof ( strXPT2046_TouchPara ) );	
	}
	
//	SPI_Flash_PowerDown();                          //�������ģʽ
	
}

/****************************************************************************
* ��    �ƣ�void RTC_Configuration(void)
* ��    �ܣ�RTC��ʼ������
* ��ڲ�������
* ���ڲ�������
* ˵    ������ʼ��RTC
* ���÷������� 
****************************************************************************/ 
void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	/* Reset Backup Domain */
	BKP_DeInit();
	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);
	/* Wait for RTC registers synchronization */
	RTC_WaitForSynchro();
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	PWR_BackupAccessCmd(DISABLE);
}


/**************  ���ܺ���  **************/

void Delay(u32 Cnt)
{
	while(--Cnt);
}


u16 KeyScan()
{
	u16 key;
	
	if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1) && (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==1)) key = 3;	
	else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0) && (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==1)) key = 2;
	else if((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==1) && (GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)==0)) key = 1;
	else key = 0;
	return key;
}


/****************************************************************************
* ��    �ƣ�void Alarm( u8 cmd )
* ��    �ܣ���������
* ��ڲ�����cmd	1:����	0:ֹͣ����
* ���ڲ�����
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void Alarm( u8 cmd )
{
	if(cmd)
	{
		TIM_Cmd( TIM7 , ENABLE );	
		TIM_Cmd( TIM1 , ENABLE );	
		TIM_CtrlPWMOutputs( TIM1 , ENABLE );
	}
	else
	{
		TIM_Cmd( TIM7 , DISABLE );	
		TIM_Cmd( TIM1 , DISABLE );	
		TIM_CtrlPWMOutputs( TIM1 , DISABLE );
	}
}

/**************  �������ܺ���  **************/


/****************************************************************************
* ��    �ƣ�u8 Is_Leap_Year(u16 year)
* ��    �ܣ��ж��Ƿ�������
* ��ڲ�����year
* ���ڲ�����1:�����ꣻ0:������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
u8 Is_LeapYear(u16 year)
{
	if(year%4==0) //�����ܱ�4����
	{ 
		if(year%100==0) 
		{
			if(year%400==0)return 1;//�����00��β,��Ҫ�ܱ�400����
			else return 0; 
		}
		else return 1; 
	}
	else return 0;
} 

/****************************************************************************
* ��    �ƣ�u8 Get_Week(u16 Year,u16 Month,u16 Date)
* ��    �ܣ��ò��գ�Zeller����ʽ�������ڼ�	

	w=y+[y/4]+[c/4]-2c+[26��m+1��/10]+d-1

	Ȼ��w��7ȡ�ࡣ
	��ʽ�еķ��ź������£�w�����ڣ�c�����ͣ�y���꣨��λ������m���£�m���ڵ���3��С
	�ڵ���14�����ڲ��չ�ʽ�У�ĳ���1��2��Ҫ������һ���13��14�������㣬����2003��1��1
	��Ҫ����2002���13��1�������㣩��d���գ�[ ]����ȡ������ֻҪ�������֡�

* ��ڲ�����Year:��; Month:��; Date:�ա�
* ���ڲ��������ڼ� 1~6��������һ~��������0����������
* ˵    ����
* ���÷�������
****************************************************************************/ 
u8 Get_Week(u16 Year,u8 Month,u8 Date)
{
	int  W,Y,C,M,D;
	u8 day;
	
	C = Year/100;
	Y = Year%100;
	M = Month;
	if(M<3){M+=12;Y--;}
	D = Date;
	W = Y + Y/4 + C/4 - 2*C + 26*(M+1)/10 + D - 1;
	while(W<0)	W += 7;
	day = W%7;
	return day;
}

u8 Get_DateMax(u16 Year,u8 Month)
{
	u8 DateMax;
	
	DateMax = DateMaxTab[ Month ];
	if( Month==2 )
	{
		if( Is_LeapYear( Year ) == 1 )	DateMax++;
	}
	
	return DateMax;
}



/****************************************************************************
* ��    �ƣ�u8 Set_RTCTime(TimeStruct *Time)
* ��    �ܣ�����ʱ��:��1970-01-01 0:0:0Ϊ��׼,�������ʱ��ת��Ϊ����,
* 					��д��RTC��������1970~2099��Ϊ�Ϸ���ݡ�
* ��ڲ�����T_STRUCT* Time
* ���ڲ�����0:�ɹ�;
						1:������룬����Чʱ��(1970~2099)
* ˵    ����
* ���÷�����Set_RTCTime(&RealTime);
****************************************************************************/ 
u8 Set_RTCTime( TimeStruct *Time)
{
	u32 Count = 0;
	u16 i;
	if(Time->Year<1970||Time->Year>2099) return 1;
	for(i=1970;i<Time->Year;i++)
	{
		if(Is_LeapYear(i)) Count += 31622400;		//���������
		else Count += 31536000;									//ƽ�������
	}
	for(i=1;i<Time->Month;i++)
	{
		Count += (u32)DateMaxTab[i]*86400;
		if(Is_LeapYear(Time->Year) && i==2) Count += 86400;
	}
	Count += (u32)(Time->Date-1)*86400;
	Count += (u32)(Time->Hour)*3600;
	Count += (u32)(Time->Min)*60;
	Count += (u32)(Time->Sec);
	
	//ʹ��PWR��BKP����ʱ��,���һ������ʡ	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	 
	PWR_BackupAccessCmd(ENABLE);	//ʹ��RTC�ͺ󱸼Ĵ������� 
	
	RTC_SetCounter(Count);
	RTC_WaitForLastTask();

	return 0;   
}




/****************************************************************************
* ��    �ƣ�void Cal_Time(u32 Count,TimeStruct *Time)
* ��    �ܣ�����32λCount����ֵ�������ں�ʱ��
* ��ڲ�����Count
* ���ڲ�����T_STRUCT* Time
* ˵    ����
* ���÷�����Cal_Time(Count,&RealTime);
****************************************************************************/ 
void Cal_Time(u32 Count,TimeStruct *Time)
{
	u32 SecTemp=0,DateTemp=0,Temp=0;
	
	DateTemp = Count/86400;					//����
	if(DateTemp!=0)							//����1��
	{
		//ȷ����
		Temp = 1970;
		while(DateTemp>=365)
		{
			if(Is_LeapYear(Temp))	       //����?
			{
				if(DateTemp>=366) DateTemp -= 366;
				else 
				{
					break;
				}
			}
			else DateTemp -= 365;
			Temp++;
		}
		Time->Year = Temp;
		
		//ȷ����
		Temp = 1;
		while(DateTemp>=28)
		{
			if(Is_LeapYear(Time->Year)&&Temp==2)
			{
				if(DateTemp>=29)DateTemp -= 29;//����Ķ�������
        else break; 
			}
			else
			{
				if(DateTemp>=DateMaxTab[Temp]) DateTemp -= DateMaxTab[Temp];
				else break;
			}
			Temp++;
		}
		Time->Month = Temp;
		Time->Date = DateTemp+1;
	}
	else
	{
		Time->Year = 1970;
		Time->Month = 1;
		Time->Date = 1;
	}
	SecTemp = Count%86400;
	Time->Hour = SecTemp/3600;
	Time->Min  = SecTemp%3600/60;
	Time->Sec  = SecTemp%60;
	Time->Day  = Get_Week(Time->Year,Time->Month,Time->Date);
}


/****************************************************************************
* ��    �ƣ�void Read_RTCTime(TimeStruct *Time)
* ��    �ܣ���RTC��������ȡʱ��		
* ��ڲ�����T_STRUCT* Time
* ���ڲ�������
* ˵    ����
* ���÷�����Read_RTCTime(&RealTime);
****************************************************************************/ 
void Read_RTCTime( TimeStruct *Time)
{
	u32 Count = 0;
	Count = RTC_GetCounter();
	Cal_Time(Count,Time);
}






/**************  ������ƺ���  **************/
void UI00( void )
{
	u16 TouchKey;
	char	cStr[ 40 ],Str[40];
	ILI9341_Clear(0,0,240,320,macBLACK);	
//	clock_base();  //ʱ��  ����
	// 20 - 60    70-120  130 - 170  180 -220      y(16-48)
	ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"ʱ��",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"����",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"���",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"����",macBLACK ,macWHITE);
	calendar_circle_clock_drawpanel(120,140,160,9);
	ILI9341_DrawCircle( 120, 298, 20, macRED,1);   //��Բ
	ILI9341_DispString_EN_CH( 104,290,(const uint8_t *)"����",macRED,macWHITE);
	// ����1:����LCD��������ͼ�ν���
	// ILI9341_Clear(0,0,240,320,UI0BackColor);
	// ......
	// ����2:����ѭ��
	while(1)
	{
		  //��ʾָ��
		 uint8_t second;   		
	{	
		if(second!=RealTime.Sec)   //��ֹʱ�� ����  ���� ����
		{	
		second=RealTime.Sec; 			
        calendar_circle_clock_showtime(120,140,160,9,RealTime.Hour,RealTime.Min,RealTime.Sec);//��ʾ ʱ����	 
         }			
	}
		//����ʱ��
		//......
		//��ʾʱ��
		sprintf( cStr , "%02d-%02d-%02d " , RealTime.Year , RealTime.Month , RealTime.Date  );
						
		ILI9341_DispString_EN_CH( 60,240, (u8*)cStr ,macBLACK  ,  macWHITE);		
		sprintf( Str , " %02d:%02d:%02d %s" ,RealTime.Hour , RealTime.Min , RealTime.Sec ,DayTab_Han[Get_Week(RealTime.Year,RealTime.Month,RealTime.Date)]);

       ILI9341_DispString_EN_CH( 60,260, (u8*)Str ,macBLACK  ,  macWHITE);	
		
		//�ж��Ƿ�����ʱ��
		//......
		
		//��������
		if ( tp_dev.sta )
		{
			TouchKey = Get_TouchKey();
			
			if( TouchKey==121)
			{
				//��������...
				while( tp_dev.sta );
				UICnt = 0x00;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==122 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x01;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==123 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x02;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==124 )  // ����
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x03;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==125)   //ʱ�����ý���
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x04;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			
		}
			//��������
		if(KeyUpCnt > PROTECTION_TIME)  // 
		{
			  Last_Ui = UICnt;
			  UICnt = 0x10;    //��������
			  break;
		}		
	}
}


void UI01( void ) //���� ���� ���� ����
{
	u16 TouchKey;
	char cStr[40],Str[40];
	ILI9341_Clear(0,0,240,20,macBLACK);  
	ILI9341_Clear(0,20,240,300,macBLACK);  
    ILI9341_DrawRectangle(0, 40, 240, 80,macWHITE, 1 ); 
	
    ILI9341_DrawCircle(185,60,10,macBLACK,1);
	ILI9341_DrawRectangle(185,50,28,21,macBLACK,1);	
	ILI9341_DrawCircle(215,60,10,macBLACK,1); 
	
	sprintf( cStr , "%02d:%02d " , num1, num2);
	ILI9341_DispString_EN_32( 30,50,(const char *)cStr,macWHITE ,macBLACK);
	ILI9341_DispString_EN_CH(10,90,"�� һ �� �� �� �� ��",macWHITE ,macBLACK);
	while(1)
	{	
	  ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"ʱ��",macBLACK ,macWHITE);
	  ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"����",macBLACK ,macWHITE);
	  ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"���",macBLACK ,macWHITE);
	  ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"����",macBLACK ,macWHITE);    
  
		sprintf( Str , " %02d:%02d " , num1 , num2 );
        ILI9341_DispString_EN_32( 30,50, (u8*)Str ,macWHITE,macBLACK);			
		//��������
		if ( tp_dev.sta )
	  {
			TouchKey = Get_TouchKey();			
			if( TouchKey==121)
			{				
				//��������...
				while( tp_dev.sta );
				UICnt = 0x00;		//�޸Ľ���ָ��  ����ʱ�� ���� ����
				break;					//�˳�
			}
			else if( TouchKey==122 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x01;		//�޸Ľ���ָ��  ���� ���� ���� ����
				break;					//�˳�
			}
			else if( TouchKey==123 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x02;		//�޸Ľ���ָ��  ���� ���� ���� ����
				break;					//�˳�
			}

			else if(TouchKey==124)
			{
			  	while( tp_dev.sta );
				UICnt = 0x03;		//�޸Ľ���ָ��  ���� ���� ���� ����
				break;					//�˳�
			}
			else if(TouchKey==125)  
			{
			   	while( tp_dev.sta );
				UICnt = 0x06;		//�޸Ľ���ָ��  ���� ���� ���� ���� ����
				break;	
			}	
		  else if(TouchKey==126)//RED
		  {
			while(tp_dev.sta )			
			ILI9341_DrawCircle(185,60,10,macRED,1); 
			ILI9341_DrawRectangle(195,50,18,21,macBLACK,1);	
			ILI9341_DrawCircle(215,60,10,macBLACK,1); 
           if(num1==RealTime.Hour&&num2==RealTime.Min)	  //RealTime.Min,RealTime.Sec
		   {
			  BEEP_ON();		
		   }		
		  }	
          else if(TouchKey==127)//BLUE
		  {
		    while(tp_dev.sta )			
			ILI9341_DrawCircle(215,60,10,macBLUE,1);
			ILI9341_DrawCircle(185,60,10,macBLACK,1);
			ILI9341_DrawRectangle(185,50,20,21,macBLACK,1);	
			BEEP_OFF();			      	
		  }	         
	  }	
		
		if(KeyUpCnt > PROTECTION_TIME) //��������
		{
			Last_Ui = UICnt;
			UICnt = 0x10;    //��������
			break;
		}
	}	
}

void UI02( void )//������
{
	u16 TouchKey;
	char cStr[20];
	ILI9341_Clear(0,0,240,20,macBLACK);
	ILI9341_Clear(0,20,240,300, macWHITE);

	ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"ʱ��",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"����",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"���",macBLACK ,macWHITE);
    ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"����",macBLACK ,macWHITE);    
	ILI9341_DrawRectangle(10,290,66,30,macBLUE2,1);
	ILI9341_DrawRectangle(86,290,66,30,macBLUE2 ,1);
	ILI9341_DrawRectangle(162,290,66,30,macBLUE2,1);
	ILI9341_DispString_CH(28,297,"��ʱ",macBLUE2,macBLACK);
	ILI9341_DispString_CH(103,297,"����",macBLUE2,macBLACK);
	ILI9341_DispString_CH(179,297,"��ͣ",macBLUE2,macBLACK);
	sprintf( cStr , " %02d:%02d:%02d:%02d" , 
						 miao_biao.MiaoB_hour,miao_biao.MiaoB_min , miao_biao.MiaoB_sec,miao_biao.MiaoB_s );
	ILI9341_DispString_EN_32( 10 , 40 , (u8*)cStr , macWHITE , macBLACK );
	
	while(1)
	{		
	if ( tp_dev.sta )
		{
		  TouchKey = Get_TouchKey();			
			
		   if( TouchKey==121 )
			{			
				while( tp_dev.sta );
				UICnt = 0x00;		//����ʱ�ӽ���
				break;					//�˳�
			}
			else if( TouchKey==122 )
			{			
				while( tp_dev.sta );
				UICnt = 0x01;		//����������
				break;					//�˳�
			} 
			else if( TouchKey==123)  
			{
				while( tp_dev.sta );
				UICnt = 0x02;		//������������
				break;					//�˳�
			}
			else if( TouchKey==124)  
			{
				while( tp_dev.sta );
				UICnt = 0x03;		//������������
				break;					//�˳�
			}
			else if( tp_dev.x>=10 && tp_dev.x<76 && tp_dev.y>=290&& tp_dev.y<320)
			{
			    TIM_Cmd( TIM2 , ENABLE );	
			}
			else if( tp_dev.x>=86 && tp_dev.x<152 && tp_dev.y>=290&& tp_dev.y<320)
			{
			 Counter_miao_biao=0;
			 miao_biao.MiaoB_hour=00;
             miao_biao.MiaoB_min=00;
             miao_biao.MiaoB_sec=00;
             miao_biao.MiaoB_s=00;	
			}
			else if( tp_dev.x>=162 && tp_dev.x<228 && tp_dev.y>=290&& tp_dev.y<320)
			{
			  TIM_Cmd( TIM2 , DISABLE );
			}
		}
		sprintf( cStr , " %02d:%02d:%02d:%02d" , 
						 miao_biao.MiaoB_hour,miao_biao.MiaoB_min , miao_biao.MiaoB_sec,miao_biao.MiaoB_s );
	   ILI9341_DispString_EN_32( 10 , 40 , (u8*)cStr , macWHITE , macBLACK );	
					
		 if(KeyUpCnt > PROTECTION_TIME)  //��������
		{
		  Last_Ui = UICnt;
		  UICnt = 0x10;    //��������
		   break;
		 }
	}
	
}
unsigned char month ;
void UI03( void )
{
	u16 TouchKey;
	unsigned char CurrentDate,SelectDate;
	
//	unsigned int row2,col2,w ;
//struct T_STRUCT Real_Time;
	month = RealTime.Month;
	CurrentDate = RealTime.Day;
	SelectDate	= RealTime.Day;;
	ILI9341_Clear(0,0,240,320,macWHITE);	
	ILI9341_Clear(0,0,240,50,macBLACK);	
	DrawCalendar(RealTime.Year,RealTime.Month,RealTime.Day,RealTime.Day);
	ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"ʱ��",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"����",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"���",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"����",macBLACK ,macWHITE);
//	ILI9341_DrawCircle( 200, 42-16, 5, macRED,1 );   //��Բ��

	while(1)
	{	
		if ( tp_dev.sta )	     
    {    			
				TouchKey = Get_TouchKey();	 
				if( TouchKey==121)
				{
					//��������...
					while( tp_dev.sta );
					UICnt = 0x00;		//�޸Ľ���ָ��
					break;					//�˳�
				}
				else if( TouchKey==122 )
				{
					//...
					while( tp_dev.sta );
					UICnt = 0x01;		//�޸Ľ���ָ��
					break;					//�˳�
				}
				else if( TouchKey==123 )
				{
					//...
					while( tp_dev.sta );
					UICnt = 0x02;		//�޸Ľ���ָ��
					break;					//�˳�
				}
				else if( TouchKey==124 )  // ����
				{
					//...
					while( tp_dev.sta );
					UICnt = 0x03;		//�޸Ľ���ָ��
					break;					//�˳�
				}	
				else if( TouchKey==125 )  // ����
				{
					//...
					while( tp_dev.sta );
					if(month<12)	{ month++; } else { month = 1;}      /*������� ��*/
					ILI9341_Clear(0,50,240,320,macWHITE);	
					DrawCalendar(2016,month,CurrentDate,SelectDate); 
				}	
				else if( TouchKey==126 )  // ����
				{
					//...
					while( tp_dev.sta );
					if(month > 1)	{ month--; } else { month = 12;}     /*������� ��*/
					ILI9341_Clear(0,50,240,320,macWHITE);	
					DrawCalendar(2016,month,CurrentDate,SelectDate); 
				}				
				else if(TouchKey != 65535)
				{		
						SelectDate = TouchKey;
						DrawCalendar(RealTime.Year,month,CurrentDate,TouchKey);/*ѡ�е� ����*/			
				}
		 }	
					//��������
			if(KeyUpCnt > PROTECTION_TIME)  // 15��
			{
				  Last_Ui = UICnt;
					UICnt = 0x10;    //��������
					break;
			}		  	
	}
}
void UI04( void )   //ʱ�����ý���
{
	char	cStr[ 40 ];
	u16 num=0,i=0,m,k=35;
	
	u16 TouchKey;
	ILI9341_Clear(0,0,240,320,macBLACK);  //����
	
	SetTime = RealTime;
	ILI9341_DispString_EN_CH( 0,5,(const uint8_t *)"<<����",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 190,5,(const uint8_t *)"����>>",macBLACK ,macWHITE);
	
	sprintf( cStr , "%02d �� %02d �� %02d ��" , RealTime.Year , RealTime.Month , RealTime.Date );
	ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr,macBLACK ,macWHITE);
	
	sprintf( cStr , "%02d:%02d:%02d " , RealTime.Hour , RealTime.Min , RealTime.Sec );
	
	ILI9341_DispString_EN_32( 48,60,(const char *)cStr,macBLACK ,macWHITE);

	for(m=0;m<4;m++)
	{
	ILI9341_DrawRectangle(6,   180+m*35,  72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(84,  180+m*35, 72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(162, 180+m*35, 72, 30, macBLUE2, 1 );
	
	}
	ILI9341_Clear(78,180,6,135,macGREY);   //����
    ILI9341_Clear(156,180,6,135,macGREY);   //����
    
	ILI9341_Clear(6,210,228,6,macGREY);   //����
    ILI9341_Clear(6,245,228,6,macGREY);   //����
	ILI9341_Clear(6,280,228,6,macGREY);   //����

	ILI9341_DispChar_EN( 39, 187, '1', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 39, 222, '4', macBLUE2, macRED );
	ILI9341_DispChar_EN( 39, 257, '7', macBLUE2, macRED );	
	ILI9341_DispString_CH( 26, 290, (const uint8_t *)"���", macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 116, 187, '2', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 222, '5', macBLUE2, macRED );
	ILI9341_DispChar_EN( 116, 257, '8', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 292, '0', macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 194, 187, '3', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 194, 222, '6', macBLUE2, macRED );
	ILI9341_DispChar_EN( 194, 257, '9', macBLUE2, macRED );	
	ILI9341_DispString_CH( 182, 290, (const uint8_t *)"ȷ��", macBLUE2, macRED );
		
	while(1)
	{		   
		//��������
		if ( tp_dev.sta )
		{
		
//			ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"                         ",macBLACK ,macBLACK);
			TouchKey = Get_TouchKey();
			if( TouchKey==121)
			{
								//...
				while( tp_dev.sta );
				UICnt = 0x00;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==122 )  //����
			{
				//��������...
//				while( tp_dev.sta );
				Set_RTCTime(&SetTime);
				Delay(1000);
				UICnt = 0x00;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==123 )  // year
			{
               change_year();	
			}
			else if( TouchKey==124 )
			{
				//��������...
//				while( tp_dev.sta );
				    change_month();
			}
			else if( TouchKey==125 )
			{
				//��������...
//				while( tp_dev.sta );
				   change_day();
			}
			else if( TouchKey==126 )
			{
				//��������...
//				while( tp_dev.sta );
				  change_hour();
			}
			else if( TouchKey==127 )
			{
				//��������...
//				while( tp_dev.sta );
				change_min();
			}
			else if( TouchKey==128 )
			{
				//��������...
//				while( tp_dev.sta );
				change_sec();
			}
		}		
		//��������
		if(KeyUpCnt > PROTECTION_TIME)  // 10��
		{
			    Last_Ui = UICnt;
				UICnt = 0x10;    //��������
				break;
		}
	}
}
void UI05( void )
{
	while(1)
	{
	 
	
	}
}
void UI06( void ) //���� ���� ��� ���� 
{
	char	cStr[ 40 ];
	u16 num=0,i=0,m,k=35;
	
	u16 TouchKey;
	ILI9341_Clear(0,0,240,320,macBLACK);  //����
	
	SetTime = RealTime;
	ILI9341_DispString_EN_CH( 0,5,(const uint8_t *)"<<����",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 190,5,(const uint8_t *)"����>>",macBLACK ,macWHITE);
		
	sprintf( cStr , "%02d:%02d " , num1,num2);
	
	ILI9341_DispString_EN_32( 96,60,(const char *)cStr,macBLACK ,macWHITE);

	for(m=0;m<4;m++)
	{
	ILI9341_DrawRectangle(6,   180+m*35,  72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(84,  180+m*35, 72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(162, 180+m*35, 72, 30, macBLUE2, 1 );	
	}
	ILI9341_Clear(78,180,6,135,macGREY);   //����
    ILI9341_Clear(156,180,6,135,macGREY);   //����
    
	ILI9341_Clear(6,210,228,6,macGREY);   //����
    ILI9341_Clear(6,245,228,6,macGREY);   //����
	ILI9341_Clear(6,280,228,6,macGREY);   //����

	ILI9341_DispChar_EN( 39, 187, '1', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 39, 222, '4', macBLUE2, macRED );
	ILI9341_DispChar_EN( 39, 257, '7', macBLUE2, macRED );	
	ILI9341_DispString_CH( 26, 290, (const uint8_t *)"���", macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 116, 187, '2', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 222, '5', macBLUE2, macRED );
	ILI9341_DispChar_EN( 116, 257, '8', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 292, '0', macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 194, 187, '3', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 194, 222, '6', macBLUE2, macRED );
	ILI9341_DispChar_EN( 194, 257, '9', macBLUE2, macRED );	
	ILI9341_DispString_CH( 182, 290, (const uint8_t *)"ȷ��", macBLUE2, macRED );
		
	while(1)
	{		   
		//��������
		if ( tp_dev.sta )
		{		
			ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"                         ",macBLACK ,macBLACK);
			TouchKey = Get_TouchKey();
			if( TouchKey==121)
			{
				while( tp_dev.sta );
				UICnt = 0x01;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==122 )  //����
			{
//				Set_RTCTime(&SetTime);//���� ���úõ� RTCҪ ���� �� ���ӹ������� 
				Delay(1000);
				UICnt = 0x01;		//�޸Ľ���ָ��
				break;					//�˳�
			}
			else if( TouchKey==127 )
			{
				nao_change_min();
			}
			else if( TouchKey==128 )
			{
				nao_change_sec();
			}
		}	
		
		//��������
		if(KeyUpCnt > PROTECTION_TIME)  // 10��
		{
			  Last_Ui = UICnt;
			  UICnt = 0x10;    //��������
			  break;
		}
	}
	
	
}
void UI10( void )  // ��������
{
	char cStr[40];
	ILI9341_Clear(0,0,240,320,macBLACK);
	ILI9341_DrawRectangle(0, 120, 240, 120,macWHITE, 1 );
	
	while(1)
	{
		
	sprintf( cStr , "%02d:%02d:%02d" , RealTime.Hour , RealTime.Min , RealTime.Sec );//��ʾʱ��
					 
	ILI9341_DispString_EN_48( 20,120, (const char *)cStr ,macWHITE  ,macBLACK  );	
	
	sprintf( cStr ,"%02d-%02d-%02d  %s" ,RealTime.Year , RealTime.Month , RealTime.Date , DayTab_Han[Get_Week(RealTime.Year,RealTime.Month,RealTime.Date)]); 
					
	ILI9341_DispString_EN_CH( 20,180, (u8*)cStr ,macWHITE  , macBLACK );	
		
	ILI9341_DispString_EN_CH(20,200,"����A1321-04-������",macWHITE  , macBLACK);
	if ( tp_dev.sta )//��������
	{				
		UICnt =Last_Ui ;	
		KeyUpCnt = 0;
		break;
	}
	}
}


/**************  ����ɨ�躯��  **************/
u16 Get_TouchKey( void )
{
	u16	KeyTmp;
	u8  num_x;
	u16 num_y;
	
	//ʱ�ӽ���
	if( UICnt==0x00 )				
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
			//ʱ��	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48 )	           KeyTmp = 121;  //ʱ�ӵķ��ؼ�ֵ 
			//����  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48 )	    KeyTmp = 122; //���ӵķ��� ��ֵ 
			//���  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48 )  	KeyTmp = 123; //��� �� ���� ��ֵ
			//��ʱ  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48 )  	KeyTmp = 124;//���� �� ���� ��ֵ
			//ʱ������
			else if( tp_dev.x>=100 && tp_dev.x<286 && tp_dev.y>=140 && tp_dev.y<320 )	KeyTmp = 125;//������ ���� ��ֵ
			//...��������...
			//..............
			else	KeyTmp = 65535;
		}
	}
	//���ӽ���
	else if( UICnt==0x01 )
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
			//ʱ��	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48 )	        KeyTmp = 121;// ʱ�� ���� ���� 
			//����  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 122;// ���� ���� ���� 
			//���  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 123;//��� ���� ���� 
			//��ʱ  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 124; //���� ���� ����
			
			else if( tp_dev.x>=30  && tp_dev.x<60  && tp_dev.y>=50 && tp_dev.y<80)  KeyTmp = 125;// ���� ���ӵ� ���ý���
			
			else if( tp_dev.x>=180 && tp_dev.x<195 && tp_dev.y>=50 && tp_dev.y<70 ) KeyTmp = 126; // ���� ���� ��

			else if( tp_dev.x>=195 && tp_dev.x<220 && tp_dev.y>=50 && tp_dev.y<70 ) KeyTmp = 127; //����  ���� ��
			
			else	KeyTmp = 65535;
		}
	}
	//������
	else if( UICnt==0x02 )
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
			//ʱ��	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48 )	        KeyTmp = 121;//ʱ��
			//����  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 122;//����
			//���  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 123; //���
			//��ʱ  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 124; //����
			
			else	KeyTmp = 65535;
		}	
	}
	//��ʱ����
	else if( UICnt==0x03 )
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
			//ʱ��	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48-16 )	        KeyTmp = 121;
			//����  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48-16 )	KeyTmp = 122;
			//���  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48-16 )	KeyTmp = 123;
			//��ʱ  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48-16 )	KeyTmp = 124;
			
			else if(tp_dev.y>32 && tp_dev.y < 32+32)
			{			  
				if(tp_dev.x>30   && tp_dev.x<48)       KeyTmp = 125;								
				if(tp_dev.x>180 && tp_dev.x<220)      KeyTmp   = 126;	     				
			}
			else if(tp_dev.y >93)
			{ 	
				  u8 row2,col2;  
					row2  = ((int)tp_dev.y-(74+19))/38;
					col2   = ((int)tp_dev.x)/34;
					KeyTmp = (7*row2)+ col2- Get_Week(2016,month,1)+1;	
			}
			//...��������...
			//..............
			else	KeyTmp = 65535;
		}	
		else	KeyTmp = 65535;
	}
	//ʱ�� ���ý���
	else if( UICnt==0x04)
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
					//���� 121
			if( tp_dev.x>=0 && tp_dev.x<50 && tp_dev.y>=0&& tp_dev.y<20 )	          KeyTmp = 121;
			else if( tp_dev.x>=200&& tp_dev.x<240 && tp_dev.y>=0 && tp_dev.y<20 )	  KeyTmp = 122;	//����	122
		
			else if( tp_dev.x>=40&& tp_dev.x<72 && tp_dev.y>=40 && tp_dev.y<50 )	  KeyTmp = 123;//��
			else if( tp_dev.x>=104&& tp_dev.x<138 && tp_dev.y>=40 && tp_dev.y<50 )    KeyTmp = 124;   
			else if( tp_dev.x>=146&& tp_dev.x<170 && tp_dev.y>=40 && tp_dev.y<50 )	  KeyTmp = 125;
				
			else if( tp_dev.x>=48&& tp_dev.x<80 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 126;
			else if( tp_dev.x>=96&& tp_dev.x<128 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 127;
			else if( tp_dev.x>=144&& tp_dev.x<176 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 128;   //se
			
			else if(tp_dev.y > 180)//���ý���  ������ 
			{
				num_x=tp_dev.x/80;
				num_y=(tp_dev.y-180)/35;	
				if(num_x>=0 && num_x<=2 &&  num_y>=0 && num_y<=2 )
				{
					num_x	=	num_x+num_y*3+1;
					return num_x;
				}
				
				else if(num_y==3)  //��� 1�� 
				{
					if(num_x==0)
					{
						return '*';   // 42
					}
					else if(num_x==1)
					{
						return 0;					
					} 
					else if(num_x==2)
					{
						return '#';  // 35
					}
				}

			}
		
			//...��������...
			//..............
			else	 KeyTmp = 65535;
		}
		else KeyTmp = 65535;
	}
	//���ӹ�������
	else if( UICnt==0x05 )
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
			//ʱ��	121
			if( tp_dev.x>=23 && tp_dev.x<55 && tp_dev.y>=0&& tp_dev.y<48 )	KeyTmp = 121;
			//����	122
			else if( tp_dev.x>=23+54 && tp_dev.x<55+54 && tp_dev.y>=0 && tp_dev.y<38 )	KeyTmp = 122;
			//...��������...
			//..............
			else	KeyTmp = 65535;
		}
	}
		//����  ���� ���� 
	else if( UICnt==0x06)
	{
		if ( tp_dev.sta )			//�����������Ļ
		{
					//���� 121
			if( tp_dev.x>=0 && tp_dev.x<50 && tp_dev.y>=0&& tp_dev.y<20 )	          KeyTmp = 121;
			else if( tp_dev.x>=200&& tp_dev.x<240 && tp_dev.y>=0 && tp_dev.y<20 )	  KeyTmp = 122;	//����	122
				
			else if( tp_dev.x>=96&& tp_dev.x<128 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 127;
			else if( tp_dev.x>=144&& tp_dev.x<176 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 128;   //se
			
			else if(tp_dev.y > 180)//���ý���  ������ 
			{
				num_x=tp_dev.x/80;
				num_y=(tp_dev.y-180)/35;	
				if(num_x>=0 && num_x<=2 &&  num_y>=0 && num_y<=2 )
				{
					num_x	=	num_x+num_y*3+1;
					return num_x;
				}
				
				else if(num_y==3)  //��� 1�� 
				{
					if(num_x==0)
					{
						return '*';   // 42
					}
					else if(num_x==1)
					{
						return 0;					
					} 
					else if(num_x==2)
					{
						return '#';  // 35
					}
				}

			}
		
			//...��������...
			//..............
			else	 KeyTmp = 65535;
		}
		else KeyTmp = 65535;
	}
	
	
	return KeyTmp;
}

void nao_change_min(void)
{        
	    
  		u16 TouchKey;
		u16 i=0;
		char cStr[ 40 ];
//		num =SetTime.Min;
		i=0;
			//��������...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" ,num1 );
		ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
			
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //���
				{
					num1 /= 10;
					if(i>0)
					i--;
					sprintf( cStr , "%02d" ,num1 );
					ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
				}

				else if(TouchKey>=0&&TouchKey<=9)
				{
					 while( tp_dev.sta ){}
					 if(i==0)
						num1 =0;								
						num1 *= 10;
						num1 += TouchKey;
						i++;
						if(i > 2)
						{
							i=0;
							num1=0;
						}
						sprintf( cStr , "%02d" ,num1);
						ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);				
				}	
				else if(TouchKey != 127  && TouchKey != 65535)
				{
				   if(TouchKey == '#' ) //ȷ��
				   {
//								while( tp_dev.sta );							
						if(num1>=0 && num1<=59)
						{
//							SetTime.Min = num;										
							sprintf( cStr , "%02d" ,num1 );
							ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macBLACK,macWHITE);
//							num1 =0;
							i=0;
						}	                        								
						else          //���벻����
						{
							 if(i != 0)
							 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"������Ӳ�����,����������",macBLACK ,macWHITE);
							 sprintf( cStr , "%02d" , num1);
							 ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macBLACK,macWHITE);
							 num1 =0;
							 i=0;
						}
						break;
				   }					
			   }							
		}

}
void nao_change_sec(void)
{
 		u16 TouchKey;
		u16 i=0;
		char	cStr[ 40 ];
//		num =SetTime.Sec;
		i=0;
			//��������...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" , num2 );
		ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);		
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //���
				{
						num2 /= 10;
						if(i>0)
						i--;
						sprintf( cStr , "%02d" ,num2 );
						ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);
				}
				else if(TouchKey>=0&&TouchKey<=9)
				{
					 while( tp_dev.sta ){}
					 if(i==0)
						 num2=0;					
						num2 *= 10;
						num2+= TouchKey;
						i++;
						if(i > 2)
						{
							i=0;
							num2 =0;
						}
						sprintf( cStr , "%02d" ,num2 );
						ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);
				
				}	
				else if(TouchKey != 127  && TouchKey != 65535)
				{
				   if(TouchKey == '#' ) //ȷ��
				   {
//						while( tp_dev.sta );				
						if(num2>=0 && num2<=59)
						{
//							SetTime.Sec = num;										
							sprintf( cStr , "%02d" ,num2 );
							ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macBLACK,macWHITE);
//							num =0;
							i=0;
						}				
						else          //���벻����
						{
							 if(i != 0)
							 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"�����벻����,����������",macBLACK ,macWHITE);
							 sprintf( cStr , "%02d" , num2 );
							 ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macBLACK,macWHITE);
//							 num =0;
							 i=0;
						}
						break;								
				   }	
				}																		
		}

}
void  change_year(void)
{
		u16 TouchKey;
		u16 num=0,i=0;
		char	cStr[ 40 ];
				num =0;
				i=0;
				//��������...
				while( tp_dev.sta );
				sprintf( cStr , "%02d" , SetTime.Year  );
				ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr, macWHITE,macBLACK);
				
				while(1)
				{
						  TouchKey = Get_TouchKey();
							if(TouchKey == '*' )  //���
							{
									num /= 10;
									if(i>0)
										i--;
									sprintf( cStr , "%04d" ,num );
									ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr, macWHITE,macBLACK);
							}

							else if(TouchKey>=0&&TouchKey<=9)
							{
								
								
									while( tp_dev.sta ){}
									num *= 10;
									num += TouchKey;
									i++;
									if(i > 4)
									{
										i=0;
										num =0;
									}
									sprintf( cStr , "%04d" ,num );
									ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr, macWHITE,macBLACK);
							
							}	
							else if(TouchKey != 123  && TouchKey != 65535)
							{
                                 if(TouchKey == '#' ) //ȷ��
							  {
//									while( tp_dev.sta );								
									if(num>=1970 && num<=2099)
									{
										SetTime.Year = num;										
										sprintf( cStr , "%04d" ,num );
										ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr,macBLACK, macWHITE);
										num =0;
										i=0;
									}	
																	
									else          //������ݲ�����
									{
										 if(i != 0)   //ʲô��û����
										 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"������ݲ�����,����������",macBLACK ,macWHITE);
										 sprintf( cStr , "%04d" ,SetTime.Year  );
										 ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr,macBLACK, macWHITE);
										 num =0;
										 i=0;
									}
								}
									break;																			
								
						}												
				}
}



void  change_month(void)
{
		u16 TouchKey;
		u16 num=0,i=0;
		char	cStr[ 40 ];
				num =0;
				i=0;
				//��������...
				while( tp_dev.sta );
				sprintf( cStr , "%02d" , SetTime.Month);
				ILI9341_DispString_EN_CH( 104,40,(const uint8_t *)cStr, macWHITE,macBLACK);
				
				while(1)
				{
						  TouchKey = Get_TouchKey();
							if(TouchKey == '*' )  //���
							{
									num /= 10;
									if(i>0)
									i--;
									sprintf( cStr , "%02d" ,num );
									ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr, macWHITE,macBLACK);
							}

							else if(TouchKey>=0&&TouchKey<=9)
							{
																
									while( tp_dev.sta ){}
									num *= 10;
									num += TouchKey;
									i++;
									if(i > 2)
									{
										i=0;
										num =0;
									}
									sprintf( cStr , "%02d" ,num );
									ILI9341_DispString_EN_CH( 104,40,(const uint8_t *)cStr, macWHITE,macBLACK);
							
							}	
							else if(TouchKey != 124  && TouchKey != 65535)
							{
								if(TouchKey == '#' ) //ȷ��
								{
//									while( tp_dev.sta )
								
									if(num>=1 && num<=12)
									{
										SetTime.Month = num;										
										sprintf( cStr , "%02d" ,num );
										ILI9341_DispString_EN_CH( 104,40,(const uint8_t *)cStr,macBLACK, macWHITE);
										num =0;
										i=0;
									}	
							
									else          //�������ݲ�����
									{
										 if(i != 0)
										 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"�����·ݲ�����,����������",macBLACK ,macWHITE);
										 sprintf( cStr , "%02d" ,SetTime.Month  );
										 ILI9341_DispString_EN_CH( 104,40,(const uint8_t *)cStr,macBLACK, macWHITE);
										 num =0;
										 i=0;
									}
								}	
									break;														
								}
																				
							
				}

}


void  change_day(void)
{
		u16 TouchKey;
		u16 num=0,i=0;
		char	cStr[ 40 ];
				num =0;
				i=0;
				//��������...
				while( tp_dev.sta );
				sprintf( cStr , "%02d" , SetTime.Day  );
				ILI9341_DispString_EN_CH( 152,40,(const uint8_t *)cStr, macWHITE,macBLACK);
				
				while(1)
				{
						  TouchKey = Get_TouchKey();
							if(TouchKey == '*' )  //���
							{
									num /= 10;
									if(i>0)
										i--;
									sprintf( cStr , "%02d" ,num );
									ILI9341_DispString_EN_CH( 152,40,(const uint8_t *)cStr, macWHITE,macBLACK);
							}
	
							else if(TouchKey>=0&&TouchKey<=9)
							{
								
								
									while( tp_dev.sta ){}
									num *= 10;
									num += TouchKey;
									i++;
									if(i > 2)
									{
										i=0;
										num =0;
									}
									sprintf( cStr , "%02d" ,num );
									ILI9341_DispString_EN_CH( 152,40,(const uint8_t *)cStr, macWHITE,macBLACK);
							
							}	
							else if(TouchKey != 125 && TouchKey != 65535)
							{
                				 if(TouchKey == '#' ) //ȷ��
						    	{
//									while( tp_dev.sta );
								
									if(num>=1 && num<=31)
									{
										SetTime.Day = num;										
										sprintf( cStr , "%02d" ,num );
										ILI9341_DispString_EN_CH( 152,40,(const uint8_t *)cStr,macBLACK, macWHITE);
										num =0;
										i=0;
									}
																	
									else          //���벻����
									{
										 if( i != 0)
										 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"�������ڲ�����,����������",macBLACK ,macWHITE);
										 sprintf( cStr , "%02d" ,SetTime.Day  );
										 ILI9341_DispString_EN_CH( 152,40,(const uint8_t *)cStr,macBLACK, macWHITE);
										 num =0;
										 i=0;
									}
								}
									break;
																									
			}																		
	}
}

void  change_hour(void)
{
		u16 TouchKey;
		u16 num=0,i=0;
		char	cStr[ 40 ];
		num =SetTime.Hour;
		i=0;
			//��������...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" , SetTime.Hour  );
		ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macWHITE,macBLACK);
			
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //���
				{
						num /= 10;
						if(i>0)
						 i--;
						sprintf( cStr , "%02d" ,num );
						ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macWHITE,macBLACK);
				}

				else if(TouchKey>=0&&TouchKey<=9)
				{
					 while( tp_dev.sta ){}
					 if(i==0)
					 num =0;						
					 num *= 10;
					 num += TouchKey;
					 i++;
					if(i > 2)
					{
						i=0;
						num =0;
					}
					sprintf( cStr , "%02d" ,num );
					ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macWHITE,macBLACK);
				
				}	
				else if(TouchKey != 126  && TouchKey != 65535)
				{
                    if(TouchKey == '#' ) //ȷ��
				  {
//					while( tp_dev.sta );				
					if(num>=0 && num<=23) //���õ�Сʱ ��Χ���� 0-23
					{
						SetTime.Hour = num;										
						sprintf( cStr , "%02d" ,num );
						ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macBLACK,macWHITE);
						num =0;
						i=0;
					}
								
					else          //���벻����
					{
						 if(i != 0)
						 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"����Сʱ������,����������",macBLACK ,macWHITE);
						 sprintf( cStr , "%02d" , SetTime.Hour  );
						 ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macBLACK,macWHITE);
						 num =0;
						 i=0;
					}
					  }	
					break;								
			}								
	}
}


void  change_min(void)
{
		u16 TouchKey;
		u16 num=0,i=0;
		char	cStr[ 40 ];
			num =SetTime.Min;
			i=0;
			//��������...
			while( tp_dev.sta );
			sprintf( cStr , "%02d" , SetTime.Min  );
			ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
			
			while(1)
			{
						TouchKey = Get_TouchKey();
						if(TouchKey == '*' )  //���
						{
								num /= 10;
								if(i>0)
									i--;
								sprintf( cStr , "%02d" ,num );
								ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
						}

						else if(TouchKey>=0&&TouchKey<=9)
						{
							 while( tp_dev.sta ){}
							 if(i==0)
								num =0;								
								num *= 10;
								num += TouchKey;
								i++;
								if(i > 2)
								{
									i=0;
									num =0;
								}
								sprintf( cStr , "%02d" ,num );
								ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
						
						}	
						else if(TouchKey != 127  && TouchKey != 65535)
						{
          	               if(TouchKey == '#' ) //ȷ��
						   {
//								while( tp_dev.sta );							
								if(num>=0 && num<=59)
								{
									SetTime.Min = num;										
									sprintf( cStr , "%02d" ,num );
									ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macBLACK,macWHITE);
									num =0;
									i=0;
								}	                        								
								else          //���벻����
								{
									 if(i != 0)
									 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"������Ӳ�����,����������",macBLACK ,macWHITE);
									 sprintf( cStr , "%02d" , SetTime.Min );
									 ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macBLACK,macWHITE);
									 num =0;
									 i=0;
								}
								break;
						   }					
					   }							
		}
}


void  change_sec(void)
{
		u16 TouchKey;
		u16 num=0,i=0;
		char	cStr[ 40 ];
		num =SetTime.Sec;
		i=0;
			//��������...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" , SetTime.Sec  );
		ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);		
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //���
				{
						num /= 10;
						if(i>0)
							i--;
						sprintf( cStr , "%02d" ,num );
						ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);
				}
				else if(TouchKey>=0&&TouchKey<=9)
				{
					 while( tp_dev.sta ){}
					 if(i==0)
						num =0;					
						num *= 10;
						num += TouchKey;
						i++;
						if(i > 2)
						{
							i=0;
							num =0;
						}
						sprintf( cStr , "%02d" ,num );
						ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);
				
				}	
				else if(TouchKey != 127  && TouchKey != 65535)
				{
				   if(TouchKey == '#' ) //ȷ��
				   {
//						while( tp_dev.sta );				
						if(num>=0 && num<=59)
						{
							SetTime.Sec = num;										
							sprintf( cStr , "%02d" ,num );
							ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macBLACK,macWHITE);
							num =0;
							i=0;
						}				
						else          //���벻����
						{
							 if(i != 0)
							 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"�����벻����,����������",macBLACK ,macWHITE);
							 sprintf( cStr , "%02d" , SetTime.Sec  );
							 ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macBLACK,macWHITE);
							 num =0;
							 i=0;
						}
						break;								
				   }	
				}																		
		}
}

/*********************************************END OF FILE**********************/

//�����������
//Year:��
//Month����
//CurrentDate:��ǰ����
//SelectDate:ѡ������
void DrawCalendar(unsigned int Year,unsigned int Month,unsigned int CurrentDate,unsigned int SelectDate)
{
	char	cStr[ 40 ];						//�����������ת�����ַ������ַ�
	unsigned int Row,Col;				//�������к�
	unsigned int CalWidth,CalHeight;	//����ÿ�����
	unsigned int ColOffset,RowOffset;	//����������ʾ�ַ�ʱ��������ƫ��ֵ
	unsigned int Cal_YOffset;		//�����������ƫ��ֵ
	unsigned int Date;					//����
	unsigned int DateMax;				//�����������
//	unsigned int Day;						//����
	unsigned int DayFirst;			//����1�����ڣ�1~6��������һ~��������0����������
	unsigned int jiagao;
	unsigned int Day;
	unsigned int hang;
	static unsigned int last_SelectDate;
	uint8_t str[15];

	//���û�ͼ����
	CalWidth = 34;//�ַ����ƫ��
	CalHeight = 20;//�ַ��߶�ƫ��
	RowOffset = 4;
	Cal_YOffset = 30+19; // 30+50
	hang = 7 ;
	//��������������
	DayFirst = Get_Week(Year,Month,1);	
	
	//�������������
	DateMax = DateMaxTab[Month];
	if(Month==2)
	{
		if(Is_LeapYear(Year)==1)DateMax++;
	}

	sprintf ( cStr, (const  char *) "%04d��%02d��", Year,Month );
	ILI9341_DispString_EN_CH(80,Cal_YOffset-20,(const uint8_t * )cStr,macBLACK,macWHITE);
	ILI9341_DispString_EN_CH(40,Cal_YOffset-20,"<",macBLACK,macWHITE);
    ILI9341_DispString_EN_CH(180,Cal_YOffset-20,">",macBLACK,macWHITE);

	// ��0�У���ʾ����
	Row = 0;
	ColOffset = 5;
	for(Col=0;Col<7;Col++)
	{
		if(Col==0 || Col==6)	ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset,DayTab[Col],macWHITE,macRED);
		else ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset,DayTab[Col],macWHITE,macBLACK);
	}
	// ��1-6�У���ʾ������
	Row = 1;
	Date = 1;
	//  ���µ� ��һ ����
	for(Col=DayFirst;Col<7;Col++) 
	{		 
		sprintf ( cStr, "%d", Date );
		ColOffset = 13;
		 /*����תũ������*/
		GetChinaCalendarStr(Year,(u8) Month,(u8) Date,str);
		
		if(Col==0 || Col==6)	
		{	
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macWHITE,macRED);
				/*��ʾũ������*/
			ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+28,str,macWHITE,macRED);
		}
		else 
		{
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macWHITE,macBLACK);
			/*��ʾũ������*/
			ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+28,str,macWHITE,macBLACK);
		}
		if(Date==CurrentDate)	ILI9341_DrawRectangle( Col*CalWidth , Cal_YOffset+Row*CalHeight+14, CalWidth-2 , CalHeight+16 , macBLUE , 0 );
		if(Date==SelectDate)	
		{
			ILI9341_DrawRectangle( Col*CalWidth, Cal_YOffset+Row*CalHeight+14, CalWidth-2 , CalHeight+16 , macRED , 1 );
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macRED,macBLACK);
			ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+28,str,macRED,macBLACK);	
		}
		else if(Date==last_SelectDate)
		{
			
			ILI9341_DrawRectangle( Col*CalWidth, Cal_YOffset+Row*CalHeight+14, CalWidth-2 , CalHeight+16 , macWHITE , 1 );
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macWHITE,macBLACK);
			ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+28,str,macWHITE,macBLACK);			
		
		}
	
		Day = Date + 28 ;
		Date++;
	}
	
	
  jiagao=30;//����ƫ��	
	if(Day>DateMax)
	hang = 6 ;
	for(Row=2;Row<hang;Row++)
	{
		
		for(Col=0;Col<7;Col++)
		{
			
     /*����תũ������*/
			GetChinaCalendarStr(Year,(u8) Month,(u8) Date,str);
			sprintf ( cStr, "%d", Date );
			if(Date<10) ColOffset = 13;
			else	ColOffset = 9;
			if(Col==0 || Col==6)	
			{	
					ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macRED);
					/*��ʾũ������*/
					ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macWHITE,macRED);		
			}
			else 
			{				
					ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macBLACK);
					/*��ʾũ������*/		
					ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macWHITE,macBLACK);	
			}
			
			if(Date==SelectDate)	
			{
	
				ILI9341_DrawRectangle( Col*CalWidth , Cal_YOffset+Row*CalHeight+2+jiagao , CalWidth-2 , CalHeight+16 , macRED , 1 );
				ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macRED,macWHITE);
                ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macRED,macWHITE);				
			}
			else if(Date==last_SelectDate)   // ���� ��һ�ε�  ����
			{
				if(Col==0 || Col==6)
				{
					ILI9341_DrawRectangle( Col*CalWidth , Cal_YOffset+Row*CalHeight+2+jiagao , CalWidth-2 , CalHeight+16 , macWHITE , 1 );
					ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macRED);
					ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macWHITE ,macRED);	
				
				}
				else
				{
					ILI9341_DrawRectangle( Col*CalWidth , Cal_YOffset+Row*CalHeight+2+jiagao , CalWidth-2 , CalHeight+16 , macWHITE , 1 );
					ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macBLACK);
					ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macWHITE ,macBLACK);			
				}					
						
			
			}
			if(Date==CurrentDate)	ILI9341_DrawRectangle( Col*CalWidth , Cal_YOffset+Row*CalHeight+2+jiagao , CalWidth-2 , CalHeight+16 , macBLUE , 0 );
			Date++;
		
			if(Date>DateMax)	break;
		}	
		
		jiagao = jiagao + 18;
		
		if(Date>DateMax)	break;
	}
	
	//��ʾ���һ�����������ڣ���ǳ��ɫ��ʾ
//	Row--;
	jiagao = jiagao - 18;
	if(Col<6)
	{
		Col++;
		Date = 1;
		for(;Col<7;Col++)
		{
			sprintf ( cStr, "%d", Date );
			ColOffset = 13;
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macBLUE2);		
			Date++;
		}	
	}
	//��ʾ��һ�����������ڣ���ǳ��ɫ��ʾ
	if(DayFirst!=0)
	{
		Month--;
		if(Month==0)
		{
			Year--;Month = 12;
		}
		
		DateMax = DateMaxTab[Month];
		if(Month==2)
		{
			if(Is_LeapYear(Year)==1)DateMax++;
		}
		
		Row = 1;
		Date = DateMax + 1 - DayFirst;		
		for(Col=0;Col<DayFirst;Col++)
		{
			sprintf ( cStr, "%d", Date );
			ColOffset = 9;
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macWHITE,macBLUE2);
			
			Date++;
		}	
	}	
	// Draw Line/*�»���*/
	for(Row=0;Row<hang;Row++) ILI9341_DrawLine(5,(Row+1)*(CalHeight+18)+Cal_YOffset-4,235,(Row+1)*(CalHeight+18)+Cal_YOffset-4,macBLUE2);
	
	last_SelectDate = SelectDate; //������һ�ε� ѡ��  ����ֵ
}

   

