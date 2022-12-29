#ifndef __TIME_H
#define __TIME_H

#include "stm32f10x.h"

// ����Ҫ��һ����ʱ����ֻ��Ҫ������ĺ궨���Ϊ1����
#define General_TIM2    0
#define General_TIM3    1
#define General_TIM4    0
#define General_TIM5    0


#if  General_TIM2                                         // ��ʱ��2
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM2               // ��ʱ��xʱ��
	#define TIMx                 TIM2                              // ��ʱ��x
	#define TIMx_IRQHandler      TIM2_IRQHandler                   // ��ʱ���жϺ���
	#define TIMx_IRQn            TIM2_IRQn                         // �ж�����

	//ʱ��Ƶ��72MHz ��ʱʱ�� = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1
#elif General_TIM3                                         // ��ʱ��3
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM3               // ��ʱ��xʱ��
	#define TIMx                 TIM3                              // ��ʱ��x
	#define TIMx_IRQHandler      TIM3_IRQHandler                   // ��ʱ���жϺ���
	#define TIMx_IRQn            TIM3_IRQn                         // �ж�����

	//ʱ��Ƶ��72MHz ��ʱʱ�� = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1

#elif General_TIM4                                         // ��ʱ��3
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM4               // ��ʱ��xʱ��
	#define TIMx                 TIM4                              // ��ʱ��x
	#define TIMx_IRQHandler      TIM4_IRQHandler                   // ��ʱ���жϺ���
	#define TIMx_IRQn            TIM4_IRQn                         // �ж�����

	//ʱ��Ƶ��72MHz ��ʱʱ�� = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1

#elif General_TIM5                                         // ��ʱ��3
	#define RCC_APBxPeriphClock  RCC_APB1PeriphClockCmd
	#define RCC_APBxPeriph_TIMx  RCC_APB1Periph_TIM5               // ��ʱ��xʱ��
	#define TIMx                 TIM5                              // ��ʱ��x
	#define TIMx_IRQHandler      TIM5_IRQHandler                   // ��ʱ���жϺ���
	#define TIMx_IRQn            TIM5_IRQn                         // �ж�����

	//ʱ��Ƶ��72MHz ��ʱʱ�� = (1/(72000000 /(TIMx_Prescaler+1))) * (TIMx_Period+1) (s)
	#define TIMx_Period          1000-1
	#define TIMx_Prescaler       72-1
#endif

void BasicTime_Init(void);

#endif


