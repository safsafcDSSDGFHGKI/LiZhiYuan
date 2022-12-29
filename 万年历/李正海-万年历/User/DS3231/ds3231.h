#ifndef __DS3231_H
#define __DS3231_H

#include "stm32f10x.h"

#define IIC_WriteAddress 0xD0                                                     // DS3232器件地址和写数据 = 1101 0000 = 0xD0
#define IIC_ReadAddress  0xD1																											// DS3232器件地址和读数据 = 1101 0001 = 0xD1

void IIC_WriteOneByte(uint8_t Addr,uint8_t Data);                                 // IIC写数据到IIC器件
uint8_t IIC_ReadOneByte(uint8_t Addr);                                            // 从器件中读出数据
void IIC_WriteMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num);                  // 写多个数据到器件
void IIC_ReadMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num);                   // 从器件中读出多个数据
void IIC_GetTemp(uint8_t *Arry);                                                  // 获取温度

#endif

