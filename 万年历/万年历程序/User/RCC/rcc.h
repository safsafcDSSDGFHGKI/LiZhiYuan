#ifndef __RCC_H
#define __RCC_H

#include "stm32f10x.h"

void HSE_SystemClock(uint32_t RCC_PLLMul_x);      // 外部系统时钟函数
void MCO_GPIO_Config(void);

#endif

