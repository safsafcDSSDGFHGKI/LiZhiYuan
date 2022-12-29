#include "lcd12864.h"
#include "delay.h"
#include "string.h"
#include "usart.h"
#include<stdio.h>
#include "StrChinese.h"
#include "asciicode.h"
/*-----------------------------------------------------------------------
LCD12864_GPIO_Congigure  				: LCD12864的GPIO初始化
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
static void LCD12864_GPIO_Congigure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                                                   // 声明结构体
	RCC_APB2PeriphClockCmd(LCD12864_Clock, ENABLE);                                        // 开启GPIOB时钟
																															
  GPIO_InitStructure.GPIO_Pin = LCD12864_CS|LCD12864_CLK|LCD12864_SID;                                // 设置引脚号
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                       // 设置GPIO的模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // 设置IO口的速度
  GPIO_Init(LCD12864_Port, &GPIO_InitStructure);                                         // 初始化结构体
}

/*-----------------------------------------------------------------------
LCD12864_WriteData      				: LCD12864写数据
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_WriteData(uint8_t Data)
{
	uint8_t i;
	uint16_t Data_H_L;
	
	LCD12864_SID_OUT();                                                                    // 数据线配置为输出模式
	Data_H_L = ((Data & 0xf0)<<8)|((Data & 0x0f)<<4);                                      // 转换为16位数据传输
	LCD12864_CS_L;                                                                         // 片选拉低
	LCD12864_CLK_L;                                                                        // 时钟信号线拉低
	LCD12864_CS_H;                                                                         // 片选拉高

	for(i=0;i<8;i++)
	{
		if(((0xfa<<i)&0x80)!=0)                                                              // 先写入写数据指令
		{
			LCD12864_SID_H;
		}
		else 
		{
			LCD12864_SID_L;
		}
		LCD12864_CLK_H;
		Delay_us(1);
		LCD12864_CLK_L;
	}
	
	for(i=0;i<16;i++)                                                                      // 写入数据
	{
		if(((Data_H_L<<i)&0x8000)!=0) 
		{
			LCD12864_SID_H;
		}
		else 
		{
			LCD12864_SID_L;
		}
		LCD12864_CLK_H;
		Delay_us(1);
		LCD12864_CLK_L;
	}
	LCD12864_CS_L;                                                                         // 片选拉低
}

/*-----------------------------------------------------------------------
LCD12864_WriteCmd      				: LCD12864写数据
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_WriteCmd(uint8_t Cmd)
{
	uint8_t i;
	uint16_t Cmd_H_L;
	
	LCD12864_SID_OUT();                                                                    // 数据线配置为输出模式
	Cmd_H_L = ((Cmd & 0xf0)<<8)|((Cmd & 0x0f)<<4);                                         // 转换为16位数据传输
	LCD12864_CS_L;                                                                         // 片选拉低
	LCD12864_CLK_L;                                                                        // 时钟信号线拉低
	LCD12864_CS_H;                                                                         // 片选拉高

	
	for(i=0;i<8;i++)
	{
		if(((0xf8<<i)&0x80)!=0) 
		{
			LCD12864_SID_H;
		}
		else 
		{
			LCD12864_SID_L;
		}
		LCD12864_CLK_H;
		Delay_us(1);
		LCD12864_CLK_L;
	}
	
	for(i=0;i<16;i++)
	{
		if(((Cmd_H_L<<i)&0x8000)!=0) 
		{
			LCD12864_SID_H;
		}
		else 
		{
			LCD12864_SID_L;
		}
		LCD12864_CLK_H;
		Delay_us(1);
		LCD12864_CLK_L;
	}
	LCD12864_CS_L;                                                                         // 片选拉低
}
/*-----------------------------------------------------------------------
LCD12864_ReadData   	    			: LCD12864读数据
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
uint8_t LCD12864_ReadData()
{
	return 0;
}
/*-----------------------------------------------------------------------
LCD12864_Init    	    			    : LCD12864初始化
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_Init(void)
{
		LCD12864_GPIO_Congigure();
	  LCD12864_WriteCmd(0x30);                                                             // 选择基本指令集，和，8位数据模式。
    Delay_ms(5);
    LCD12864_WriteCmd(0x0c);                                                             //开显示,无游标,不反白.
    Delay_ms(5); 
    LCD12864_WriteCmd(0x01);                                                             //清除显示，并将 DDRAM 的地址计数器 AC 设为 00H.
    Delay_ms(5);
    LCD12864_WriteCmd(0x06);                                                             //设置，外部读写数据后,地址记数器 AC 会自动加 1。
    Delay_ms(5);
    LCD12864_WriteCmd(0x80);                                                             //将 DDRAM 地址计数器 AC 设为 0.
    Delay_ms(5);	
}

/*-----------------------------------------------------------------------
LCD12864_SetLocal    	    	    : LCD12864设置坐标
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_SetLocal(uint8_t X,uint8_t Y)
{
	switch(X)
	{
		case 0: LCD12864_WriteCmd(0x80+Y); break;
		case 1: LCD12864_WriteCmd(0x90+Y); break;
		case 2: LCD12864_WriteCmd(0x88+Y); break;
		case 3: LCD12864_WriteCmd(0x98+Y); break;
	}
}
/*-----------------------------------------------------------------------
LCD12864_DisplayStrChinSingle   : LCD12864显示单个字符串和汉字
	
输入参数                   			：uint8_t X ：X轴坐标,uint8_t Y ：Y轴坐标,char Str ：字符 
                                  

-----------------------------------------------------------------------*/
void LCD12864_DisplayStrChinSingle(uint8_t X,uint8_t Y,char *Str)
{
	LCD12864_SetLocal(X,Y);                                                                // 设置坐标

	LCD12864_WriteData(*Str);
	LCD12864_WriteData(*(Str+1));

}
/*-----------------------------------------------------------------------
LCD12864_DisplayStrChin    	    : LCD12864显示字符串和汉字
	
输入参数                   			：uint8_t X ：X轴坐标,uint8_t Y ：Y轴坐标,char *Str ：字符串
                                  

-----------------------------------------------------------------------*/
void LCD12864_DisplayStrChin(uint8_t X,uint8_t Y,char *Str)
{
	LCD12864_SetLocal(X,Y);                                                                // 设置坐标
	while(*Str != '\0')
	{
		LCD12864_WriteData(*Str);
		Str ++;
	}
}

/*-----------------------------------------------------------------------
LCD12864_DisplayFlaotInt        : LCD12864显示整数和浮点数
	
输入参数                   			：uint8_t X ：X轴坐标,uint8_t Y ：Y轴坐标,double Num ：数
                                  

-----------------------------------------------------------------------*/
void LCD12864_DisplayFlaotInt(uint8_t X,uint8_t Y,double Num)
{
	uint8_t StrLen;
	char FloatChar[16];
	char FloatChar1[16]={0};                                                               // 必须进行赋值
	
	if(Num == (long long int)Num)                                                          // 判断是整数还是小数，如果是整数
	{
		if(Num<10)sprintf(FloatChar,":0%lld",(long long int)Num);                            // 前面加：和0是为了写入秒时和前面的分隔开距离
		else sprintf(FloatChar,":%lld",(long long int)Num);
		LCD12864_DisplayStrChin(X,Y,FloatChar);
	}
	else                                                                                   // 如果是小数
	{
		sprintf(FloatChar,"%f",Num);	                                                       // 把数字转化成字符串         
		StrLen = strlen(FloatChar);                                                          // 判断字符串的长度，目的是为了去掉浮点数小数点后面自动加0
		while(*(FloatChar+StrLen-1) == '0')                                                  // 判断最后有几个零
		{
			StrLen = StrLen - 1;
		}
		strncpy(FloatChar1, FloatChar, StrLen);                                              // 把 FloatChar 的前 StrLen 个字符串复制到 FloatChar1 中
		LCD12864_DisplayStrChin(X,Y,FloatChar1);                                             // 把字符串显示出来
	}	
}
void LCD12864_DisplayFlaotIntDate(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,"/0%lld/",(long long int)Num);                            // 前面加：和0是为了写入秒时和前面的分隔开距离
	else sprintf(FloatChar,"/%lld/",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

void LCD12864_DisplayFlaotIntDateYear(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,"0%lld",(long long int)Num);                            // 前面加：和0是为了写入秒时和前面的分隔开距离
	else sprintf(FloatChar,"%lld",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}
void LCD12864_DisplayFlaotIntDateTemp(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,".%lldC",(long long int)Num);                            // 前面加：和0是为了写入秒时和前面的分隔开距离
	else sprintf(FloatChar,".%lldC",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}
void LCD12864_DisplayFlaotIntDateH(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,".%lld%%",(long long int)Num);                            // 前面加：和0是为了写入秒时和前面的分隔开距离
	else sprintf(FloatChar,"%lld%%",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}
/*---------------------------------------------------------------------
LCD12864_Clear      	    	    : LCD12864清屏
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_Clear(void)
{
	LCD12864_WriteCmd(0x01);                                                               // 写入清屏指令
	Delay_ms(6);	 
}

/*-----------------------------------------------------------------------
LCD12864_DrawClear      		    : LCD12864清屏，和上一个清屏不一样，这个是通过给每个点写0进行清屏
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawClear(void)
{	
	uint8_t  i,j;
	LCD12864_WriteCmd(0x34);
  Delay_ms(2);	
	for(i=0;i<32;i++)			                                                                 // 因为LCD有纵坐标32格所以写三十二次
	{
		LCD12864_WriteCmd(0x80+i);		                                                       // 先写入纵坐标Y的值
		LCD12864_WriteCmd(0x80);		                                                         // 再写入横坐标X的值
		for(j=0;j<32;j++)		                                                                 // 横坐标有16位，每位写入两个字节的的数据，也就写入32次
		{						                                                                         // 因为当写入两个字节之后横坐标会自动加1，所以就不用再次写入地址了。
			LCD12864_WriteData(0x00);	  
		}
	}
	LCD12864_WriteCmd(0x36);                                                               // 开显示
  Delay_ms(2);	
	LCD12864_WriteCmd(0x30);                                                               // 转回基本指令集
  Delay_ms(5);	
}
/*-----------------------------------------------------------------------
LCD12864_DrawPoint      		    : LCD12864画点
	
输入参数                   			：uint8_t x,uint8_t y   x,y轴坐标
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawPoint(uint8_t x,uint8_t y)
{
	uint16_t bt=0,read=0;
	uint8_t x_adr,y_adr,h_bit,l_bit;
	y_adr=0x80+y%32;			                                                                 // 计算Y轴的地址，应为纵坐标有64个，所有对32求余，当Y大于31时，Y的坐标是下半屏的。
	if(y>31)                                                                               // 计算X轴的地址当Y大于31时X的地址在下半屏，从0X88开始，小于31时X的地址是在上半屏，从0X80开始
		x_adr=0x88+x/16;		
	else
		x_adr=0x80+x/16;
	bt=0x8000>>(x%16);                                                                     // 求这个点到底是在哪个点
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(y_adr);	                                                             // 读取数据的时候要先写入所取数据的地址
	LCD12864_WriteCmd(x_adr);
	LCD12864_ReadData();		                                                               // 读取的第一个字节不要，
	read=LCD12864_ReadData();	                                                             // 从第二个字节开始接收。
	read<<=8;
	read|=LCD12864_ReadData();
	bt=bt|read;
	h_bit=bt>>8;
	l_bit=bt;
	LCD12864_WriteCmd(y_adr);	                                                             // 写入点的时候，重新写入地址，因为地址已经改变。
	LCD12864_WriteCmd(x_adr);
	LCD12864_WriteData(h_bit);
	LCD12864_WriteData(l_bit);
	LCD12864_WriteCmd(0x36);                                                               // 开显示
	LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集	
}	

/*-----------------------------------------------------------------------
LCD12864_DrowPic        		    : LCD12864画图
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrowPic(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *img)
{
    uint16_t i;
    uint8_t xi,yi;
    uint8_t xt,yt;
 
    x >>= 4;
    w >>= 3;
    i = 0;
    LCD12864_WriteCmd(0x36); 
	
    for (yi=0; yi<h; yi++)
    {
        yt = y+yi;
        xt = x;
        if (yt >= 32)
        {
            yt -= 32;
            xt += 8;
        }
        LCD12864_WriteCmd(0x80|yt);
        LCD12864_WriteCmd(0x80|xt);
        for (xi=0; xi<w; xi++)
        {
          LCD12864_WriteData(img[i++]);
        }
    }
}

/*-----------------------------------------------------------------------
LCD12864_DrowChines      		    : LCD12864通过取模的方式写汉字
	
输入参数                   			：uint8_t x ：横坐标（0-7）, uint8_t y ：纵坐标（0-63）,uint8_t Num 写的汉字的个数, uint8_t Local ：（汉字字模在数组中的位置）
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrowChines(uint8_t x, uint8_t y,uint8_t Num, uint8_t Local)
{
	uint8_t X_Adr,Y_Adr;
	uint8_t i,j;
	
	Y_Adr=0x80+y%32;			                                                                 // 计算Y轴的地址，应为纵坐标有64个，所有对32求余，当Y大于31时，Y的坐标是下半屏的。
	if(y>31)                                                                               // 计算X轴的地址当Y大于31时X的地址在下半屏，从0X88开始，小于31时X的地址是在上半屏，从0X80开始
		X_Adr=0x88+x/16;		
	else
		X_Adr=0x80+x/16;
	LCD12864_WriteCmd(0x34);
	Delay_ms(5);
	for(j=0;j<Num;j++)
	{		
		LCD12864_WriteCmd(Y_Adr);	                                                           // 写入点的时候，重新写入地址，因为地址已经改变。
		LCD12864_WriteCmd(X_Adr+j);
		for(i=0;i<16;i++)
		{
			LCD12864_WriteCmd(Y_Adr+i);	                                                       // 写入点的时候，重新写入地址，因为地址已经改变。
			LCD12864_WriteCmd(X_Adr+j);
			LCD12864_WriteData(Chinese[Local][2*i]);
			LCD12864_WriteData(Chinese[Local][2*i+1]);
		}
		Local++;
	}
	LCD12864_WriteCmd(0x36);                                                               // 开显示
	Delay_ms(2);	
	LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集		
	Delay_ms(2);	
}

/*-----------------------------------------------------------------------
LCD12864_DrowChines      		    : LCD12864通过取模的方式写汉字
	
输入参数                   			：uint8_t x ：横坐标（0-7）, uint8_t y ：纵坐标（0-63）,uint8_t Num 写的汉字的个数, uint8_t Local ：（汉字字模在数组中的位置）
																																								Val : 0正常显示 1取反

-----------------------------------------------------------------------*/
void LCD12864_DrowChines_N(uint8_t x, uint8_t y,uint8_t Num, uint8_t Local,uint8_t Val)
{
	uint8_t X_Adr,Y_Adr;
	uint8_t i,j;
	
	Y_Adr=0x80+y%32;			                                                                 // 计算Y轴的地址，应为纵坐标有64个，所有对32求余，当Y大于31时，Y的坐标是下半屏的。
	if(y>31)                                                                               // 计算X轴的地址当Y大于31时X的地址在下半屏，从0X88开始，小于31时X的地址是在上半屏，从0X80开始
		X_Adr=0x88+x/16;		
	else
		X_Adr=0x80+x/16;
	LCD12864_WriteCmd(0x34);
	Delay_ms(5);
	for(j=0;j<Num;j++)
	{		
		LCD12864_WriteCmd(Y_Adr);	                                                           // 写入点的时候，重新写入地址，因为地址已经改变。
		LCD12864_WriteCmd(X_Adr+j);
		for(i=0;i<16;i++)
		{
			LCD12864_WriteCmd(Y_Adr+i);	                                                       // 写入点的时候，重新写入地址，因为地址已经改变。
			LCD12864_WriteCmd(X_Adr+j);
			if(Val==0)
			{
				LCD12864_WriteData(Chinese[Local][2*i]);
				LCD12864_WriteData(Chinese[Local][2*i+1]);
			}
			else
			{
				LCD12864_WriteData(~Chinese[Local][2*i]);
				LCD12864_WriteData(~Chinese[Local][2*i+1]);
			}
		}
		Local++;
	}
	LCD12864_WriteCmd(0x36);                                                               // 开显示
//	Delay_ms(2);	
	LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集		
//	Delay_ms(2);	
}

/*-----------------------------------------------------------------------
LCD12864_DrowChineseRandom      : LCD12864任意点写16x16汉字
	
输入参数                   			：x : X轴坐标（0-127） y ：Y轴坐标（0-63） Num ：显示字数  Local ：在数组中的位置
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrowChineseRandom(uint8_t x, uint8_t y,uint8_t Num,uint8_t Local)
{
	uint8_t i,j,k;
	uint8_t Resualt,Font;
	uint8_t X_Addr,Y_Addr,Y_Ad=0;
	Y_Addr = y;
	for(k=0;k<Num;k++)
	{
		for(j=0;j<32;j++)
		{
			Font = Chinese[Local][j];
			for(i=0;i<8;i++)
			{
				if(j%2==0)
				{
					X_Addr = x;
				}
				else
				{
					X_Addr = x + 8;
				}
				Resualt = Font&0x80;
				if(Resualt!=0)
				{
					LCD12864_DrawPoint(X_Addr+i,Y_Addr);
				}
				Font <<=1;
			}
			Y_Ad ++;
			if(Y_Ad==2)
			{
				Y_Addr = Y_Addr + 1;
				Y_Ad = 0;
			}	
		}
		Local ++;
		Y_Addr = y;
		x = x + 16;
	}
}

/*-----------------------------------------------------------------------
LCD12864_DrowChineseRandom      : LCD12864任意大小的汉字字符，宽度必须是8的倍数
	
输入参数                   			：x : X轴坐标（0-127） y ：Y轴坐标（0-63） Num ：显示字数  Local ：在数组中的位置  Higth ：高度   Wide ：宽度  Mode : 0反显 ，1正常显示
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrowChineseRandomSize(uint8_t x, uint8_t y,uint8_t Num,uint8_t Local,uint8_t Higth,uint8_t Wide,uint8_t Mode)
{
	uint16_t i,j,k;
	uint8_t Resualt,Font;
	uint8_t X_Addr,Y_Addr,Y_Ad=0;
	Y_Addr = y;
	Mode<<=7;
	for(k=0;k<Num;k++)
	{
		for(j=0;j<(Wide/8)*Higth;j++)
		{
			Font = Chinese[Local][j];
			for(i=0;i<8;i++)
			{
				if(j%(Wide/8)!=0)
				{
					X_Addr = x + j%(Wide/8)*8;
				}
				else
				{
					X_Addr = x ;
				}

				Resualt = Font&0x80;				
				if(Resualt==Mode)
				{
					LCD12864_DrawPoint(X_Addr+i,Y_Addr);
				}
				Font <<=1;
			}
			Y_Ad ++;
			if(Y_Ad==(Wide/8))
			{
				Y_Addr = Y_Addr + 1;
				Y_Ad = 0;
			}	
		}
		Local ++;
		Y_Addr = y;
		x = x + Wide;
	}
}

/*-----------------------------------------------------------------------
LCD12864_DispChar6x8            : LCD12864任意点写6x8ASCII码一个字符
	
输入参数                   			：x : X轴坐标（0-127） y ：Y轴坐标（0-63） Str ：字符  Mode ：显示模式 1，正常显示  0，反白
                                  

-----------------------------------------------------------------------*/
void LCD12864_DispChar6x8(uint8_t x, uint8_t y,char Str,uint8_t Mode)
{
	uint16_t i,j;
	uint8_t Resualt,Font6x8;
	uint8_t X_Addr,Y_Addr;
	char St;
	Y_Addr = y;
	X_Addr = x;
	Mode<<=7;
	St = Str - 32;
	for(j=0;j<6;j++)
	{			
		Font6x8 = font6x8[St][j];
		for(i=0;i<8;i++)
		{
			Resualt = Font6x8&0x80; 
			if(Resualt==Mode)
			{
				LCD12864_DrawPoint(X_Addr,Y_Addr+8-i);
			}
			Font6x8 <<=1;
		}
		X_Addr++;
		Y_Addr = y;
	}
}
/*-----------------------------------------------------------------------
LCD12864_DispString6x8          : LCD12864任意点写6x8ASCII码字符串
	
输入参数                   			：x : X轴坐标（0-127） y ：Y轴坐标（0-63） Str ：字符  Mode ：显示模式 1，正常显示  0，反白
                                  

-----------------------------------------------------------------------*/
void LCD12864_DispString6x8(uint8_t x, uint8_t y,char *Str,uint8_t Mode)
{
	uint8_t Y_Addr;
	Y_Addr = y;
	while(*Str != '\0')
	{
		LCD12864_DispChar6x8(x, Y_Addr,*Str,Mode);
		Y_Addr = y;
		x = x + 6;
		Str ++;
	}
}

/*-----------------------------------------------------------------------
LCD12864_DisplayFlaotInt        : LCD12864显示整数和浮点数
	
输入参数                   			：uint8_t X ：X轴坐标,uint8_t Y ：Y轴坐标,double Num ：数
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawFlaotInt(uint8_t X,uint8_t Y,double Num)
{
	uint8_t StrLen;
	char FloatChar[16];
	char FloatChar1[16]={0};                                                               // 必须进行赋值
	
	if(Num == (long long int)Num)                                                          // 判断是整数还是小数，如果是整数
	{
		sprintf(FloatChar,"%lld",(long long int)Num);
		LCD12864_DispString6x8(X,Y,FloatChar,1);
	}
	else                                                                                   // 如果是小数
	{
		sprintf(FloatChar,"%f",Num);	                                                       // 把数字转化成字符串         
		StrLen = strlen(FloatChar);                                                          // 判断字符串的长度，目的是为了去掉浮点数小数点后面自动加0
		while(*(FloatChar+StrLen-1) == '0')                                                  // 判断最后有几个零
		{
			StrLen = StrLen - 1;
		}
		strncpy(FloatChar1, FloatChar, StrLen);                                              // 把 FloatChar 的前 StrLen 个字符串复制到 FloatChar1 中
		LCD12864_DispString6x8(X,Y,FloatChar1,1);                                            // 把字符串显示出来
	}	
}

/*-----------------------------------------------------------------------
LCD12864_DrawCircle             : LCD12864画圆
	
输入参数                   			：(x,y) : 圆点坐标
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawCircle(int x,int y,int r)
{
	int xc=0;
	int yc,p;
	yc=r;
	p=3-(r<<1);	
	while(xc <= yc)
	{
		LCD12864_DrawPoint(x+xc,y+yc);
		LCD12864_DrawPoint(x+xc,y-yc);	
		LCD12864_DrawPoint(x-xc,y+yc);
		LCD12864_DrawPoint(x-xc,y-yc);
		
		LCD12864_DrawPoint(x+yc,y+xc);	
		LCD12864_DrawPoint(x+yc,y-xc);
		LCD12864_DrawPoint(x-yc,y+xc);
		LCD12864_DrawPoint(x-yc,y-xc);
		if(p<0)
		{
			p += (xc++ << 2) + 6;	
		}
		else
			p += ((xc++ - yc--)<<2) + 10;
	}
}

/*-----------------------------------------------------------------------
LCD12864_DrawLine							  : LCD12864画线函数

输入参数uint16_t x1, uint16_t y1	：起始坐标点
				uint16_t x2, uint16_t y2：终止坐标点           


-----------------------------------------------------------------------*/
void LCD12864_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1;                                                                         // 计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1;                                                                   // 设置单步方向 
	else if(delta_x==0)incx=0;                                                             // 垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;                                                             // 水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;                                                  // 选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )                                                            // 画线输出 
	{  
		LCD12864_DrawPoint(uRow,uCol);                                                       // 画点 
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

void LCD12864_CleanPoint(uint8_t x,uint8_t y)
{
	uint16_t bt=0,read=0;
	uint8_t x_adr,y_adr,h_bit,l_bit;
	y_adr=0x80+y%32;			                                                                 // 计算Y轴的地址，应为纵坐标有64个，所有对32求余，当Y大于31时，Y的坐标是下半屏的。
	if(y>31)                                                                               // 计算X轴的地址当Y大于31时X的地址在下半屏，从0X88开始，小于31时X的地址是在上半屏，从0X80开始
		x_adr=0x88+x/16;		
	else
		x_adr=0x80+x/16;
	bt=0x8000>>(x%16);                                                                     // 求这个点到底是在哪个点
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(y_adr);	                                                             // 读取数据的时候要先写入所取数据的地址
	LCD12864_WriteCmd(x_adr);
	LCD12864_ReadData();		                                                               // 读取的第一个字节不要，
	read=LCD12864_ReadData();	                                                             // 从第二个字节开始接收。
	read<<=8;
	read|=LCD12864_ReadData();
	bt=bt|read;
	h_bit=bt>>8;
	l_bit=bt;
	LCD12864_WriteCmd(y_adr);	                                                             // 写入点的时候，重新写入地址，因为地址已经改变。
	LCD12864_WriteCmd(x_adr);
	LCD12864_WriteData(h_bit&0xff<<(x/16));
	LCD12864_WriteData(l_bit&0xff<<(x/16));
	LCD12864_WriteCmd(0x36);                                                               // 开显示
	LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集	
}

void LCD12864_CleanLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1;                                                                         // 计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1;                                                                   // 设置单步方向 
	else if(delta_x==0)incx=0;                                                             // 垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;                                                             // 水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;                                                  // 选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )                                                            // 画线输出 
	{  
		LCD12864_CleanPoint(uRow,uCol);                                                       // 画点 
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


void LCD12864_DrowPicNum(uint8_t x, uint8_t y, uint8_t Num)
{
	uint16_t i;
	uint8_t xi,yi;
	uint8_t xt,yt;

	x >>= 4;
	i = 0;
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x36); 

	for (yi=0; yi<32; yi++)
	{
			yt = y+yi;
			xt = x;
			if (yt >= 32)
			{
					yt -= 32;
					xt += 8;
			}
			LCD12864_WriteCmd(0x80|yt);
			LCD12864_WriteCmd(0x80|xt);
			for (xi=0; xi<(16>>3); xi++)
			{
				LCD12864_WriteData(Num32x16[Num][i++]);
			}
	}
	LCD12864_WriteCmd(0x36);                                                               // 开显示
	LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集
}
/*
	带反显
*/
void LCD12864_DrowPicNumX(uint8_t x, uint8_t y, uint8_t Num,uint8_t Val)
{
	uint16_t i;
	uint8_t xi,yi;
	uint8_t xt,yt;

	x >>= 4;
	i = 0;
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x36); 

	for (yi=0; yi<32; yi++)
	{
			yt = y+yi;
			xt = x;
			if (yt >= 32)
			{
					yt -= 32;
					xt += 8;
			}
			LCD12864_WriteCmd(0x80|yt);
			LCD12864_WriteCmd(0x80|xt);
			for (xi=0; xi<(16>>3); xi++)
			{
				if(Val == 0)
					LCD12864_WriteData(Num32x16[Num][i++]);
				else
					LCD12864_WriteData(~Num32x16[Num][i++]);
			}
	}
	LCD12864_WriteCmd(0x36);                                                               // 开显示
	LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集
}
void LCD12864_DrowWeek(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t Num)
{
    uint16_t i;
    uint8_t xi,yi;
    uint8_t xt,yt;
 
    x >>= 4;
    w >>= 3;
    i = 0;
    LCD12864_WriteCmd(0x36); 
	
    for (yi=0; yi<h; yi++)
    {
        yt = y+yi;
        xt = x;
        if (yt >= 32)
        {
            yt -= 32;
            xt += 8;
        }
        LCD12864_WriteCmd(0x80|yt);
        LCD12864_WriteCmd(0x80|xt);
        for (xi=0; xi<w; xi++)
        {
          LCD12864_WriteData(Num16x32[Num][i++]);
        }
    }
		LCD12864_WriteCmd(0x36);                                                               // 开显示
		LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集
}

/*
Val = 0正常显示  Val = 1 反显
*/
void LCD12864_DrowSet(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t Num,uint8_t Val)
{
    uint16_t i;
    uint8_t xi,yi;
    uint8_t xt,yt;
 
    x >>= 4;
    w >>= 3;
    i = 0;
    LCD12864_WriteCmd(0x36); 
	
    for (yi=0; yi<h; yi++)
    {
        yt = y+yi;
        xt = x;
        if (yt >= 32)
        {
            yt -= 32;
            xt += 8;
        }
        LCD12864_WriteCmd(0x80|yt);
        LCD12864_WriteCmd(0x80|xt);
        for (xi=0; xi<w; xi++)
        {
					if(Val == 0)
						LCD12864_WriteData(Num16x32[Num][i++]);
					else
						LCD12864_WriteData(~Num16x32[Num][i++]);
        }
    }
		LCD12864_WriteCmd(0x36);                                                               // 开显示
		LCD12864_WriteCmd(0x30);	                                                             // 转回基本指令集
}
/*-----------------------------------------------------------------------
LCD12864_Disp_Temp    				  ： LCD12864显示温度

输入参数                      		： Num:温度   T_Val：温度正还是负
				    


-----------------------------------------------------------------------*/

void LCD12864_Disp_Temp(uint8_t X,uint8_t Y,int Num,uint8_t T_Val)
{
	char FloatChar[16];                                                             // 必须进行赋值

	if(Num < 10)
	{
		if(T_Val == 0)
			sprintf(FloatChar," T:+0%d℃",Num);
		else if(T_Val == 1)
			sprintf(FloatChar," T:-0%d℃",Num);
	}
	else
	{
		if(T_Val == 0)
			sprintf(FloatChar," T:+%d℃",Num);
		else if(T_Val == 1)
			sprintf(FloatChar," T:-%d℃",Num);
	}
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

/*-----------------------------------------------------------------------
LCD12864_Disp_humid				      ： LCD12864显示湿度

输入参数                      		： Num:湿度   
				    


-----------------------------------------------------------------------*/
void LCD12864_Dis_humid(uint8_t X,uint8_t Y,int Num)
{
	char FloatChar[16];                                                             // 必须进行赋值

	if(Num < 10)
		sprintf(FloatChar," H:+0%d％",Num);
	else
		sprintf(FloatChar," H:+%d％",Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

/*-----------------------------------------------------------------------
LCD12864_Disp_Data				      ： LCD12864显示日期

输入参数                      		： Year年， Mouth月， Day日
				    


-----------------------------------------------------------------------*/
void LCD12864_Disp_Data(uint8_t X,uint8_t Y,uint16_t Year,uint8_t Mouth,uint8_t Day)
{
	char FloatChar[16];                                                             // 必须进行赋值

	if(Mouth < 10 && Day < 10)
		sprintf(FloatChar,"20%d-0%d-0%d",Year,Mouth,Day);
	else if(Mouth >= 10 && Day >= 10)
		sprintf(FloatChar,"20%d-%d-%d",Year,Mouth,Day);
	else if(Mouth >= 10 && Day < 10)
		sprintf(FloatChar,"20%d-%d-0%d",Year,Mouth,Day);
	else if(Mouth < 10 && Day >= 10)
		sprintf(FloatChar,"20%d-0%d-%d",Year,Mouth,Day);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

/*-----------------------------------------------------------------------
LCD12864_Disp_Data				      ： LCD12864显示时间

输入参数                      		： Num:时间
				    


-----------------------------------------------------------------------*/
void LCD12864_SetDispTime(uint8_t X,uint8_t Y,int Num)
{
	char FloatChar[16];                                                             // 必须进行赋值

	if(Num < 10)
		sprintf(FloatChar,"0%d",Num);
	else
		sprintf(FloatChar,"%d",Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}




