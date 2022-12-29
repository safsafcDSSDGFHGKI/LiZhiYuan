#include "stm32f10x.h" 
#include "bsp_ili9341_lcd.h"
#include "clock.h"
#include "math.h"
#define pi 3.1415926
/*******************************************************************************/
//画一条粗线
//x0,y0:起点 x1,y1:终点
//size:线粗细,仅支持:0~2.
//color:颜色
void gui_draw_bline1(u16 x0,u16 y0,u16 x1,u16 y1,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x1-x0; //计算坐标增量 
	delta_y=y1-y0; 
	uRow=x0; 
	uCol=y0; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		if(size==0)ILI9341_SetPointPixel(uRow,uCol,color);//画点 
		if(size==1)
		{
			ILI9341_SetPointPixel(uRow,uCol,color);//画点 
			ILI9341_SetPointPixel(uRow+1,uCol,color);//画点 
			ILI9341_SetPointPixel(uRow,uCol+1,color);//画点 
			ILI9341_SetPointPixel(uRow+1,uCol+1,color);//画点 
		}
		if(size==2)
		{
			ILI9341_SetPointPixel(uRow,uCol,color);//画点 
			ILI9341_SetPointPixel(uRow+1,uCol,color);//画点 
			ILI9341_SetPointPixel(uRow,uCol+1,color);//画点 
			ILI9341_SetPointPixel(uRow+1,uCol+1,color);//画点 
			ILI9341_SetPointPixel(uRow-1,uCol+1,color);//画点 
			ILI9341_SetPointPixel(uRow+1,uCol-1,color);//画点
			ILI9341_SetPointPixel(uRow-1,uCol-1,color);//画点  
			ILI9341_SetPointPixel(uRow-1,uCol,color);//画点 
			ILI9341_SetPointPixel(uRow,uCol-1,color);//画点  
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

//画圆形指针表盘
//x,y:坐标中心点
//size:表盘大小(直径)
//d:表盘分割,秒钟的高度
void calendar_circle_clock_drawpanel(u16 x,u16 y,u16 size,u16 d)
{
	u16 r=size/2;//得到半径 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1; 
	u16 i; 
	ILI9341_DrawCircle(x,y,r,macWHITE,0);		//画外圈
	ILI9341_DrawCircle(x,y,r-4,macWHITE,0);		//画内圈
	for(i=0;i<60;i++)//画秒钟格
	{ 
		px0=sx+r+(r-4)*sin((pi/30)*i); 
		py0=sy+r-(r-4)*cos((pi/30)*i); 
		px1=sx+r+(r-d)*sin((pi/30)*i); 
		py1=sy+r-(r-d)*cos((pi/30)*i);  
		gui_draw_bline1(px0,py0,px1,py1,0,macWHITE);		
	}
	for(i=0;i<12;i++)//画小时格
	{ 
		px0=sx+r+(r-5)*sin((pi/6)*i); 
		py0=sy+r-(r-5)*cos((pi/6)*i); 
		px1=sx+r+(r-d)*sin((pi/6)*i); 
		py1=sy+r-(r-d)*cos((pi/6)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,macYELLOW);		
	}
	for(i=0;i<4;i++)//画3小时格
	{ 
		px0=sx+r+(r-5)*sin((pi/2)*i); 
		py0=sy+r-(r-5)*cos((pi/2)*i); 
		px1=sx+r+(r-d-3)*sin((pi/2)*i); 
		py1=sy+r-(r-d-3)*cos((pi/2)*i);  
		gui_draw_bline1(px0,py0,px1,py1,2,macYELLOW);		
	}
	ILI9341_DrawCircle(x,y,d/2,macWHITE,1);		//画中心圈
   
}
/*******************************************************************************************
函数功能：显示时间
形参:x  y 坐标中心点 size表盘大小直径  d 表盘分割 秒钟的高度 hour时钟 min 分钟sec秒钟
返回值:无
*******************************************************************************************/
void calendar_circle_clock_showtime(u16 x,u16 y,u16 size,u16 d,u8 hour,u8 min,u8 sec)
{
	static u8 oldhour=0;	//最近一次进入该函数的时分秒信息
	static u8 oldmin=0;
	static u8 oldsec=0;
	float temp;
	u16 r=size/2;//得到半径 
	u16 sx=x-r;
	u16 sy=y-r;
	u16 px0,px1;
	u16 py0,py1;  
	u8 r1; 
	if(hour>11)hour-=12;
///////////////////////////////////////////////
	//清除小时
	r1=d/2+4;
	//清除上一次的数据
	temp=(float)oldmin/60;
	temp+=oldhour;
	px0=sx+r+(r-3*d-7)*sin((pi/6)*temp); 
	py0=sy+r-(r-3*d-7)*cos((pi/6)*temp); 
	px1=sx+r+r1*sin((pi/6)*temp); 
	py1=sy+r-r1*cos((pi/6)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,2,macBLACK);
	//清除分钟
	r1=d/2+3;
	temp=(float)oldsec/60;
	temp+=oldmin;
	//清除上一次的数据
	px0=sx+r+(r-2*d-7)*sin((pi/30)*temp); 
	py0=sy+r-(r-2*d-7)*cos((pi/30)*temp); 
	px1=sx+r+r1*sin((pi/30)*temp); 
	py1=sy+r-r1*cos((pi/30)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,1,macBLACK); 
	//清除秒钟 
	r1=d/2+3;
	//清除上一次的数据
	px0=sx+r+(r-d-7)*sin((pi/30)*oldsec); 
	py0=sy+r-(r-d-7)*cos((pi/30)*oldsec); 
	px1=sx+r+r1*sin((pi/30)*oldsec); 
	py1=sy+r-r1*cos((pi/30)*oldsec); 
	gui_draw_bline1(px0,py0,px1,py1,0,macBLACK); 
///////////////////////////////////////////////
	//显示小时 
	r1=d/2+4; 
	//显示新的时钟
	temp=(float)min/60;
	temp+=hour;
	px0=sx+r+(r-3*d-7)*sin((pi/6)*temp); 
	py0=sy+r-(r-3*d-7)*cos((pi/6)*temp); 
	px1=sx+r+r1*sin((pi/6)*temp); 
	py1=sy+r-r1*cos((pi/6)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,2,macYELLOW); 
	//显示分钟 
	r1=d/2+3; 
	temp=(float)sec/60;
	temp+=min;
	//显示新的分钟
	px0=sx+r+(r-2*d-7)*sin((pi/30)*temp); 
	py0=sy+r-(r-2*d-7)*cos((pi/30)*temp); 
	px1=sx+r+r1*sin((pi/30)*temp); 
	py1=sy+r-r1*cos((pi/30)*temp); 
	gui_draw_bline1(px0,py0,px1,py1,1,macGREEN); 	
	//显示秒钟  
	r1=d/2+3;
	//显示新的秒钟
	px0=sx+r+(r-d-7)*sin((pi/30)*sec); 
	py0=sy+r-(r-d-7)*cos((pi/30)*sec); 
	px1=sx+r+r1*sin((pi/30)*sec); 
	py1=sy+r-r1*cos((pi/30)*sec); 
	gui_draw_bline1(px0,py0,px1,py1,0,macRED); 
	oldhour=hour;	//保存时
	oldmin=min;		//保存分
	oldsec=sec;		//保存秒
}	















