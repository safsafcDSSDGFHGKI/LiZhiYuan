#ifndef __GPIO_H
#define __GPIO_H

#include "stm32f10x.h"

/*-----------------------------------------------------------------------

							ʹ�ú궨����Ը����������޸ĺ���ֲ

-----------------------------------------------------------------------*/
 

#define KFB_KEY_Pin        GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4
#define KFB_KEY_Port       GPIOA
#define KFB_KEY_Clock      RCC_APB2Periph_GPIOA

#define K_UP               PAin(3)              
#define K_Right            PAin(2)
#define K_Left             PAin(1)
#define K_Down             PAin(0)

#define K_Bk               PAin(4)
#define LED_BACK           PAout(5)


void LCD12864_KEY_Congigure(void);
void LCD12864_LED_BACK(void);
#endif


