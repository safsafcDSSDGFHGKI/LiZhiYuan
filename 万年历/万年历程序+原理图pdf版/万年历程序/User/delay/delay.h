#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void Delay_us(unsigned int us);
void Delay_ms(unsigned int ms);
void Delay_s(unsigned int s);
void Delay(uint16_t time); 
void delay_us(uint32_t time);
void delay_ms(uint32_t time);

#endif
