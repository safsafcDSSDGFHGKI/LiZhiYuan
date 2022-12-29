#ifndef __DS3231_H
#define __DS3231_H

#include "stm32f10x.h"

#define IIC_WriteAddress 0xD0                                                     // DS3232������ַ��д���� = 1101 0000 = 0xD0
#define IIC_ReadAddress  0xD1																											// DS3232������ַ�Ͷ����� = 1101 0001 = 0xD1

void IIC_WriteOneByte(uint8_t Addr,uint8_t Data);                                 // IICд���ݵ�IIC����
uint8_t IIC_ReadOneByte(uint8_t Addr);                                            // �������ж�������
void IIC_WriteMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num);                  // д������ݵ�����
void IIC_ReadMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num);                   // �������ж����������
void IIC_GetTemp(uint8_t *Arry);                                                  // ��ȡ�¶�

#endif

