#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

void USART1_Init(uint32_t Band_Rate);                                        // USART1��ʼ��
void USART2_Init(uint32_t Band_Rate);                                        // USART2��ʼ��
void USART3_Init(uint32_t Band_Rate);                                        // USART3��ʼ��
void USART4_Init(uint32_t Band_Rate);                                        // USART4��ʼ��
void USART5_Init(uint32_t Band_Rate);                                        // USART5��ʼ��
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data);                   // ����һ���ֽ�
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data);              // ���������ֽ�
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num);    // ���Ͱ�λ���ݵ�����
void Usart_SendStr(USART_TypeDef* pUSARTx, uint8_t *str);                    // �����ַ���

#endif

