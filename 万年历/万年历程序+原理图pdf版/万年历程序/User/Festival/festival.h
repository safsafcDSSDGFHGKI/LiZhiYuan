#ifndef __FESTIVAL_H
#define __FESTIVAL_H

#include "stm32f10x.h"


uint8_t Festival_Yearly(uint16_t Year,uint8_t Mouth,uint8_t Day);       // ��ʾ��������
void Festival_YearlyongLi_N(uint8_t Mouth,uint8_t Day);              // ��ʾũ������
void Get_JieQi(uint8_t mouth,uint8_t day);                           // ��ʾ24����
void Return_Festival(uint8_t Valu);

#endif


