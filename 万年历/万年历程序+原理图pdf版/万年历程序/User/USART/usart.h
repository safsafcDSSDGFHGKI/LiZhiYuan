#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Init(uint32_t Band_Rate);                                        // USART1初始化
void USART2_Init(uint32_t Band_Rate);                                        // USART2初始化
void USART3_Init(uint32_t Band_Rate);                                        // USART3初始化
void USART4_Init(uint32_t Band_Rate);                                        // USART4初始化
void USART5_Init(uint32_t Band_Rate);                                        // USART5初始化
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data);                   // 发送一个字节
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data);              // 发送两个字节
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num);    // 发送八位数据的数组
void Usart_SendStr(USART_TypeDef* pUSARTx, uint8_t *str);                    // 发送字符串

#endif

