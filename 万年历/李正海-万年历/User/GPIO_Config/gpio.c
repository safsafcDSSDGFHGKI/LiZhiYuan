#include "gpio.h"

/*-----------------------------------------------------------------------

  GPIO_Mode_AIN                      模拟输入
  GPIO_Mode_IN_FLOATING              浮空输入 
  GPIO_Mode_IPD                      下拉输入
  GPIO_Mode_IPU                      上拉输入
  GPIO_Mode_Out_OD                   开漏输出
  GPIO_Mode_Out_PP                   推挽输出
  GPIO_Mode_AF_OD                    复用开漏输出
  GPIO_Mode_AF_PP                    复用推挽输出

-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------
LCD12864_KEY_Congigure  			 	: 功能按键初始化
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void LCD12864_KEY_Congigure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                        // 声明结构体
	RCC_APB2PeriphClockCmd(KFB_KEY_Clock, ENABLE);              // 开启GPIOA时钟
																															
  GPIO_InitStructure.GPIO_Pin = KFB_KEY_Pin;              		// 设置引脚号
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               // 设置GPIO的模式
  GPIO_Init(KFB_KEY_Port, &GPIO_InitStructure);               // 初始化结构体
}


void LCD12864_LED_BACK(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                        // 声明结构体
	RCC_APB2PeriphClockCmd(KFB_KEY_Clock, ENABLE);              // 开启GPIOA时钟
																															
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;              		// 设置引脚号
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;               // 设置GPIO的模式
  GPIO_Init(KFB_KEY_Port, &GPIO_InitStructure);               // 初始化结构体
}
