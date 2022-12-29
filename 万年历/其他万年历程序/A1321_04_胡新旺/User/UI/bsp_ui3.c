#include "main.h"
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
	ILI9341_DispString_EN_CH( 184,0,(const uint8_t *)"日历",macBLACK ,macWHITE);
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
