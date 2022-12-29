#ifndef __NVIC_H
#define __NVIC_H

#include "stm32f10x.h"

#define NVIC_PriorityGroup_x   NVIC_PriorityGroup_1       // 把组定义成宏定义，方便改写和移植程序
//#define Key_IRQChannel         EXTI2_IRQn                 // 外部中断0进行宏定义

#define Key1_IRQChannel        EXTI4_IRQn                 // 外部中断0进行宏定义

void NVIC_Configure(void);

#endif


