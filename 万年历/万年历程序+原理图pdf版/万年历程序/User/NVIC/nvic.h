#ifndef __NVIC_H
#define __NVIC_H

#include "stm32f10x.h"

#define NVIC_PriorityGroup_x   NVIC_PriorityGroup_1       // ���鶨��ɺ궨�壬�����д����ֲ����
//#define Key_IRQChannel         EXTI2_IRQn                 // �ⲿ�ж�0���к궨��

#define Key1_IRQChannel        EXTI4_IRQn                 // �ⲿ�ж�0���к궨��

void NVIC_Configure(void);

#endif


