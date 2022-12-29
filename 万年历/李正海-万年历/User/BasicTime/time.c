#include "time.h"

/*-----------------------------------------------------------------------
Time_Configure  			 	        : 基本定时器初始化
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
static void Time_Configure(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APBxPeriphClock(RCC_APBxPeriph_TIMx,ENABLE); 
	
	TIM_TimeBaseInitStruct.TIM_Period = TIMx_Period;                                    // 自动重装载寄存器的值
	TIM_TimeBaseInitStruct.TIM_Prescaler = TIMx_Prescaler;                              // 时钟预分频系数
	TIM_ITConfig(TIMx, TIM_IT_Update,ENABLE);                                           // 使能中断
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);                                    // 初始化基本定时器
//	TIM_Cmd(TIMx,ENABLE);
}

void BasicTime_Init()
{
	Time_Configure();
}

