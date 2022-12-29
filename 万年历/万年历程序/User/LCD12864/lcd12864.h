#ifndef __LCD12864_
#define __LCD12864_

#include "stm32f10x.h"
#include "GPIO_Bit_Config.h"

#define LCD12864_Clock         RCC_APB2Periph_GPIOB                 // 定义LCD12864 时钟
#define LCD12864_Port          GPIOB                                // 定义LCD12864 GPIO口

#define LCD12864_CS            GPIO_Pin_14                          // 片选引脚
#define LCD12864_SID           GPIO_Pin_13                          // 数据引脚
#define LCD12864_CLK           GPIO_Pin_12                          // 时钟引脚
 
#define LCD12864_CS_H          GPIO_SetBits(LCD12864_Port,LCD12864_CS)      // 输出高电平
#define LCD12864_CS_L          GPIO_ResetBits(LCD12864_Port,LCD12864_CS)    // 输出低电平

#define LCD12864_SID_H         GPIO_SetBits(LCD12864_Port,LCD12864_SID)     // 输出高电平
#define LCD12864_SID_L         GPIO_ResetBits(LCD12864_Port,LCD12864_SID)   // 输出低电平

#define LCD12864_CLK_H         GPIO_SetBits(LCD12864_Port,LCD12864_CLK)     // 输出高电平
#define LCD12864_CLK_L         GPIO_ResetBits(LCD12864_Port,LCD12864_CLK)   // 输出低电平

#define LCD12864_SID_IN()      {LCD12864_Port->CRH &= 0XFF0FFFFF; LCD12864_Port->CRH |= (uint32_t)4<<20;}
#define LCD12864_SID_OUT()     {LCD12864_Port->CRH &= 0XFF0FFFFF; LCD12864_Port->CRH |= (uint32_t)3<<20;}

void LCD12864_WriteData(uint8_t Data);                        // LCD12864写数据
void LCD12864_WriteCmd(uint8_t Cmd);                          // LCD12864写命令
void LCD12864_Init(void);                                     // LCD12864初始化
void LCD12864_SetLocal(uint8_t X,uint8_t Y);                  // LCD12864设置坐标
void LCD12864_Clear(void);                                    // LCD12864清屏

void LCD12864_DisplayStrChinSingle(uint8_t X,uint8_t Y,char *Str);  // LCD12864显示单个字符 
void LCD12864_DisplayStrChin(uint8_t X,uint8_t Y,char *Str);  // LCD12864显示字符串
void LCD12864_DisplayFlaotInt(uint8_t X,uint8_t Y,double Num);// LCD12864显示整数和浮点数

void LCD12864_DrawPoint(uint8_t x,uint8_t y);                 // LCD12864清屏，和上一个清屏不一样，这个是通过给每个点写0进行清屏
void LCD12864_DrawClear(void);
void LCD12864_DrawPoint(uint8_t x,uint8_t y);
void LCD12864_DrowPic(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t *img); // LCD12864画图

void LCD12864_DrowChines(uint8_t x, uint8_t y,uint8_t Num, uint8_t Local);       // LCD12864通过取模的方式写汉字
void LCD12864_DrowChineseRandom(uint8_t x, uint8_t y,uint8_t Num,uint8_t Local); // LCD12864任意点写16x16汉字
void LCD12864_DrowChineseRandomSize(uint8_t x, uint8_t y,uint8_t Num,uint8_t Local,uint8_t Higth,uint8_t Wide,uint8_t Mode);

void LCD12864_DispChar6x8(uint8_t x, uint8_t y,char Str,uint8_t Mode);
void LCD12864_DispString6x8(uint8_t x, uint8_t y,char *Str,uint8_t Mode);
void LCD12864_DrawFlaotInt(uint8_t X,uint8_t Y,double Num);

void LCD12864_DrawCircle(int x,int y,int r);
void LCD12864_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void LCD12864_DrowPicNum(uint8_t x, uint8_t y, uint8_t Num);
//void LCD12864_DrowPicNum16x8(uint8_t x, uint8_t y, uint8_t Num);

void LCD12864_DisplayFlaotIntDate(uint8_t X,uint8_t Y,double Num);
void LCD12864_DisplayFlaotIntDateYear(uint8_t X,uint8_t Y,double Num);
void LCD12864_DisplayFlaotIntDateTemp(uint8_t X,uint8_t Y,double Num);
void LCD12864_DrowWeek(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t Num);
void LCD12864_DisplayFlaotIntDateH(uint8_t X,uint8_t Y,double Num);

void LCD12864_Disp_Temp(uint8_t X,uint8_t Y,int Num,uint8_t T_Val);        // 显示温度
void LCD12864_Dis_humid(uint8_t X,uint8_t Y,int Num);                      // 显示湿度
void LCD12864_Disp_Data(uint8_t X,uint8_t Y,uint16_t Year,uint8_t Mouth,uint8_t Day);       // 显示年月日

void LCD12864_DrowChines_N(uint8_t x, uint8_t y,uint8_t Num, uint8_t Local,uint8_t Val);       
void LCD12864_DrowSet(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t Num,uint8_t Val);
void LCD12864_SetDispTime(uint8_t X,uint8_t Y,int Num);
void LCD12864_DrowPicNumX(uint8_t x, uint8_t y, uint8_t Num,uint8_t Val);

#endif


