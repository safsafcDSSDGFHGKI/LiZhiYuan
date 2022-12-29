#ifndef __EXIT_H
#define __EXIT_H

#include "stm32f10x.h"

#define EXIT_PORT    GPIOA
#define EXIT_Clock   RCC_APB2Periph_GPIOA

#define GPIO_PortSource GPIO_PortSourceGPIOA
//#define GPIO_PinSource_x  GPIO_PinSource2
#define GPIO_PinSource_y  GPIO_PinSource4

//#define EXTI_Line_x  EXTI_Line2          // �궨���ⲿ�ж���
//#define EXIT_GPIO_x  GPIO_Pin_2          // �궨���ⲿ�ж�����

#define EXTI_Line_y  EXTI_Line4          // �궨���ⲿ�ж���
#define EXIT_GPIO_y  GPIO_Pin_4          // �궨���ⲿ�ж�����

void Exit_Configure(void);

#endif

