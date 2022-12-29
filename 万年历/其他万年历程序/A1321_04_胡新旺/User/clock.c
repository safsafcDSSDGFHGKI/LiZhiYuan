#include "stm32f10x.h" 
#include "bsp_ili9341_lcd.h"
#include "clock.h"
#include "math.h"
#define pi 3.1415926
/*******************************************************************************/
//��һ������
//x0,y0:��� x1,y1:�յ�
//size:�ߴ�ϸ,��֧��:0~2.
//color:��ɫ
void gui_draw_bline1(u16 x0,u16 y0,u16 x1,u16 y1,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x1-x0; //������������ 
	delta_y=y1-y0; 
	uRow=x0; 
	uCol=y0; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		if(size==0)ILI9341_SetPointPixel(uRow,uCol,color);//���� 
		if(size==1)
		{
			ILI9341_SetPointPixel(uRow,uCol,color);//���� 
			ILI9341_SetPointPixel(uRow+1,uCol,color);//���� 
			ILI9341_SetPointPixel(uRow,uCol+1,color);//���� 
			ILI9341_SetPointPixel(uRow+1,uCol+1,color);//���� 
		}
		if(size==2)
		{
			ILI9341_SetPointPixel(uRow,uCol,color);//���� 
			ILI9341_SetPointPixel(uRow+1,uCol,color);//���� 
			ILI9341_SetPointPixel(uRow,uCol+1,color);//���� 
			ILI9341_SetPointPixel(uRow+1,uCol+1,color);//���� 
			ILI9341_SetPointPixel(uRow-1,uCol+1,color);//���� 
			ILI9341_SetPointPixel(uRow+1,uCol-1,color);//����
			ILI9341_SetPointPixel(uRow-1,uCol-1,color);//����  
			ILI9341_SetPointPixel(uRow-1,uCol,color);//���� 
			ILI9341_SetPointPixel(uRow,uCol-1,color);//����  
		}
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	} 				 
}

//��Բ��ָ�����
//x,y:�������ĵ�
//size:���̴�С(ֱ��)
//d:���̷ָ�,���ӵĸ߶�
void calendar_circle_clock_drawpanel(u16 x,u16 y,u16 size,u16 d)
{
	u16 r=size/2;//�õ��뾶 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1; 
	u16 i; 
	ILI9341_DrawCircle(x,y,r,macWHITE,0);		//����Ȧ
	ILI9341_DrawCircle(x,y,r-4,macWHITE,0);		//����Ȧ
	for(i=0;i<60;i++)//�����Ӹ�
	{ 
		px0=sx+r+(r-4)*sin((pi/30)*i); 
		py0=sy+r-(r-4)*cos((pi/30)*i); 
		px1=sx+r+(r-d)*sin((pi/30)*i); 
		py1=sy+r-(r-d)*cos((pi/30)*i);  
		gui_draw_bline1(px0,py0,px1,py1,0,macWHITE);		
	}
	for(i=0;i<12;i++)//��Сʱ��
	{ 
		px0=sx+r+(r-5)*sin((pi/6)*i); 
		py0=sy+r-(r-5)*cos((pi/6)*i); 
		px1=sx+r+(r-d)*sin((pi/6)*i); 
		py1=sy+r-(r-d)*cos((pi/6)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,macYELLOW);		
	}
	for(i=0;i<4;i++)//��3Сʱ��
	{ 
		px0=sx+r+(r-5)*sin((pi/2)*i); 
		py0=sy+r-(r-5)*cos((pi/2)*i); 
		px1=sx+r+(r-d-3)*sin((pi/2)*i); 
		py1=sy+r-(r-d-3)*cos((pi/2)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,macYELLOW);		
	}
	ILI9341_DrawCircle(x,y,d/2,macWHITE,1);		//������Ȧ
   
}
/*******************************************************************************************
�������ܣ���ʾʱ��
�β�:x  y �������ĵ� size���̴�Сֱ��  d ���̷ָ� ���ӵĸ߶� hourʱ�� min ����sec����
����ֵ:��
*******************************************************************************************/
void calendar_circle_clock_showtime(u16 x,u16 y,u16 size,u16 d,u8 hour,u8 min,u8 sec)
{
	static u8 oldhour=0;	//���һ�ν���ú�����ʱ������Ϣ
	static u8 oldmin=0;
	static u8 oldsec=0;
	float temp;
	u16 r=size/2;//�õ��뾶 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1;  
	u8 r1; 
	if(hour>11)hour-=12;
///////////////////////////////////////////////
	//���Сʱ
	r1=d/2+4;
	//�����һ�ε�����
	temp=(float)oldmin/60;
	temp+=oldhour;
	px0=sx+r+(r-3*d-7)*sin((pi/6)*temp); 
	py0=sy+r-(r-3*d-7)*cos((pi/6)*temp); 
	px1=sx+r+r1*sin((pi/6)*temp); 
	py1=sy+r-r1*cos((pi/6)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,2,macBLACK);
	//�������
	r1=d/2+3;
	temp=(float)oldsec/60;
	temp+=oldmin;
	//�����һ�ε�����
	px0=sx+r+(r-2*d-7)*sin((pi/30)*temp); 
	py0=sy+r-(r-2*d-7)*cos((pi/30)*temp); 
	px1=sx+r+r1*sin((pi/30)*temp); 
	py1=sy+r-r1*cos((pi/30)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,1,macBLACK); 
	//������� 
	r1=d/2+3;
	//�����һ�ε�����
	px0=sx+r+(r-d-7)*sin((pi/30)*oldsec); 
	py0=sy+r-(r-d-7)*cos((pi/30)*oldsec); 
	px1=sx+r+r1*sin((pi/30)*oldsec); 
	py1=sy+r-r1*cos((pi/30)*oldsec); 
	gui_draw_bline1(px0,py0,px1,py1,0,macBLACK); 
///////////////////////////////////////////////
	//��ʾСʱ 
	r1=d/2+4; 
	//��ʾ�µ�ʱ��
	temp=(float)min/60;
	temp+=hour;
	px0=sx+r+(r-3*d-7)*sin((pi/6)*temp); 
	py0=sy+r-(r-3*d-7)*cos((pi/6)*temp); 
	px1=sx+r+r1*sin((pi/6)*temp); 
	py1=sy+r-r1*cos((pi/6)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,2,macYELLOW); 
	//��ʾ���� 
	r1=d/2+3; 
	temp=(float)sec/60;
	temp+=min;
	//��ʾ�µķ���
	px0=sx+r+(r-2*d-7)*sin((pi/30)*temp); 
	py0=sy+r-(r-2*d-7)*cos((pi/30)*temp); 
	px1=sx+r+r1*sin((pi/30)*temp); 
	py1=sy+r-r1*cos((pi/30)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,1,macGREEN); 	
	//��ʾ����  
	r1=d/2+3;
	//��ʾ�µ�����
	px0=sx+r+(r-d-7)*sin((pi/30)*sec); 
	py0=sy+r-(r-d-7)*cos((pi/30)*sec); 
	px1=sx+r+r1*sin((pi/30)*sec); 
	py1=sy+r-r1*cos((pi/30)*sec); 
	gui_draw_bline1(px0,py0,px1,py1,0,macRED); 
	oldhour=hour;	//����ʱ
	oldmin=min;		//�����
	oldsec=sec;		//������
}	















