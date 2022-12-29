#include "nvic.h"
#include "time.h"
/*-----------------------------------------------------------------------
NVIC_Configure  			 				  : NVIC配置函数
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void NVIC_Configure(void)
{
	NVIC_InitTypeDef  NVIC_InitStruct;                     		   // 声明结构体
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);        		   // 设置优先级分组
//	NVIC_InitStruct.NVIC_IRQChannel = Key_IRQChannel;            // 指定中断通道号，参考 stm32f10x.h 头文件
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;    // 设置抢占优先级
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;           // 设置响应优先级
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                 // 使能中断通道	
//	NVIC_Init(&NVIC_InitStruct);                                 // 初始化NVIC
	
//	NVIC_InitStruct.NVIC_IRQChannel = Key1_IRQChannel;           // 指定中断通道号，参考 stm32f10x.h 头文件
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;    // 设置抢占优先级
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;           // 设置响应优先级
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                 // 使能中断通道	
//	NVIC_Init(&NVIC_InitStruct); 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);                                          // 选择组
	NVIC_InitStruct.NVIC_IRQChannel = TIMx_IRQn;                                             // 配置中断源              
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;                                   // 配置抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;                                          // 配置子优先级
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                                             // 使能
	NVIC_Init(&NVIC_InitStruct);
}



