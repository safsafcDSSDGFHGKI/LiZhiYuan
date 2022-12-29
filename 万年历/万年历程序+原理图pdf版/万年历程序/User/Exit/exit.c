#include "exit.h"

/*-----------------------------------------------------------------------
Exit_Configure  			 				  : 外部中断配置函数(中断服务函数在 stm32f10x_it.c 中)
	
输入参数                   			：无
                                  
编写日期                        	：2018年11月19日
最后修改日期                  		：2018年11月19日
-----------------------------------------------------------------------*/
void Exit_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;                                // 声明结构体
	EXTI_InitTypeDef EXTI_InitStruct;                                // 声明结构体
		
	RCC_APB2PeriphClockCmd(EXIT_Clock, ENABLE);                      // 开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);             // 开启复用时钟
		
//	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource_x);          // 选择GPIO引脚作为外部中断线路
//	GPIO_InitStruct.GPIO_Pin = EXIT_GPIO_x;                          // 设置中断引脚
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                       // 设置输入模式
//	GPIO_Init(EXIT_PORT, &GPIO_InitStruct);                              // 初始化结构体
	
	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource_y);          // 选择GPIO引脚作为外部中断线路
	GPIO_InitStruct.GPIO_Pin = EXIT_GPIO_y;                          // 设置中断引脚
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                       // 设置输入模式
	GPIO_Init(EXIT_PORT, &GPIO_InitStruct);                          // 初始化结构体
	
//	EXTI_InitStruct.EXTI_Line = EXTI_Line_x;                         // 选择外部中断线
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;                 // 选择模式
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;             // 选择触发中断的方式
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;                           // 使能中断
	
	EXTI_Init(&EXTI_InitStruct);                                     // 初始化结构体
	EXTI_InitStruct.EXTI_Line = EXTI_Line_y;                         // 选择外部中断线
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;                 // 选择模式
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;             // 选择触发中断的方式
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;                           // 使能中断
	EXTI_Init(&EXTI_InitStruct); 
}

