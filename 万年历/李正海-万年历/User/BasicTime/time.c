#include "time.h"

/*-----------------------------------------------------------------------
Time_Configure  			 	        : ������ʱ����ʼ��
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
static void Time_Configure(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	RCC_APBxPeriphClock(RCC_APBxPeriph_TIMx,ENABLE); 
	
	TIM_TimeBaseInitStruct.TIM_Period = TIMx_Period;                                    // �Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = TIMx_Prescaler;                              // ʱ��Ԥ��Ƶϵ��
	TIM_ITConfig(TIMx, TIM_IT_Update,ENABLE);                                           // ʹ���ж�
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStruct);                                    // ��ʼ��������ʱ��
//	TIM_Cmd(TIMx,ENABLE);
}

void BasicTime_Init()
{
	Time_Configure();
}

