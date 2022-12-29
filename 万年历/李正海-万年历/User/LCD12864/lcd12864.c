#include "lcd12864.h"
#include "delay.h"
#include "string.h"
#include "usart.h"
#include<stdio.h>
#include "StrChinese.h"
#include "asciicode.h"
/*-----------------------------------------------------------------------
LCD12864_GPIO_Congigure  				: LCD12864��GPIO��ʼ��
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
static void LCD12864_GPIO_Congigure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                                                   // �����ṹ��
	RCC_APB2PeriphClockCmd(LCD12864_Clock, ENABLE);                                        // ����GPIOBʱ��
																															
  GPIO_InitStructure.GPIO_Pin = LCD12864_CS|LCD12864_CLK|LCD12864_SID;                                // �������ź�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                                       // ����GPIO��ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // ����IO�ڵ��ٶ�
  GPIO_Init(LCD12864_Port, &GPIO_InitStructure);                                         // ��ʼ���ṹ��
}

/*-----------------------------------------------------------------------
LCD12864_WriteData      				: LCD12864д����
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void LCD12864_WriteData(uint8_t Data)
{
	uint8_t i;
	uint16_t Data_H_L;
	
	LCD12864_SID_OUT();                                                                    // ����������Ϊ���ģʽ
	Data_H_L = ((Data & 0xf0)<<8)|((Data & 0x0f)<<4);                                      // ת��Ϊ16λ���ݴ���
	LCD12864_CS_L;                                                                         // Ƭѡ����
	LCD12864_CLK_L;                                                                        // ʱ���ź�������
	LCD12864_CS_H;                                                                         // Ƭѡ����

	for(i=0;i<8;i++)
	{
		if(((0xfa<<i)&0x80)!=0)                                                              // ��д��д����ָ��
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
	
	for(i=0;i<16;i++)                                                                      // д������
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
	LCD12864_CS_L;                                                                         // Ƭѡ����
}

/*-----------------------------------------------------------------------
LCD12864_WriteCmd      				: LCD12864д����
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void LCD12864_WriteCmd(uint8_t Cmd)
{
	uint8_t i;
	uint16_t Cmd_H_L;
	
	LCD12864_SID_OUT();                                                                    // ����������Ϊ���ģʽ
	Cmd_H_L = ((Cmd & 0xf0)<<8)|((Cmd & 0x0f)<<4);                                         // ת��Ϊ16λ���ݴ���
	LCD12864_CS_L;                                                                         // Ƭѡ����
	LCD12864_CLK_L;                                                                        // ʱ���ź�������
	LCD12864_CS_H;                                                                         // Ƭѡ����

	
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
	LCD12864_CS_L;                                                                         // Ƭѡ����
}
/*-----------------------------------------------------------------------
LCD12864_ReadData   	    			: LCD12864������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
uint8_t LCD12864_ReadData()
{
	return 0;
}
/*-----------------------------------------------------------------------
LCD12864_Init    	    			    : LCD12864��ʼ��
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void LCD12864_Init(void)
{
		LCD12864_GPIO_Congigure();
	  LCD12864_WriteCmd(0x30);                                                             // ѡ�����ָ����ͣ�8λ����ģʽ��
    Delay_ms(5);
    LCD12864_WriteCmd(0x0c);                                                             //����ʾ,���α�,������.
    Delay_ms(5); 
    LCD12864_WriteCmd(0x01);                                                             //�����ʾ������ DDRAM �ĵ�ַ������ AC ��Ϊ 00H.
    Delay_ms(5);
    LCD12864_WriteCmd(0x06);                                                             //���ã��ⲿ��д���ݺ�,��ַ������ AC ���Զ��� 1��
    Delay_ms(5);
    LCD12864_WriteCmd(0x80);                                                             //�� DDRAM ��ַ������ AC ��Ϊ 0.
    Delay_ms(5);	
}

/*-----------------------------------------------------------------------
LCD12864_SetLocal    	    	    : LCD12864��������
	
�������                   			����
                                  

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
LCD12864_DisplayStrChinSingle   : LCD12864��ʾ�����ַ����ͺ���
	
�������                   			��uint8_t X ��X������,uint8_t Y ��Y������,char Str ���ַ� 
                                  

-----------------------------------------------------------------------*/
void LCD12864_DisplayStrChinSingle(uint8_t X,uint8_t Y,char *Str)
{
	LCD12864_SetLocal(X,Y);                                                                // ��������

	LCD12864_WriteData(*Str);
	LCD12864_WriteData(*(Str+1));

}
/*-----------------------------------------------------------------------
LCD12864_DisplayStrChin    	    : LCD12864��ʾ�ַ����ͺ���
	
�������                   			��uint8_t X ��X������,uint8_t Y ��Y������,char *Str ���ַ���
                                  

-----------------------------------------------------------------------*/
void LCD12864_DisplayStrChin(uint8_t X,uint8_t Y,char *Str)
{
	LCD12864_SetLocal(X,Y);                                                                // ��������
	while(*Str != '\0')
	{
		LCD12864_WriteData(*Str);
		Str ++;
	}
}

/*-----------------------------------------------------------------------
LCD12864_DisplayFlaotInt        : LCD12864��ʾ�����͸�����
	
�������                   			��uint8_t X ��X������,uint8_t Y ��Y������,double Num ����
                                  

-----------------------------------------------------------------------*/
void LCD12864_DisplayFlaotInt(uint8_t X,uint8_t Y,double Num)
{
	uint8_t StrLen;
	char FloatChar[16];
	char FloatChar1[16]={0};                                                               // ������и�ֵ
	
	if(Num == (long long int)Num)                                                          // �ж�����������С�������������
	{
		if(Num<10)sprintf(FloatChar,":0%lld",(long long int)Num);                            // ǰ��ӣ���0��Ϊ��д����ʱ��ǰ��ķָ�������
		else sprintf(FloatChar,":%lld",(long long int)Num);
		LCD12864_DisplayStrChin(X,Y,FloatChar);
	}
	else                                                                                   // �����С��
	{
		sprintf(FloatChar,"%f",Num);	                                                       // ������ת�����ַ���         
		StrLen = strlen(FloatChar);                                                          // �ж��ַ����ĳ��ȣ�Ŀ����Ϊ��ȥ��������С��������Զ���0
		while(*(FloatChar+StrLen-1) == '0')                                                  // �ж�����м�����
		{
			StrLen = StrLen - 1;
		}
		strncpy(FloatChar1, FloatChar, StrLen);                                              // �� FloatChar ��ǰ StrLen ���ַ������Ƶ� FloatChar1 ��
		LCD12864_DisplayStrChin(X,Y,FloatChar1);                                             // ���ַ�����ʾ����
	}	
}
void LCD12864_DisplayFlaotIntDate(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,"/0%lld/",(long long int)Num);                            // ǰ��ӣ���0��Ϊ��д����ʱ��ǰ��ķָ�������
	else sprintf(FloatChar,"/%lld/",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

void LCD12864_DisplayFlaotIntDateYear(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,"0%lld",(long long int)Num);                            // ǰ��ӣ���0��Ϊ��д����ʱ��ǰ��ķָ�������
	else sprintf(FloatChar,"%lld",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}
void LCD12864_DisplayFlaotIntDateTemp(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,".%lldC",(long long int)Num);                            // ǰ��ӣ���0��Ϊ��д����ʱ��ǰ��ķָ�������
	else sprintf(FloatChar,".%lldC",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}
void LCD12864_DisplayFlaotIntDateH(uint8_t X,uint8_t Y,double Num)
{
	char FloatChar[16];
	
	if(Num<10)sprintf(FloatChar,".%lld%%",(long long int)Num);                            // ǰ��ӣ���0��Ϊ��д����ʱ��ǰ��ķָ�������
	else sprintf(FloatChar,"%lld%%",(long long int)Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}
/*---------------------------------------------------------------------
LCD12864_Clear      	    	    : LCD12864����
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void LCD12864_Clear(void)
{
	LCD12864_WriteCmd(0x01);                                                               // д������ָ��
	Delay_ms(6);	 
}

/*-----------------------------------------------------------------------
LCD12864_DrawClear      		    : LCD12864����������һ��������һ���������ͨ����ÿ����д0��������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawClear(void)
{	
	uint8_t  i,j;
	LCD12864_WriteCmd(0x34);
  Delay_ms(2);	
	for(i=0;i<32;i++)			                                                                 // ��ΪLCD��������32������д��ʮ����
	{
		LCD12864_WriteCmd(0x80+i);		                                                       // ��д��������Y��ֵ
		LCD12864_WriteCmd(0x80);		                                                         // ��д�������X��ֵ
		for(j=0;j<32;j++)		                                                                 // ��������16λ��ÿλд�������ֽڵĵ����ݣ�Ҳ��д��32��
		{						                                                                         // ��Ϊ��д�������ֽ�֮���������Զ���1�����ԾͲ����ٴ�д���ַ�ˡ�
			LCD12864_WriteData(0x00);	  
		}
	}
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
  Delay_ms(2);	
	LCD12864_WriteCmd(0x30);                                                               // ת�ػ���ָ�
  Delay_ms(5);	
}
/*-----------------------------------------------------------------------
LCD12864_DrawPoint      		    : LCD12864����
	
�������                   			��uint8_t x,uint8_t y   x,y������
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawPoint(uint8_t x,uint8_t y)
{
	uint16_t bt=0,read=0;
	uint8_t x_adr,y_adr,h_bit,l_bit;
	y_adr=0x80+y%32;			                                                                 // ����Y��ĵ�ַ��ӦΪ��������64�������ж�32���࣬��Y����31ʱ��Y���������°����ġ�
	if(y>31)                                                                               // ����X��ĵ�ַ��Y����31ʱX�ĵ�ַ���°�������0X88��ʼ��С��31ʱX�ĵ�ַ�����ϰ�������0X80��ʼ
		x_adr=0x88+x/16;		
	else
		x_adr=0x80+x/16;
	bt=0x8000>>(x%16);                                                                     // ������㵽�������ĸ���
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(y_adr);	                                                             // ��ȡ���ݵ�ʱ��Ҫ��д����ȡ���ݵĵ�ַ
	LCD12864_WriteCmd(x_adr);
	LCD12864_ReadData();		                                                               // ��ȡ�ĵ�һ���ֽڲ�Ҫ��
	read=LCD12864_ReadData();	                                                             // �ӵڶ����ֽڿ�ʼ���ա�
	read<<=8;
	read|=LCD12864_ReadData();
	bt=bt|read;
	h_bit=bt>>8;
	l_bit=bt;
	LCD12864_WriteCmd(y_adr);	                                                             // д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
	LCD12864_WriteCmd(x_adr);
	LCD12864_WriteData(h_bit);
	LCD12864_WriteData(l_bit);
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
	LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�	
}	

/*-----------------------------------------------------------------------
LCD12864_DrowPic        		    : LCD12864��ͼ
	
�������                   			����
                                  

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
LCD12864_DrowChines      		    : LCD12864ͨ��ȡģ�ķ�ʽд����
	
�������                   			��uint8_t x �������꣨0-7��, uint8_t y �������꣨0-63��,uint8_t Num д�ĺ��ֵĸ���, uint8_t Local ����������ģ�������е�λ�ã�
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrowChines(uint8_t x, uint8_t y,uint8_t Num, uint8_t Local)
{
	uint8_t X_Adr,Y_Adr;
	uint8_t i,j;
	
	Y_Adr=0x80+y%32;			                                                                 // ����Y��ĵ�ַ��ӦΪ��������64�������ж�32���࣬��Y����31ʱ��Y���������°����ġ�
	if(y>31)                                                                               // ����X��ĵ�ַ��Y����31ʱX�ĵ�ַ���°�������0X88��ʼ��С��31ʱX�ĵ�ַ�����ϰ�������0X80��ʼ
		X_Adr=0x88+x/16;		
	else
		X_Adr=0x80+x/16;
	LCD12864_WriteCmd(0x34);
	Delay_ms(5);
	for(j=0;j<Num;j++)
	{		
		LCD12864_WriteCmd(Y_Adr);	                                                           // д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
		LCD12864_WriteCmd(X_Adr+j);
		for(i=0;i<16;i++)
		{
			LCD12864_WriteCmd(Y_Adr+i);	                                                       // д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
			LCD12864_WriteCmd(X_Adr+j);
			LCD12864_WriteData(Chinese[Local][2*i]);
			LCD12864_WriteData(Chinese[Local][2*i+1]);
		}
		Local++;
	}
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
	Delay_ms(2);	
	LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�		
	Delay_ms(2);	
}

/*-----------------------------------------------------------------------
LCD12864_DrowChines      		    : LCD12864ͨ��ȡģ�ķ�ʽд����
	
�������                   			��uint8_t x �������꣨0-7��, uint8_t y �������꣨0-63��,uint8_t Num д�ĺ��ֵĸ���, uint8_t Local ����������ģ�������е�λ�ã�
																																								Val : 0������ʾ 1ȡ��

-----------------------------------------------------------------------*/
void LCD12864_DrowChines_N(uint8_t x, uint8_t y,uint8_t Num, uint8_t Local,uint8_t Val)
{
	uint8_t X_Adr,Y_Adr;
	uint8_t i,j;
	
	Y_Adr=0x80+y%32;			                                                                 // ����Y��ĵ�ַ��ӦΪ��������64�������ж�32���࣬��Y����31ʱ��Y���������°����ġ�
	if(y>31)                                                                               // ����X��ĵ�ַ��Y����31ʱX�ĵ�ַ���°�������0X88��ʼ��С��31ʱX�ĵ�ַ�����ϰ�������0X80��ʼ
		X_Adr=0x88+x/16;		
	else
		X_Adr=0x80+x/16;
	LCD12864_WriteCmd(0x34);
	Delay_ms(5);
	for(j=0;j<Num;j++)
	{		
		LCD12864_WriteCmd(Y_Adr);	                                                           // д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
		LCD12864_WriteCmd(X_Adr+j);
		for(i=0;i<16;i++)
		{
			LCD12864_WriteCmd(Y_Adr+i);	                                                       // д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
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
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
//	Delay_ms(2);	
	LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�		
//	Delay_ms(2);	
}

/*-----------------------------------------------------------------------
LCD12864_DrowChineseRandom      : LCD12864�����д16x16����
	
�������                   			��x : X�����꣨0-127�� y ��Y�����꣨0-63�� Num ����ʾ����  Local ���������е�λ��
                                  

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
LCD12864_DrowChineseRandom      : LCD12864�����С�ĺ����ַ�����ȱ�����8�ı���
	
�������                   			��x : X�����꣨0-127�� y ��Y�����꣨0-63�� Num ����ʾ����  Local ���������е�λ��  Higth ���߶�   Wide �����  Mode : 0���� ��1������ʾ
                                  

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
LCD12864_DispChar6x8            : LCD12864�����д6x8ASCII��һ���ַ�
	
�������                   			��x : X�����꣨0-127�� y ��Y�����꣨0-63�� Str ���ַ�  Mode ����ʾģʽ 1��������ʾ  0������
                                  

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
LCD12864_DispString6x8          : LCD12864�����д6x8ASCII���ַ���
	
�������                   			��x : X�����꣨0-127�� y ��Y�����꣨0-63�� Str ���ַ�  Mode ����ʾģʽ 1��������ʾ  0������
                                  

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
LCD12864_DisplayFlaotInt        : LCD12864��ʾ�����͸�����
	
�������                   			��uint8_t X ��X������,uint8_t Y ��Y������,double Num ����
                                  

-----------------------------------------------------------------------*/
void LCD12864_DrawFlaotInt(uint8_t X,uint8_t Y,double Num)
{
	uint8_t StrLen;
	char FloatChar[16];
	char FloatChar1[16]={0};                                                               // ������и�ֵ
	
	if(Num == (long long int)Num)                                                          // �ж�����������С�������������
	{
		sprintf(FloatChar,"%lld",(long long int)Num);
		LCD12864_DispString6x8(X,Y,FloatChar,1);
	}
	else                                                                                   // �����С��
	{
		sprintf(FloatChar,"%f",Num);	                                                       // ������ת�����ַ���         
		StrLen = strlen(FloatChar);                                                          // �ж��ַ����ĳ��ȣ�Ŀ����Ϊ��ȥ��������С��������Զ���0
		while(*(FloatChar+StrLen-1) == '0')                                                  // �ж�����м�����
		{
			StrLen = StrLen - 1;
		}
		strncpy(FloatChar1, FloatChar, StrLen);                                              // �� FloatChar ��ǰ StrLen ���ַ������Ƶ� FloatChar1 ��
		LCD12864_DispString6x8(X,Y,FloatChar1,1);                                            // ���ַ�����ʾ����
	}	
}

/*-----------------------------------------------------------------------
LCD12864_DrawCircle             : LCD12864��Բ
	
�������                   			��(x,y) : Բ������
                                  

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
LCD12864_DrawLine							  : LCD12864���ߺ���

�������uint16_t x1, uint16_t y1	����ʼ�����
				uint16_t x2, uint16_t y2����ֹ�����           


-----------------------------------------------------------------------*/
void LCD12864_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1;                                                                         // ������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1;                                                                   // ���õ������� 
	else if(delta_x==0)incx=0;                                                             // ��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;                                                             // ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;                                                  // ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )                                                            // ������� 
	{  
		LCD12864_DrawPoint(uRow,uCol);                                                       // ���� 
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
	y_adr=0x80+y%32;			                                                                 // ����Y��ĵ�ַ��ӦΪ��������64�������ж�32���࣬��Y����31ʱ��Y���������°����ġ�
	if(y>31)                                                                               // ����X��ĵ�ַ��Y����31ʱX�ĵ�ַ���°�������0X88��ʼ��С��31ʱX�ĵ�ַ�����ϰ�������0X80��ʼ
		x_adr=0x88+x/16;		
	else
		x_adr=0x80+x/16;
	bt=0x8000>>(x%16);                                                                     // ������㵽�������ĸ���
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(y_adr);	                                                             // ��ȡ���ݵ�ʱ��Ҫ��д����ȡ���ݵĵ�ַ
	LCD12864_WriteCmd(x_adr);
	LCD12864_ReadData();		                                                               // ��ȡ�ĵ�һ���ֽڲ�Ҫ��
	read=LCD12864_ReadData();	                                                             // �ӵڶ����ֽڿ�ʼ���ա�
	read<<=8;
	read|=LCD12864_ReadData();
	bt=bt|read;
	h_bit=bt>>8;
	l_bit=bt;
	LCD12864_WriteCmd(y_adr);	                                                             // д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
	LCD12864_WriteCmd(x_adr);
	LCD12864_WriteData(h_bit&0xff<<(x/16));
	LCD12864_WriteData(l_bit&0xff<<(x/16));
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
	LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�	
}

void LCD12864_CleanLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1;                                                                         // ������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1;                                                                   // ���õ������� 
	else if(delta_x==0)incx=0;                                                             // ��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;                                                             // ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x;                                                  // ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )                                                            // ������� 
	{  
		LCD12864_CleanPoint(uRow,uCol);                                                       // ���� 
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
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
	LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�
}
/*
	������
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
	LCD12864_WriteCmd(0x36);                                                               // ����ʾ
	LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�
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
		LCD12864_WriteCmd(0x36);                                                               // ����ʾ
		LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�
}

/*
Val = 0������ʾ  Val = 1 ����
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
		LCD12864_WriteCmd(0x36);                                                               // ����ʾ
		LCD12864_WriteCmd(0x30);	                                                             // ת�ػ���ָ�
}
/*-----------------------------------------------------------------------
LCD12864_Disp_Temp    				  �� LCD12864��ʾ�¶�

�������                      		�� Num:�¶�   T_Val���¶������Ǹ�
				    


-----------------------------------------------------------------------*/

void LCD12864_Disp_Temp(uint8_t X,uint8_t Y,int Num,uint8_t T_Val)
{
	char FloatChar[16];                                                             // ������и�ֵ

	if(Num < 10)
	{
		if(T_Val == 0)
			sprintf(FloatChar," T:+0%d��",Num);
		else if(T_Val == 1)
			sprintf(FloatChar," T:-0%d��",Num);
	}
	else
	{
		if(T_Val == 0)
			sprintf(FloatChar," T:+%d��",Num);
		else if(T_Val == 1)
			sprintf(FloatChar," T:-%d��",Num);
	}
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

/*-----------------------------------------------------------------------
LCD12864_Disp_humid				      �� LCD12864��ʾʪ��

�������                      		�� Num:ʪ��   
				    


-----------------------------------------------------------------------*/
void LCD12864_Dis_humid(uint8_t X,uint8_t Y,int Num)
{
	char FloatChar[16];                                                             // ������и�ֵ

	if(Num < 10)
		sprintf(FloatChar," H:+0%d��",Num);
	else
		sprintf(FloatChar," H:+%d��",Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}

/*-----------------------------------------------------------------------
LCD12864_Disp_Data				      �� LCD12864��ʾ����

�������                      		�� Year�꣬ Mouth�£� Day��
				    


-----------------------------------------------------------------------*/
void LCD12864_Disp_Data(uint8_t X,uint8_t Y,uint16_t Year,uint8_t Mouth,uint8_t Day)
{
	char FloatChar[16];                                                             // ������и�ֵ

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
LCD12864_Disp_Data				      �� LCD12864��ʾʱ��

�������                      		�� Num:ʱ��
				    


-----------------------------------------------------------------------*/
void LCD12864_SetDispTime(uint8_t X,uint8_t Y,int Num)
{
	char FloatChar[16];                                                             // ������и�ֵ

	if(Num < 10)
		sprintf(FloatChar,"0%d",Num);
	else
		sprintf(FloatChar,"%d",Num);
	LCD12864_DisplayStrChin(X,Y,FloatChar);
}




