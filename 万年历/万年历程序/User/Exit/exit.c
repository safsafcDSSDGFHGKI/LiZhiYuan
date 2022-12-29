#include "exit.h"

/*-----------------------------------------------------------------------
Exit_Configure  			 				  : �ⲿ�ж����ú���(�жϷ������� stm32f10x_it.c ��)
	
�������                   			����
                                  
��д����                        	��2018��11��19��
����޸�����                  		��2018��11��19��
-----------------------------------------------------------------------*/
void Exit_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;                                // �����ṹ��
	EXTI_InitTypeDef EXTI_InitStruct;                                // �����ṹ��
		
	RCC_APB2PeriphClockCmd(EXIT_Clock, ENABLE);                      // ����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);             // ��������ʱ��
		
//	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource_x);          // ѡ��GPIO������Ϊ�ⲿ�ж���·
//	GPIO_InitStruct.GPIO_Pin = EXIT_GPIO_x;                          // �����ж�����
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                       // ��������ģʽ
//	GPIO_Init(EXIT_PORT, &GPIO_InitStruct);                              // ��ʼ���ṹ��
	
	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource_y);          // ѡ��GPIO������Ϊ�ⲿ�ж���·
	GPIO_InitStruct.GPIO_Pin = EXIT_GPIO_y;                          // �����ж�����
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;                       // ��������ģʽ
	GPIO_Init(EXIT_PORT, &GPIO_InitStruct);                          // ��ʼ���ṹ��
	
//	EXTI_InitStruct.EXTI_Line = EXTI_Line_x;                         // ѡ���ⲿ�ж���
//	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;                 // ѡ��ģʽ
//	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;             // ѡ�񴥷��жϵķ�ʽ
//	EXTI_InitStruct.EXTI_LineCmd = ENABLE;                           // ʹ���ж�
	
	EXTI_Init(&EXTI_InitStruct);                                     // ��ʼ���ṹ��
	EXTI_InitStruct.EXTI_Line = EXTI_Line_y;                         // ѡ���ⲿ�ж���
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;                 // ѡ��ģʽ
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;             // ѡ�񴥷��жϵķ�ʽ
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;                           // ʹ���ж�
	EXTI_Init(&EXTI_InitStruct); 
}

