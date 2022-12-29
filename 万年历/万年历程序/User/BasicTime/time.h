#ifndef __TIME_H
#define __TIME_H

#include "stm32f10x.h"

// 当需要哪一个定时器，只需要把下面的宏定义改为1即可
#define General_TIM2    0
#define General_TIM3    1
#define General_TIM4    0
#define General_TIM5    0


#if  General_TIM2                                         // 定时器2
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM2               // 定时器x时钟
	#define TIMx                 TIM2                              // 定时器x
	#define TIMx_IRQHandler      TIM2_IRQHandler                   // 定时器中断函数
	#define TIMx_IRQn            TIM2_IRQn                         // 中断向量

	//时钟频率72MHz 定时时间 = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1
#elif General_TIM3                                         // 定时器3
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM3               // 定时器x时钟
	#define TIMx                 TIM3                              // 定时器x
	#define TIMx_IRQHandler      TIM3_IRQHandler                   // 定时器中断函数
	#define TIMx_IRQn            TIM3_IRQn                         // 中断向量

	//时钟频率72MHz 定时时间 = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1

#elif General_TIM4                                         // 定时器3
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM4               // 定时器x时钟
	#define TIMx                 TIM4                              // 定时器x
	#define TIMx_IRQHandler      TIM4_IRQHandler                   // 定时器中断函数
	#define TIMx_IRQn            TIM4_IRQn                         // 中断向量

	//时钟频率72MHz 定时时间 = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1

#elif General_TIM5                                         // 定时器3
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM5               // 定时器x时钟
	#define TIMx                 TIM5                              // 定时器x
	#define TIMx_IRQHandler      TIM5_IRQHandler                   // 定时器中断函数
	#define TIMx_IRQn            TIM5_IRQn                         // 中断向量

	//时钟频率72MHz 定时时间 = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1
#endif

void BasicTime_Init(void);

#endif


