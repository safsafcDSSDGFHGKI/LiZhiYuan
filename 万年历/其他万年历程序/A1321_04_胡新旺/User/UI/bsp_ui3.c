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
