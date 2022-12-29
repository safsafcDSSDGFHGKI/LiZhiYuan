#ifndef _CLOCK_H_
#define  _CLOCK_H_

#include "math.h"

#define PI 3.14159
#define CLOCK_X 120
#define CLOCK_Y 150
#define CENTER_X 120
#define CENTER_Y 160

void clock_base(void);
void showsec(float i);
void showmin(float i);
void showhour(float i,float j);
void repair_clock(float hour,float min,float sec); //修补 被其他指针擦除的部分
#endif
