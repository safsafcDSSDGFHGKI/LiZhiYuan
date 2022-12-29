#include "main.h"
#include "clock.h"
#include "math.h"
/*******************************  全局变量定义  *******************************/
u32                 Counter_miao_biao;                     //秒表
u16	 		        KeyNum;												//键值
u32			        KeyCnt,KeyUpCnt;								    //按键时间（单位10ms）,按键释放时间（单位10ms）
u8			        UICnt,UIRep;										//界面指针，界面指针备份
TimeStruct 			RealTime;								            //时钟
TimeStruct 			SetTime;                                             //set time 
CalendarStruct	    Calendar,LunarCalendar;	                             //公历，农历
Miao_Biao 	     	miao_biao;                                           //秒表
u16                 Last_Ui;                                             //用于屏保保存上一个ui界面
u16                 num1,num2;
/*****************************  全局变量定义结束  *****************************/

/*12-11 检查界面设计，打分   12-13 检查控制逻辑，打分     12-16 检查设计报告，ppt，打分     */
#define  PROTECTION_TIME  1*1000// 进入屏保时间 10s

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
			case	0x00:	UI00();	break; // 时钟界面
			case	0x01:	UI01();	break; // 闹钟界面
			case	0x02:	UI02();	break; // 秒表界面
			case	0x03:	UI03();	break; // 日历界面
			case	0x04:	UI04();	break; // 时钟设置界面
			case	0x05:	UI05();	break; // 
			case	0x06:	UI06();	break; // 闹钟 设置 界面
			case	0x10:	UI10();	break; //屏保界面

			default:	break;
		}
	}
}


/*******************************  数据表格  *******************************/
//星期显示字符串(英文)
const char DayTab[7][4] = {
	"Sun\0","Mon\0","Tue\0","Wed\0","Thu\0","Fri\0","Sat\0",
};

//星期显示字符串(中文)
const char DayTab_Han[7][3] = {
	"日\0","一\0","二\0","三\0","四\0","五\0","六\0",
};

//月最大日期表
const unsigned char DateMaxTab[13] = {
	0,31,28,31,30,31,30,31,31,30,31,30,31,
};

//农历日期表
const unsigned char LunarDateName[][5]=   {
	"  \0","初一\0","初二\0","初三\0","初四\0","初五\0","初六\0","初七\0","初八\0","初九\0","初十\0",
	"十一\0","十二\0","十三\0","十四\0","十五\0","十六\0","十七\0","十八\0","十九\0","二十\0",
	"廿一\0","廿二\0","廿三\0","廿四\0","廿五\0","廿六\0","廿七\0","廿八\0","廿九\0","三十\0"
};

//农历月份表
const unsigned char LunarMonthName[][5]=   {
	"  \0","正月\0","二月\0","三月\0","四月\0","五月\0","六月\0","七月\0","八月\0","九月\0","十月\0","冬月\0","腊月\0",
};


/*******************************  系统配置函数  *******************************/
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
	
	//必须先开启时钟再配置引脚
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

	
	//设置TIM2中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	//设置TIM6中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	//设置TIM7中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	//设置RTC中断
	//1级抢占式优先级,0级副优先级,使能引脚作为中断源
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}



/****************************************************************************
* 名    称：void TIM1_Configuration(void)
* 功    能：TIM1初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void TIM1_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	// 输出比较通道 GPIO 初始化
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_TIM1 , ENABLE );
		
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;	
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;		// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;	
	TIM_TimeBaseInit( TIM1 , &TIM_TimeBaseStructure);

	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;// 配置为PWM模式1	
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;// 输出使能	
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 500;// 设置占空比大小	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;// 有效电平为高
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;	//空闲输出低电平
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init( TIM1 , &TIM_OCInitStructure );
	TIM_OC1PreloadConfig( TIM1 , TIM_OCPreload_Enable );//使能TIM1 在 CCR1 上的预装载寄存器
	
	// 使能计数器
//	TIM_Cmd( TIM1 , ENABLE );	
	// 主输出使能，当使用的是通用定时器时，这句不需要
//	TIM_CtrlPWMOutputs( TIM1 , ENABLE );
}

/****************************************************************************
* 名    称：void TIM2_Configuration(void)
* 功    能：TIM2初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：设置定时器T2每10ms中断一次
* 调用方法：无 
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
* 名    称：void TIM6_Configuration(void)
* 功    能：TIM6初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：设置定时器T6每10ms中断一次
* 调用方法：无 
****************************************************************************/ 
void TIM6_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	TIM_DeInit(TIM6);
	
	TIM_TimeBaseStructure.TIM_Period = 99; 							//定时10ms
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
	

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);   
	TIM_Cmd(TIM6, ENABLE);
}

/****************************************************************************
* 名    称：void TIM7_Configuration(void)
* 功    能：TIM7初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：设置定时器T7每80ms中断一次,用于闹钟定时
* 调用方法：无 
****************************************************************************/ 
void TIM7_Configuration(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	
	TIM_DeInit(TIM7);
	
	TIM_TimeBaseStructure.TIM_Period = 799; 							//定时80ms
	TIM_TimeBaseStructure.TIM_Prescaler = 7199;
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);	

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);   
//	TIM_Cmd(TIM7, ENABLE);
}


 /**
  * @brief  LCD触摸屏校准或从外部flash读取校准系数
  * @param  无
  * @retval 无
  */	
void Flash_TouchCalibrate ( void )
{
	uint8_t ucStoreFlag;                            //LCD触摸屏校准系数存储标志
	
	SPI_FLASH_ReadDeviceID();                       // Get SPI Flash Device ID */
	
	SPI_FLASH_BufferRead ( & ucStoreFlag, 0, 1 );   //从外部flash读出LCD触摸屏校准系数存储标志
	
	if ( ucStoreFlag == 0x52 )                                                                         //已存储过LCD触摸屏校准系数
		SPI_FLASH_BufferRead ( ( void * )  & strXPT2046_TouchPara, 1, sizeof ( strXPT2046_TouchPara ) ); //继续读取LCD触摸屏校准系数
		
	else                                          //尚未存储过LCD触摸屏校准系数
	{
		while( ! XPT2046_Touch_Calibrate () );      //等待触摸屏校正完毕

		/* 存储LCD触摸屏校准系数和标志 */
		ucStoreFlag = 0x52;
		SPI_FLASH_SectorErase ( 0 );
		SPI_FLASH_BufferWrite ( & ucStoreFlag, 0, 1 );     
		SPI_FLASH_BufferWrite ( ( void * )  & strXPT2046_TouchPara, 1, sizeof ( strXPT2046_TouchPara ) );	
	}
	
//	SPI_Flash_PowerDown();                          //进入掉电模式
	
}

/****************************************************************************
* 名    称：void RTC_Configuration(void)
* 功    能：RTC初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：初始化RTC
* 调用方法：无 
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


/**************  功能函数  **************/

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
* 名    称：void Alarm( u8 cmd )
* 功    能：控制闹钟
* 入口参数：cmd	1:响铃	0:停止响铃
* 出口参数：
* 说    明：
* 调用方法：无 
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

/**************  日历功能函数  **************/


/****************************************************************************
* 名    称：u8 Is_Leap_Year(u16 year)
* 功    能：判断是否是闰年
* 入口参数：year
* 出口参数：1:是闰年；0:非闰年
* 说    明：
* 调用方法：无 
****************************************************************************/ 
u8 Is_LeapYear(u16 year)
{
	if(year%4==0) //必须能被4整除
	{ 
		if(year%100==0) 
		{
			if(year%400==0)return 1;//如果以00结尾,还要能被400整除
			else return 0; 
		}
		else return 1; 
	}
	else return 0;
} 

/****************************************************************************
* 名    称：u8 Get_Week(u16 Year,u16 Month,u16 Date)
* 功    能：用蔡勒（Zeller）公式计算星期几	

	w=y+[y/4]+[c/4]-2c+[26（m+1）/10]+d-1

	然后w对7取余。
	公式中的符号含义如下，w：星期；c：世纪；y：年（两位数）；m：月（m大于等于3，小
	于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的13、14月来计算，比如2003年1月1
	日要看作2002年的13月1日来计算）；d：日；[ ]代表取整，即只要整数部分。

* 入口参数：Year:年; Month:月; Date:日。
* 出口参数：星期几 1~6代表星期一~星期六，0代表星期天
* 说    明：
* 调用方法：无
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
* 名    称：u8 Set_RTCTime(TimeStruct *Time)
* 功    能：设置时钟:以1970-01-01 0:0:0为基准,把输入的时钟转换为秒钟,
* 					并写入RTC计数器，1970~2099年为合法年份。
* 入口参数：T_STRUCT* Time
* 出口参数：0:成功;
						1:错误代码，非有效时间(1970~2099)
* 说    明：
* 调用方法：Set_RTCTime(&RealTime);
****************************************************************************/ 
u8 Set_RTCTime( TimeStruct *Time)
{
	u32 Count = 0;
	u16 i;
	if(Time->Year<1970||Time->Year>2099) return 1;
	for(i=1970;i<Time->Year;i++)
	{
		if(Is_LeapYear(i)) Count += 31622400;		//闰年的秒数
		else Count += 31536000;									//平年的秒数
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
	
	//使能PWR和BKP外设时钟,这句一定不能省	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);	 
	PWR_BackupAccessCmd(ENABLE);	//使能RTC和后备寄存器访问 
	
	RTC_SetCounter(Count);
	RTC_WaitForLastTask();

	return 0;   
}




/****************************************************************************
* 名    称：void Cal_Time(u32 Count,TimeStruct *Time)
* 功    能：根据32位Count计数值计算日期和时间
* 入口参数：Count
* 出口参数：T_STRUCT* Time
* 说    明：
* 调用方法：Cal_Time(Count,&RealTime);
****************************************************************************/ 
void Cal_Time(u32 Count,TimeStruct *Time)
{
	u32 SecTemp=0,DateTemp=0,Temp=0;
	
	DateTemp = Count/86400;					//天数
	if(DateTemp!=0)							//超过1天
	{
		//确定年
		Temp = 1970;
		while(DateTemp>=365)
		{
			if(Is_LeapYear(Temp))	       //闰年?
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
		
		//确定月
		Temp = 1;
		while(DateTemp>=28)
		{
			if(Is_LeapYear(Time->Year)&&Temp==2)
			{
				if(DateTemp>=29)DateTemp -= 29;//闰年的二月天数
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
* 名    称：void Read_RTCTime(TimeStruct *Time)
* 功    能：从RTC计数器读取时间		
* 入口参数：T_STRUCT* Time
* 出口参数：无
* 说    明：
* 调用方法：Read_RTCTime(&RealTime);
****************************************************************************/ 
void Read_RTCTime( TimeStruct *Time)
{
	u32 Count = 0;
	Count = RTC_GetCounter();
	Cal_Time(Count,Time);
}






/**************  界面设计函数  **************/
void UI00( void )
{
	u16 TouchKey;
	char	cStr[ 40 ],Str[40];
	ILI9341_Clear(0,0,240,320,macBLACK);	
//	clock_base();  //时钟  表盘
	// 20 - 60    70-120  130 - 170  180 -220      y(16-48)
	ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"时钟",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"闹钟",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"秒表",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"月历",macBLACK ,macWHITE);
	calendar_circle_clock_drawpanel(120,140,160,9);
	ILI9341_DrawCircle( 120, 298, 20, macRED,1);   //画圆
	ILI9341_DispString_EN_CH( 104,290,(const uint8_t *)"设置",macRED,macWHITE);
	// 步骤1:调用LCD函数绘制图形界面
	// ILI9341_Clear(0,0,240,320,UI0BackColor);
	// ......
	// 步骤2:界面循环
	while(1)
	{
		  //显示指针
		 uint8_t second;   		
	{	
		if(second!=RealTime.Sec)   //防止时针 分针  秒针 抖动
		{	
		second=RealTime.Sec; 			
        calendar_circle_clock_showtime(120,140,160,9,RealTime.Hour,RealTime.Min,RealTime.Sec);//显示 时分秒	 
         }			
	}
		//更新时间
		//......
		//显示时间
		sprintf( cStr , "%02d-%02d-%02d " , RealTime.Year , RealTime.Month , RealTime.Date  );
						
		ILI9341_DispString_EN_CH( 60,240, (u8*)cStr ,macBLACK  ,  macWHITE);		
		sprintf( Str , " %02d:%02d:%02d %s" ,RealTime.Hour , RealTime.Min , RealTime.Sec ,DayTab_Han[Get_Week(RealTime.Year,RealTime.Month,RealTime.Date)]);

       ILI9341_DispString_EN_CH( 60,260, (u8*)Str ,macBLACK  ,  macWHITE);	
		
		//判断是否闹钟时间
		//......
		
		//按键处理
		if ( tp_dev.sta )
		{
			TouchKey = Get_TouchKey();
			
			if( TouchKey==121)
			{
				//按键功能...
				while( tp_dev.sta );
				UICnt = 0x00;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==122 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x01;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==123 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x02;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==124 )  // 日历
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x03;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==125)   //时钟设置界面
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x04;		//修改界面指针
				break;					//退出
			}
			
		}
			//进入屏保
		if(KeyUpCnt > PROTECTION_TIME)  // 
		{
			  Last_Ui = UICnt;
			  UICnt = 0x10;    //屏保界面
			  break;
		}		
	}
}


void UI01( void ) //闹钟 界面 工作 函数
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
	ILI9341_DispString_EN_CH(10,90,"日 一 二 三 四 五 六",macWHITE ,macBLACK);
	while(1)
	{	
	  ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"时钟",macBLACK ,macWHITE);
	  ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"闹钟",macBLACK ,macWHITE);
	  ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"秒表",macBLACK ,macWHITE);
	  ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"月历",macBLACK ,macWHITE);    
  
		sprintf( Str , " %02d:%02d " , num1 , num2 );
        ILI9341_DispString_EN_32( 30,50, (u8*)Str ,macWHITE,macBLACK);			
		//按键处理
		if ( tp_dev.sta )
	  {
			TouchKey = Get_TouchKey();			
			if( TouchKey==121)
			{				
				//按键功能...
				while( tp_dev.sta );
				UICnt = 0x00;		//修改界面指针  进入时钟 工作 界面
				break;					//退出
			}
			else if( TouchKey==122 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x01;		//修改界面指针  进入 闹钟 工作 界面
				break;					//退出
			}
			else if( TouchKey==123 )
			{
				//...
				while( tp_dev.sta );
				UICnt = 0x02;		//修改界面指针  进入 闹钟 工作 界面
				break;					//退出
			}

			else if(TouchKey==124)
			{
			  	while( tp_dev.sta );
				UICnt = 0x03;		//修改界面指针  进入 月历 工作 界面
				break;					//退出
			}
			else if(TouchKey==125)  
			{
			   	while( tp_dev.sta );
				UICnt = 0x06;		//修改界面指针  进入 闹钟 设置 工作 界面
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
		
		if(KeyUpCnt > PROTECTION_TIME) //进入屏保
		{
			Last_Ui = UICnt;
			UICnt = 0x10;    //屏保界面
			break;
		}
	}	
}

void UI02( void )//秒表界面
{
	u16 TouchKey;
	char cStr[20];
	ILI9341_Clear(0,0,240,20,macBLACK);
	ILI9341_Clear(0,20,240,300, macWHITE);

	ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"时钟",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"闹钟",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"秒表",macBLACK ,macWHITE);
    ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"月历",macBLACK ,macWHITE);    
	ILI9341_DrawRectangle(10,290,66,30,macBLUE2,1);
	ILI9341_DrawRectangle(86,290,66,30,macBLUE2 ,1);
	ILI9341_DrawRectangle(162,290,66,30,macBLUE2,1);
	ILI9341_DispString_CH(28,297,"计时",macBLUE2,macBLACK);
	ILI9341_DispString_CH(103,297,"清零",macBLUE2,macBLACK);
	ILI9341_DispString_CH(179,297,"暂停",macBLUE2,macBLACK);
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
				UICnt = 0x00;		//进入时钟界面
				break;					//退出
			}
			else if( TouchKey==122 )
			{			
				while( tp_dev.sta );
				UICnt = 0x01;		//进入秒表界面
				break;					//退出
			} 
			else if( TouchKey==123)  
			{
				while( tp_dev.sta );
				UICnt = 0x02;		//进入日历界面
				break;					//退出
			}
			else if( TouchKey==124)  
			{
				while( tp_dev.sta );
				UICnt = 0x03;		//进入日历界面
				break;					//退出
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
					
		 if(KeyUpCnt > PROTECTION_TIME)  //进入屏保
		{
		  Last_Ui = UICnt;
		  UICnt = 0x10;    //屏保界面
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
	ILI9341_DispString_EN_CH( 20,0,(const uint8_t *)"时钟",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 79,0,(const uint8_t *)"闹钟",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 134,0,(const uint8_t *)"秒表",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"月历",macBLACK ,macWHITE);
//	ILI9341_DrawCircle( 200, 42-16, 5, macRED,1 );   //画圆点

	while(1)
	{	
		if ( tp_dev.sta )	     
    {    			
				TouchKey = Get_TouchKey();	 
				if( TouchKey==121)
				{
					//按键功能...
					while( tp_dev.sta );
					UICnt = 0x00;		//修改界面指针
					break;					//退出
				}
				else if( TouchKey==122 )
				{
					//...
					while( tp_dev.sta );
					UICnt = 0x01;		//修改界面指针
					break;					//退出
				}
				else if( TouchKey==123 )
				{
					//...
					while( tp_dev.sta );
					UICnt = 0x02;		//修改界面指针
					break;					//退出
				}
				else if( TouchKey==124 )  // 日历
				{
					//...
					while( tp_dev.sta );
					UICnt = 0x03;		//修改界面指针
					break;					//退出
				}	
				else if( TouchKey==125 )  // 日历
				{
					//...
					while( tp_dev.sta );
					if(month<12)	{ month++; } else { month = 1;}      /*控制年份 加*/
					ILI9341_Clear(0,50,240,320,macWHITE);	
					DrawCalendar(2016,month,CurrentDate,SelectDate); 
				}	
				else if( TouchKey==126 )  // 日历
				{
					//...
					while( tp_dev.sta );
					if(month > 1)	{ month--; } else { month = 12;}     /*控制年份 减*/
					ILI9341_Clear(0,50,240,320,macWHITE);	
					DrawCalendar(2016,month,CurrentDate,SelectDate); 
				}				
				else if(TouchKey != 65535)
				{		
						SelectDate = TouchKey;
						DrawCalendar(RealTime.Year,month,CurrentDate,TouchKey);/*选中的 日期*/			
				}
		 }	
					//进入屏保
			if(KeyUpCnt > PROTECTION_TIME)  // 15秒
			{
				  Last_Ui = UICnt;
					UICnt = 0x10;    //屏保界面
					break;
			}		  	
	}
}
void UI04( void )   //时钟设置界面
{
	char	cStr[ 40 ];
	u16 num=0,i=0,m,k=35;
	
	u16 TouchKey;
	ILI9341_Clear(0,0,240,320,macBLACK);  //清屏
	
	SetTime = RealTime;
	ILI9341_DispString_EN_CH( 0,5,(const uint8_t *)"<<返回",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 190,5,(const uint8_t *)"保存>>",macBLACK ,macWHITE);
	
	sprintf( cStr , "%02d 年 %02d 月 %02d 日" , RealTime.Year , RealTime.Month , RealTime.Date );
	ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr,macBLACK ,macWHITE);
	
	sprintf( cStr , "%02d:%02d:%02d " , RealTime.Hour , RealTime.Min , RealTime.Sec );
	
	ILI9341_DispString_EN_32( 48,60,(const char *)cStr,macBLACK ,macWHITE);

	for(m=0;m<4;m++)
	{
	ILI9341_DrawRectangle(6,   180+m*35,  72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(84,  180+m*35, 72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(162, 180+m*35, 72, 30, macBLUE2, 1 );
	
	}
	ILI9341_Clear(78,180,6,135,macGREY);   //竖线
    ILI9341_Clear(156,180,6,135,macGREY);   //竖线
    
	ILI9341_Clear(6,210,228,6,macGREY);   //竖线
    ILI9341_Clear(6,245,228,6,macGREY);   //竖线
	ILI9341_Clear(6,280,228,6,macGREY);   //竖线

	ILI9341_DispChar_EN( 39, 187, '1', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 39, 222, '4', macBLUE2, macRED );
	ILI9341_DispChar_EN( 39, 257, '7', macBLUE2, macRED );	
	ILI9341_DispString_CH( 26, 290, (const uint8_t *)"清除", macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 116, 187, '2', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 222, '5', macBLUE2, macRED );
	ILI9341_DispChar_EN( 116, 257, '8', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 292, '0', macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 194, 187, '3', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 194, 222, '6', macBLUE2, macRED );
	ILI9341_DispChar_EN( 194, 257, '9', macBLUE2, macRED );	
	ILI9341_DispString_CH( 182, 290, (const uint8_t *)"确定", macBLUE2, macRED );
		
	while(1)
	{		   
		//按键处理
		if ( tp_dev.sta )
		{
		
//			ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"                         ",macBLACK ,macBLACK);
			TouchKey = Get_TouchKey();
			if( TouchKey==121)
			{
								//...
				while( tp_dev.sta );
				UICnt = 0x00;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==122 )  //保存
			{
				//按键功能...
//				while( tp_dev.sta );
				Set_RTCTime(&SetTime);
				Delay(1000);
				UICnt = 0x00;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==123 )  // year
			{
               change_year();	
			}
			else if( TouchKey==124 )
			{
				//按键功能...
//				while( tp_dev.sta );
				    change_month();
			}
			else if( TouchKey==125 )
			{
				//按键功能...
//				while( tp_dev.sta );
				   change_day();
			}
			else if( TouchKey==126 )
			{
				//按键功能...
//				while( tp_dev.sta );
				  change_hour();
			}
			else if( TouchKey==127 )
			{
				//按键功能...
//				while( tp_dev.sta );
				change_min();
			}
			else if( TouchKey==128 )
			{
				//按键功能...
//				while( tp_dev.sta );
				change_sec();
			}
		}		
		//进入屏保
		if(KeyUpCnt > PROTECTION_TIME)  // 10秒
		{
			    Last_Ui = UICnt;
				UICnt = 0x10;    //屏保界面
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
void UI06( void ) //闹钟 界面 设计 函数 
{
	char	cStr[ 40 ];
	u16 num=0,i=0,m,k=35;
	
	u16 TouchKey;
	ILI9341_Clear(0,0,240,320,macBLACK);  //清屏
	
	SetTime = RealTime;
	ILI9341_DispString_EN_CH( 0,5,(const uint8_t *)"<<返回",macBLACK ,macWHITE);
	ILI9341_DispString_EN_CH( 190,5,(const uint8_t *)"保存>>",macBLACK ,macWHITE);
		
	sprintf( cStr , "%02d:%02d " , num1,num2);
	
	ILI9341_DispString_EN_32( 96,60,(const char *)cStr,macBLACK ,macWHITE);

	for(m=0;m<4;m++)
	{
	ILI9341_DrawRectangle(6,   180+m*35,  72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(84,  180+m*35, 72, 30, macBLUE2, 1 );
	ILI9341_DrawRectangle(162, 180+m*35, 72, 30, macBLUE2, 1 );	
	}
	ILI9341_Clear(78,180,6,135,macGREY);   //竖线
    ILI9341_Clear(156,180,6,135,macGREY);   //竖线
    
	ILI9341_Clear(6,210,228,6,macGREY);   //竖线
    ILI9341_Clear(6,245,228,6,macGREY);   //竖线
	ILI9341_Clear(6,280,228,6,macGREY);   //竖线

	ILI9341_DispChar_EN( 39, 187, '1', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 39, 222, '4', macBLUE2, macRED );
	ILI9341_DispChar_EN( 39, 257, '7', macBLUE2, macRED );	
	ILI9341_DispString_CH( 26, 290, (const uint8_t *)"清除", macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 116, 187, '2', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 222, '5', macBLUE2, macRED );
	ILI9341_DispChar_EN( 116, 257, '8', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 116, 292, '0', macBLUE2, macRED );
	
	ILI9341_DispChar_EN( 194, 187, '3', macBLUE2, macRED );	
	ILI9341_DispChar_EN( 194, 222, '6', macBLUE2, macRED );
	ILI9341_DispChar_EN( 194, 257, '9', macBLUE2, macRED );	
	ILI9341_DispString_CH( 182, 290, (const uint8_t *)"确定", macBLUE2, macRED );
		
	while(1)
	{		   
		//按键处理
		if ( tp_dev.sta )
		{		
			ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"                         ",macBLACK ,macBLACK);
			TouchKey = Get_TouchKey();
			if( TouchKey==121)
			{
				while( tp_dev.sta );
				UICnt = 0x01;		//修改界面指针
				break;					//退出
			}
			else if( TouchKey==122 )  //保存
			{
//				Set_RTCTime(&SetTime);//这里 设置好的 RTC要 返回 给 闹钟工作函数 
				Delay(1000);
				UICnt = 0x01;		//修改界面指针
				break;					//退出
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
		
		//进入屏保
		if(KeyUpCnt > PROTECTION_TIME)  // 10秒
		{
			  Last_Ui = UICnt;
			  UICnt = 0x10;    //屏保界面
			  break;
		}
	}
	
	
}
void UI10( void )  // 屏保界面
{
	char cStr[40];
	ILI9341_Clear(0,0,240,320,macBLACK);
	ILI9341_DrawRectangle(0, 120, 240, 120,macWHITE, 1 );
	
	while(1)
	{
		
	sprintf( cStr , "%02d:%02d:%02d" , RealTime.Hour , RealTime.Min , RealTime.Sec );//显示时间
					 
	ILI9341_DispString_EN_48( 20,120, (const char *)cStr ,macWHITE  ,macBLACK  );	
	
	sprintf( cStr ,"%02d-%02d-%02d  %s" ,RealTime.Year , RealTime.Month , RealTime.Date , DayTab_Han[Get_Week(RealTime.Year,RealTime.Month,RealTime.Date)]); 
					
	ILI9341_DispString_EN_CH( 20,180, (u8*)cStr ,macWHITE  , macBLACK );	
		
	ILI9341_DispString_EN_CH(20,200,"电子A1321-04-胡新旺",macWHITE  , macBLACK);
	if ( tp_dev.sta )//按键处理
	{				
		UICnt =Last_Ui ;	
		KeyUpCnt = 0;
		break;
	}
	}
}


/**************  触屏扫描函数  **************/
u16 Get_TouchKey( void )
{
	u16	KeyTmp;
	u8  num_x;
	u16 num_y;
	
	//时钟界面
	if( UICnt==0x00 )				
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
			//时钟	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48 )	           KeyTmp = 121;  //时钟的返回键值 
			//闹钟  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48 )	    KeyTmp = 122; //闹钟的返回 键值 
			//秒表  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48 )  	KeyTmp = 123; //秒表 的 返回 键值
			//计时  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48 )  	KeyTmp = 124;//月历 的 返回 键值
			//时钟设置
			else if( tp_dev.x>=100 && tp_dev.x<286 && tp_dev.y>=140 && tp_dev.y<320 )	KeyTmp = 125;//月历的 返回 键值
			//...其他区域...
			//..............
			else	KeyTmp = 65535;
		}
	}
	//闹钟界面
	else if( UICnt==0x01 )
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
			//时钟	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48 )	        KeyTmp = 121;// 时钟 工作 界面 
			//闹钟  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 122;// 闹钟 工作 界面 
			//秒表  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 123;//秒表 工作 界面 
			//计时  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 124; //月历 工作 界面
			
			else if( tp_dev.x>=30  && tp_dev.x<60  && tp_dev.y>=50 && tp_dev.y<80)  KeyTmp = 125;// 进入 闹钟的 设置界面
			
			else if( tp_dev.x>=180 && tp_dev.x<195 && tp_dev.y>=50 && tp_dev.y<70 ) KeyTmp = 126; // 闹钟 设置 开

			else if( tp_dev.x>=195 && tp_dev.x<220 && tp_dev.y>=50 && tp_dev.y<70 ) KeyTmp = 127; //闹钟  设置 关
			
			else	KeyTmp = 65535;
		}
	}
	//秒表界面
	else if( UICnt==0x02 )
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
			//时钟	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48 )	        KeyTmp = 121;//时钟
			//闹钟  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 122;//闹钟
			//秒表  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 123; //秒表
			//计时  124
			else if( tp_dev.x>=180 && tp_dev.x<220 && tp_dev.y>=0 && tp_dev.y<48 )	KeyTmp = 124; //月历
			
			else	KeyTmp = 65535;
		}	
	}
	//定时界面
	else if( UICnt==0x03 )
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
			//时钟	121
			if( tp_dev.x>=20 && tp_dev.x<60 && tp_dev.y>=0&& tp_dev.y<48-16 )	        KeyTmp = 121;
			//闹钟  122
			else if( tp_dev.x>=70 && tp_dev.x<120 && tp_dev.y>=0 && tp_dev.y<48-16 )	KeyTmp = 122;
			//秒表  123
			else if( tp_dev.x>=130 && tp_dev.x<170 && tp_dev.y>=0 && tp_dev.y<48-16 )	KeyTmp = 123;
			//计时  124
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
			//...其他区域...
			//..............
			else	KeyTmp = 65535;
		}	
		else	KeyTmp = 65535;
	}
	//时钟 设置界面
	else if( UICnt==0x04)
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
					//返回 121
			if( tp_dev.x>=0 && tp_dev.x<50 && tp_dev.y>=0&& tp_dev.y<20 )	          KeyTmp = 121;
			else if( tp_dev.x>=200&& tp_dev.x<240 && tp_dev.y>=0 && tp_dev.y<20 )	  KeyTmp = 122;	//保存	122
		
			else if( tp_dev.x>=40&& tp_dev.x<72 && tp_dev.y>=40 && tp_dev.y<50 )	  KeyTmp = 123;//年
			else if( tp_dev.x>=104&& tp_dev.x<138 && tp_dev.y>=40 && tp_dev.y<50 )    KeyTmp = 124;   
			else if( tp_dev.x>=146&& tp_dev.x<170 && tp_dev.y>=40 && tp_dev.y<50 )	  KeyTmp = 125;
				
			else if( tp_dev.x>=48&& tp_dev.x<80 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 126;
			else if( tp_dev.x>=96&& tp_dev.x<128 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 127;
			else if( tp_dev.x>=144&& tp_dev.x<176 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 128;   //se
			
			else if(tp_dev.y > 180)//设置界面  触摸屏 
			{
				num_x=tp_dev.x/80;
				num_y=(tp_dev.y-180)/35;	
				if(num_x>=0 && num_x<=2 &&  num_y>=0 && num_y<=2 )
				{
					num_x	=	num_x+num_y*3+1;
					return num_x;
				}
				
				else if(num_y==3)  //最后 1行 
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
		
			//...其他区域...
			//..............
			else	 KeyTmp = 65535;
		}
		else KeyTmp = 65535;
	}
	//闹钟工作界面
	else if( UICnt==0x05 )
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
			//时钟	121
			if( tp_dev.x>=23 && tp_dev.x<55 && tp_dev.y>=0&& tp_dev.y<48 )	KeyTmp = 121;
			//闹钟	122
			else if( tp_dev.x>=23+54 && tp_dev.x<55+54 && tp_dev.y>=0 && tp_dev.y<38 )	KeyTmp = 122;
			//...其他区域...
			//..............
			else	KeyTmp = 65535;
		}
	}
		//闹钟  设置 界面 
	else if( UICnt==0x06)
	{
		if ( tp_dev.sta )			//如果触摸了屏幕
		{
					//返回 121
			if( tp_dev.x>=0 && tp_dev.x<50 && tp_dev.y>=0&& tp_dev.y<20 )	          KeyTmp = 121;
			else if( tp_dev.x>=200&& tp_dev.x<240 && tp_dev.y>=0 && tp_dev.y<20 )	  KeyTmp = 122;	//保存	122
				
			else if( tp_dev.x>=96&& tp_dev.x<128 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 127;
			else if( tp_dev.x>=144&& tp_dev.x<176 && tp_dev.y>=60 && tp_dev.y<92 )	  KeyTmp = 128;   //se
			
			else if(tp_dev.y > 180)//设置界面  触摸屏 
			{
				num_x=tp_dev.x/80;
				num_y=(tp_dev.y-180)/35;	
				if(num_x>=0 && num_x<=2 &&  num_y>=0 && num_y<=2 )
				{
					num_x	=	num_x+num_y*3+1;
					return num_x;
				}
				
				else if(num_y==3)  //最后 1行 
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
		
			//...其他区域...
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
			//按键功能...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" ,num1 );
		ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
			
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //清除
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
				   if(TouchKey == '#' ) //确认
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
						else          //输入不符合
						{
							 if(i != 0)
							 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入分钟不符合,请重新输入",macBLACK ,macWHITE);
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
			//按键功能...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" , num2 );
		ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);		
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //清除
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
				   if(TouchKey == '#' ) //确认
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
						else          //输入不符合
						{
							 if(i != 0)
							 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入秒不符合,请重新输入",macBLACK ,macWHITE);
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
				//按键功能...
				while( tp_dev.sta );
				sprintf( cStr , "%02d" , SetTime.Year  );
				ILI9341_DispString_EN_CH( 40,40,(const uint8_t *)cStr, macWHITE,macBLACK);
				
				while(1)
				{
						  TouchKey = Get_TouchKey();
							if(TouchKey == '*' )  //清除
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
                                 if(TouchKey == '#' ) //确认
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
																	
									else          //输入年份不符合
									{
										 if(i != 0)   //什么都没输入
										 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入年份不符合,请重新输入",macBLACK ,macWHITE);
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
				//按键功能...
				while( tp_dev.sta );
				sprintf( cStr , "%02d" , SetTime.Month);
				ILI9341_DispString_EN_CH( 104,40,(const uint8_t *)cStr, macWHITE,macBLACK);
				
				while(1)
				{
						  TouchKey = Get_TouchKey();
							if(TouchKey == '*' )  //清除
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
								if(TouchKey == '#' ) //确认
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
							
									else          //输入数据不符合
									{
										 if(i != 0)
										 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入月份不符合,请重新输入",macBLACK ,macWHITE);
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
				//按键功能...
				while( tp_dev.sta );
				sprintf( cStr , "%02d" , SetTime.Day  );
				ILI9341_DispString_EN_CH( 152,40,(const uint8_t *)cStr, macWHITE,macBLACK);
				
				while(1)
				{
						  TouchKey = Get_TouchKey();
							if(TouchKey == '*' )  //清除
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
                				 if(TouchKey == '#' ) //确认
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
																	
									else          //输入不符合
									{
										 if( i != 0)
										 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入日期不符合,请重新输入",macBLACK ,macWHITE);
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
			//按键功能...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" , SetTime.Hour  );
		ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macWHITE,macBLACK);
			
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //清除
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
                    if(TouchKey == '#' ) //确认
				  {
//					while( tp_dev.sta );				
					if(num>=0 && num<=23) //设置的小时 范围符合 0-23
					{
						SetTime.Hour = num;										
						sprintf( cStr , "%02d" ,num );
						ILI9341_DispString_EN_32( 48,60,(const char *)cStr, macBLACK,macWHITE);
						num =0;
						i=0;
					}
								
					else          //输入不符合
					{
						 if(i != 0)
						 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入小时不符合,请重新输入",macBLACK ,macWHITE);
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
			//按键功能...
			while( tp_dev.sta );
			sprintf( cStr , "%02d" , SetTime.Min  );
			ILI9341_DispString_EN_32( 96,60,(const char *)cStr, macWHITE,macBLACK);
			
			while(1)
			{
						TouchKey = Get_TouchKey();
						if(TouchKey == '*' )  //清除
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
          	               if(TouchKey == '#' ) //确认
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
								else          //输入不符合
								{
									 if(i != 0)
									 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入分钟不符合,请重新输入",macBLACK ,macWHITE);
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
			//按键功能...
		while( tp_dev.sta );
		sprintf( cStr , "%02d" , SetTime.Sec  );
		ILI9341_DispString_EN_32( 144,60,(const char *)cStr, macWHITE,macBLACK);		
		while(1)
		{
				TouchKey = Get_TouchKey();
				if(TouchKey == '*' )  //清除
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
				   if(TouchKey == '#' ) //确认
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
						else          //输入不符合
						{
							 if(i != 0)
							 ILI9341_DispString_EN_CH( 10,128,(const uint8_t *)"输入秒不符合,请重新输入",macBLACK ,macWHITE);
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

//绘制日历表格
//Year:年
//Month：月
//CurrentDate:当前日期
//SelectDate:选定日期
void DrawCalendar(unsigned int Year,unsigned int Month,unsigned int CurrentDate,unsigned int SelectDate)
{
	char	cStr[ 40 ];						//用来存放数字转换成字符串的字符
	unsigned int Row,Col;				//日历行列号
	unsigned int CalWidth,CalHeight;	//日历每格宽，高
	unsigned int ColOffset,RowOffset;	//日历格中显示字符时横向、纵向偏移值
	unsigned int Cal_YOffset;		//日历表格纵向偏移值
	unsigned int Date;					//日期
	unsigned int DateMax;				//当月最大日期
//	unsigned int Day;						//星期
	unsigned int DayFirst;			//当月1号星期，1~6代表星期一~星期六，0代表星期天
	unsigned int jiagao;
	unsigned int Day;
	unsigned int hang;
	static unsigned int last_SelectDate;
	uint8_t str[15];

	//设置绘图参数
	CalWidth = 34;//字符宽度偏移
	CalHeight = 20;//字符高度偏移
	RowOffset = 4;
	Cal_YOffset = 30+19; // 30+50
	hang = 7 ;
	//计算月首日星期
	DayFirst = Get_Week(Year,Month,1);	
	
	//计算月最大日期
	DateMax = DateMaxTab[Month];
	if(Month==2)
	{
		if(Is_LeapYear(Year)==1)DateMax++;
	}

	sprintf ( cStr, (const  char *) "%04d年%02d月", Year,Month );
	ILI9341_DispString_EN_CH(80,Cal_YOffset-20,(const uint8_t * )cStr,macBLACK,macWHITE);
	ILI9341_DispString_EN_CH(40,Cal_YOffset-20,"<",macBLACK,macWHITE);
    ILI9341_DispString_EN_CH(180,Cal_YOffset-20,">",macBLACK,macWHITE);

	// 第0行，显示星期
	Row = 0;
	ColOffset = 5;
	for(Col=0;Col<7;Col++)
	{
		if(Col==0 || Col==6)	ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset,DayTab[Col],macWHITE,macRED);
		else ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset,DayTab[Col],macWHITE,macBLACK);
	}
	// 第1-6行，显示日历表
	Row = 1;
	Date = 1;
	//  当月的 第一 星期
	for(Col=DayFirst;Col<7;Col++) 
	{		 
		sprintf ( cStr, "%d", Date );
		ColOffset = 13;
		 /*公历转农历函数*/
		GetChinaCalendarStr(Year,(u8) Month,(u8) Date,str);
		
		if(Col==0 || Col==6)	
		{	
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macWHITE,macRED);
				/*显示农历日期*/
			ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+28,str,macWHITE,macRED);
		}
		else 
		{
			ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+10,cStr,macWHITE,macBLACK);
			/*显示农历日期*/
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
	
	
  jiagao=30;//向下偏移	
	if(Day>DateMax)
	hang = 6 ;
	for(Row=2;Row<hang;Row++)
	{
		
		for(Col=0;Col<7;Col++)
		{
			
     /*公历转农历函数*/
			GetChinaCalendarStr(Year,(u8) Month,(u8) Date,str);
			sprintf ( cStr, "%d", Date );
			if(Date<10) ColOffset = 13;
			else	ColOffset = 9;
			if(Col==0 || Col==6)	
			{	
					ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macRED);
					/*显示农历日期*/
					ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macWHITE,macRED);		
			}
			else 
			{				
					ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macWHITE,macBLACK);
					/*显示农历日期*/		
					ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macWHITE,macBLACK);	
			}
			
			if(Date==SelectDate)	
			{
	
				ILI9341_DrawRectangle( Col*CalWidth , Cal_YOffset+Row*CalHeight+2+jiagao , CalWidth-2 , CalHeight+16 , macRED , 1 );
				ILI9341_DispString_EN(Col*CalWidth+ColOffset,Cal_YOffset+Row*CalHeight+RowOffset+jiagao,cStr,macRED,macWHITE);
                ILI9341_DispString_CH(Col*CalWidth,Cal_YOffset+Row*CalHeight+RowOffset+jiagao+18,str,macRED,macWHITE);				
			}
			else if(Date==last_SelectDate)   // 擦除 上一次的  矩形
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
	
	//显示最后一周中下月日期，用浅蓝色显示
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
	//显示第一周中上月日期，用浅蓝色显示
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
	// Draw Line/*下划线*/
	for(Row=0;Row<hang;Row++) ILI9341_DrawLine(5,(Row+1)*(CalHeight+18)+Cal_YOffset-4,235,(Row+1)*(CalHeight+18)+Cal_YOffset-4,macBLUE2);
	
	last_SelectDate = SelectDate; //保存上一次的 选中  日期值
}

   

