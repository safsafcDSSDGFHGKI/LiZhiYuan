#ifndef __AT24C32_H
#define __AT24C32_H

#include "stm32f10x.h"

#define AT24C32_WriteAddr  0xAE                                          // AT24C32写地址（8位） DS3231时钟模块上的AT24C32的A0 A1 A2接高
#define AT24C32_ReadAddr   0xAF                                          // AT24C32写地址（8位）

void AT24C32_WriteOneByte(uint16_t Addr,uint8_t Data);                   // IIC写数据到AT24C32器件
uint8_t AT24C32_ReadOneByte(uint16_t Addr);                              // 从AT24C32中读取数据
void AT24C32_PageWrite(uint16_t Addr,uint8_t *Page_Arry,uint8_t num);    // 页写入数据
void AT24C32_PageRead(uint16_t Addr,uint8_t *Page_Arry,uint8_t num);     // 页读取数据
	
#endif

