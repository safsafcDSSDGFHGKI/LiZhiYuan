#ifndef __AT24C32_H
#define __AT24C32_H

#include "stm32f10x.h"

#define AT24C32_WriteAddr  0xAE                                          // AT24C32д��ַ��8λ�� DS3231ʱ��ģ���ϵ�AT24C32��A0 A1 A2�Ӹ�
#define AT24C32_ReadAddr   0xAF                                          // AT24C32д��ַ��8λ��

void AT24C32_WriteOneByte(uint16_t Addr,uint8_t Data);                   // IICд���ݵ�AT24C32����
uint8_t AT24C32_ReadOneByte(uint16_t Addr);                              // ��AT24C32�ж�ȡ����
void AT24C32_PageWrite(uint16_t Addr,uint8_t *Page_Arry,uint8_t num);    // ҳд������
void AT24C32_PageRead(uint16_t Addr,uint8_t *Page_Arry,uint8_t num);     // ҳ��ȡ����
	
#endif

