#ifndef __CALENDAR_H
#define __CALENDAR_H

#include "stm32f10x.h"

//Äê·Ý±í


u8 GetChinaCalendar(u16  year,u8 month,u8 day,u8 *p);
void Get_TianGan_DiZhi_ShengXiao(uint16_t year,uint8_t mouth,uint8_t day);
uint8_t Judge_Week(uint16_t y,uint8_t m,uint8_t d);

#endif
