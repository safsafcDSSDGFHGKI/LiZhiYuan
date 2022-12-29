#ifndef __PICTURE_H
#define __PICTURE_H

#include "stm32f10x.h"

uint8_t  KaiJiDongHua[] ={
	/*--  调入了一幅图像：KaiJiDongHua  --*/
/*--  宽度x高度=128x64  --*/
	 

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,
0x00,0x04,0x00,0x00,0x00,0x06,0x01,0xFF,0xF8,0xCF,0xF8,0x00,0x01,0xFF,0xF8,0x02,0x00,0x68,0x00,0x00,0x00,0x0F,0x80,0x02,0x00,0x10,0x00,0x00,0x00,0x32,0xC0,0x42,0x01,0x2F,0xF0,0x00,
0x00,0xE2,0x30,0x42,0x00,0xCB,0x30,0x00,0x01,0x80,0x08,0x43,0xF0,0x59,0xA0,0x00,0x00,0x7F,0xE0,0x42,0x00,0x3F,0xF8,0x00,0x00,0x03,0x80,0x42,0x00,0x52,0x20,0x00,0x00,0x02,0x00,0x42,
0x00,0xD3,0x20,0x00,0x01,0xFF,0xF8,0x42,0x00,0x90,0x20,0x00,0x00,0x02,0x00,0x42,0x00,0x9F,0xF8,0x00,0x00,0x02,0x01,0xFF,0xF9,0x80,0x20,0x00,0x00,0x1E,0x00,0x00,0x01,0x01,0xE0,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,
0x00,0x0F,0xFE,0x3F,0xE3,0xFF,0x00,0x00,0x00,0x01,0x00,0x42,0x02,0x10,0x00,0x00,0x00,0x01,0x00,0xC2,0x02,0x10,0x00,0x00,0x00,0x01,0xF8,0xBF,0xE2,0xFF,0x00,0x00,0x00,0x01,0x08,0x22,
0x02,0x11,0x00,0x00,0x00,0x02,0x08,0x22,0x02,0x20,0x00,0x00,0x00,0x02,0x08,0xFF,0xF2,0x22,0x00,0x00,0x00,0x06,0x08,0x02,0x02,0x22,0x00,0x00,0x00,0x04,0x08,0x02,0x02,0x42,0x00,0x00,
0x00,0x08,0x70,0x02,0x04,0x9E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x20,0x04,0x80,0x80,0x00,0x08,0x00,0x04,0x26,0x04,0x80,0x8F,0x82,0x08,0x00,0x07,0xAC,0x04,0x80,
0x48,0x81,0x08,0x00,0x04,0x30,0x64,0x98,0x08,0x80,0x08,0x00,0x04,0x22,0x24,0x90,0x18,0xEE,0x08,0x00,0x05,0xA2,0x34,0x93,0x80,0x02,0x7F,0x80,0x0E,0x3E,0x14,0xA0,0x9F,0xC2,0x08,0x00,
0x00,0x40,0x14,0xA0,0x88,0x82,0x08,0x00,0x00,0x40,0x04,0x80,0x8C,0x82,0x08,0x00,0x1F,0xFE,0x04,0x80,0xA7,0x02,0xC8,0x00,0x00,0x40,0x04,0x80,0xE7,0x03,0x88,0x00,0x00,0x40,0x7F,0xF8,
0x98,0xE2,0x08,0x00,0x00,0x40,0x00,0x00,0x20,0x20,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00


};
//uint8_t Li_Zhenghai[] = 
//{
//	/*--  调入了一幅图像：C:\Users\Li_Zhenghai\Desktop\xx.bmp  --*/
//	/*--  宽度x高度=128x16  --*/
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x00,0x00,0x04,0x00,0x00,0x00,0xD6,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x00,0x01,0x04,0x00,0x00,0x00,0x54,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x00,0xC1,0x04,0x00,0x00,0x00,0x54,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x89,0x27,0xC4,0x07,0x11,0x1C,0x54,0x70,0xE0,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x89,0x01,0x04,0x08,0x91,0x22,0x6C,0x89,0x10,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x88,0xC1,0x04,0x08,0x91,0x3C,0x28,0xF1,0x10,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x44,0x88,0x21,0x04,0x08,0x8A,0x20,0x28,0x81,0x10,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x48,0x89,0x21,0x04,0x08,0x8E,0x22,0x28,0x89,0x10,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x30,0x70,0xC0,0xC7,0xC7,0x04,0x1C,0x28,0x71,0x10,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//};

//uint8_t Study[] = 
//{
//	/*--  调入了一幅图像：C:\Users\Li_Zhenghai\Desktop\xx.bmp  --*/
///*--  宽度x高度=128x16  --*/
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x02,0x00,0x00,0x00,0x04,0x00,0x7F,0xFC,0x20,0x00,0x40,0x00,0x90,0x80,0x00,0x00,
//0x02,0x00,0x0F,0xFE,0x04,0x9E,0x04,0x40,0x23,0xF0,0x47,0xE0,0x49,0x03,0xFF,0x80,
//0x03,0xFF,0x00,0x40,0x1E,0x92,0x04,0x40,0x20,0x10,0x40,0x20,0x02,0x00,0x00,0x80,
//0x04,0x00,0x00,0x40,0x05,0x12,0x3F,0xF8,0xF8,0x21,0xF0,0x43,0xFF,0xE0,0x00,0x80,
//0x0B,0xFE,0x00,0x40,0x05,0x12,0x24,0x48,0x48,0x40,0x90,0x82,0x00,0x20,0x80,0x80,
//0x02,0x42,0x00,0x40,0x3F,0xD4,0x24,0x48,0x48,0x40,0x90,0x82,0x00,0x20,0x40,0x80,
//0x02,0x22,0x1F,0xFF,0x04,0x14,0x3F,0xF8,0x4B,0xF8,0x97,0xF0,0xFF,0x00,0x44,0x80,
//0x0F,0xFF,0x80,0x40,0x08,0x12,0x02,0x00,0x88,0x41,0x10,0x80,0x02,0x00,0x18,0x80,
//0x02,0x02,0x00,0xA0,0x1F,0x92,0x7F,0xFC,0x48,0x40,0x90,0x80,0x0C,0x00,0x60,0x80,
//0x04,0x42,0x00,0xA0,0x28,0x92,0x04,0x20,0x30,0x40,0x60,0x83,0xFF,0xE1,0x80,0x80,
//0x04,0x22,0x01,0x10,0x0F,0x92,0x0C,0x40,0x10,0x40,0x20,0x80,0x08,0x06,0x00,0x80,
//0x07,0xFF,0x02,0x08,0x08,0x9C,0x03,0x80,0x28,0x40,0x50,0x80,0x08,0x00,0x00,0x80,
//0x00,0x02,0x04,0x04,0x0F,0x90,0x0C,0x70,0x48,0x40,0x90,0x80,0x08,0x00,0x01,0x00,
//0x00,0x0C,0x18,0x03,0x08,0x90,0x70,0x08,0x84,0xC1,0x09,0x80,0x38,0x00,0x06,0x00,
//};
//uint8_t  Photo1[] ={
//	0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x01,0x3F,0xC0,
//	0x80,0x42,0x04,0x20,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x1F,
//	0xFC,0x42,0x04,0xF8,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x80,
//	0x01,0xFF,0xDE,0x88,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x01,0x2A,0x87,
//	0xF0,0xA2,0x0A,0xF8,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0x84,
//	0x10,0xA2,0x0A,0x88,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x1F,
//	0xFC,0xA2,0x0A,0xF8,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x9F,0x90,
//	0x05,0x2F,0xCA,0xA4,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x03,
//	0xE1,0xA8,0x4A,0xA8,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xC2,
//	0x24,0x48,0x44,0x90,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x84,
//	0x24,0xA8,0x4A,0xA8,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0xA6,0x58,
//	0x3D,0x0F,0xD0,0xC4,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x1C,0xFF,0xC0,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x23,0x08,0x37,0x80,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x40,0x10,0x08,0x40,0x00,0xFF,0x90,
//	0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x81,0x86,0x10,0x40,0x00,0x08,0x08,
//	0x10,0xFF,0x86,0x00,0x00,0x00,0x00,0x00,
//	0x01,0x02,0x49,0x40,0x40,0x00,0x7F,0x0B,
//	0xFC,0x08,0x0F,0x00,0x00,0x00,0x00,0x00,
//	0x01,0x08,0x00,0x40,0x20,0x00,0x10,0x00,
//	0x10,0x49,0x0F,0x00,0x00,0x00,0x00,0x00,
//	0x02,0x08,0x00,0x20,0x20,0x01,0xFF,0xDD,
//	0x10,0x2A,0x0F,0x00,0x00,0x00,0x00,0x00,
//	0x04,0x31,0x83,0x20,0x20,0x00,0x20,0x04,
//	0x91,0xFF,0xC6,0x00,0x00,0x00,0x00,0x00,
//	0x04,0x52,0x44,0x90,0x20,0x00,0x7F,0x04,
//	0x90,0x1C,0x06,0x00,0x00,0x00,0x00,0x00,
//	0x09,0xA4,0x28,0x4C,0x10,0x00,0xA1,0x04,
//	0x10,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x0E,0x44,0xE9,0xC3,0x90,0x01,0x3F,0x04,
//	0x70,0x49,0x06,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x82,0xC5,0x81,0x70,0x00,0x21,0x0A,
//	0x01,0x88,0xC6,0x00,0x00,0x00,0x00,0x00,
//	0x01,0x01,0x83,0x00,0x80,0x00,0x3F,0x11,
//	0xFC,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x01,0x0C,0x70,0x00,0x80,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x02,0x13,0x87,0x10,0x40,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x02,0x20,0x78,0xA0,0x40,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x02,0x20,0x00,0x60,0x40,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x02,0x21,0x80,0x60,0x40,0x00,0x00,0x71,
//	0xEE,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x01,0x11,0x98,0x90,0x80,0x00,0x00,0x8E,
//	0x31,0xC6,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x01,0x08,0x18,0x80,0x80,0x00,0x01,0x24,
//	0x24,0x83,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x96,0x01,0x01,0x00,0x00,0x01,0x40,
//	0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x49,0x86,0x03,0x00,0x00,0x01,0x40,
//	0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x34,0x78,0x8C,0x00,0x00,0x01,0x00,
//	0x20,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x0E,0x01,0x30,0x00,0x00,0x00,0x80,
//	0x30,0x06,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x71,0x87,0xCE,0x00,0x00,0x00,0x40,
//	0x68,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0xE0,0x78,0x07,0x00,0x00,0x00,0x20,
//	0xC4,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x01,0xAF,0xFF,0xC5,0x80,0x00,0x00,0x11,
//	0x82,0x30,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x03,0xA9,0xB6,0x45,0xC0,0x00,0x00,0x0B,
//	0x01,0x60,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x07,0x2F,0x03,0xC4,0xE0,0x00,0x00,0x06,
//	0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x0E,0x16,0x01,0x88,0x70,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x0F,0x08,0x00,0x10,0xF0,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x0F,0x84,0x00,0x21,0xF0,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
//};
///******************************************************************************/
//uint8_t  Photo2[] ={
///*--  调入了一幅图像：C:\Users\Administrator\Desktop\QQ图片20190211113618.bmp  --*/
///*--  宽度x高度=128x64  --*/
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x3F,0xDF,0xC0,0x00,0x00,0x00,0x00,0x0F,0xEF,0xF0,0x00,0x00,0x00,
//0x00,0x00,0x01,0xC0,0x00,0x3C,0x00,0x00,0x00,0x00,0xF0,0x00,0x0E,0x00,0x00,0x00,
//0x00,0x00,0x06,0x00,0x00,0x07,0x00,0x00,0x00,0x03,0x80,0x00,0x01,0x80,0x00,0x00,
//0x00,0x00,0x18,0x00,0x00,0x00,0x80,0x00,0x00,0x04,0x00,0x00,0x00,0x60,0x00,0x00,
//0x00,0x00,0x30,0x00,0x00,0x00,0x60,0x00,0x00,0x18,0x00,0x00,0x00,0x30,0x00,0x00,
//0x00,0x00,0x40,0x00,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x00,0x08,0x00,0x00,
//0x00,0x00,0x80,0x00,0x00,0x00,0x08,0x00,0x00,0x40,0x00,0x00,0x00,0x04,0x00,0x00,
//0x00,0x01,0x00,0x00,0x00,0x00,0x0C,0x00,0x00,0xC0,0x00,0x00,0x00,0x02,0x00,0x00,
//0x00,0x03,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x80,0x00,0x00,0x00,0x03,0x00,0x00,
//0x00,0x02,0x00,0x00,0x00,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,
//0x00,0x04,0x03,0xFC,0x00,0x0F,0xF2,0x00,0x01,0x3F,0xC0,0x00,0xFF,0x00,0x80,0x00,
//0x00,0x04,0x07,0x83,0x00,0x3C,0x09,0x00,0x02,0x40,0xF0,0x03,0x07,0x80,0x80,0x00,
//0x00,0x08,0x1F,0xC0,0xC0,0x3E,0x05,0x00,0x02,0x81,0xF0,0x0C,0x0F,0xE0,0x40,0x00,
//0x00,0x08,0x1F,0xC0,0x40,0x7E,0x02,0x80,0x05,0x01,0xF8,0x08,0x0F,0xE0,0x40,0x00,
//0x00,0x08,0x3F,0xC0,0x20,0x7E,0x02,0x80,0x05,0x01,0xF8,0x10,0x0F,0xF0,0x40,0x00,
//0x00,0x10,0x3F,0xC0,0x20,0x7E,0x02,0x80,0x05,0x01,0xF8,0x10,0x0F,0xF0,0x20,0x00,
//0x00,0x10,0x3F,0xC0,0x10,0x7C,0x02,0x40,0x09,0x00,0xF8,0x20,0x0F,0xF0,0x20,0x00,
//0x00,0x10,0x3F,0xC0,0x00,0x3D,0xFC,0x40,0x08,0xFE,0xF0,0x00,0x0F,0xF0,0x20,0x00,
//0x00,0x10,0x3F,0x80,0x20,0x1C,0x00,0x40,0x08,0x00,0xE0,0x10,0x07,0xF0,0x20,0x00,
//0x00,0x10,0x1F,0xEF,0xC0,0x00,0x00,0x40,0x08,0x00,0x00,0x0F,0xDF,0xE0,0x20,0x00,
//0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x40,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x00,
//0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x40,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x00,
//0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x40,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x00,
//0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x40,0x08,0x00,0x00,0x00,0x00,0x00,0x20,0x00,
//0x00,0x08,0x00,0x00,0x40,0x20,0x00,0x40,0x08,0x00,0x10,0x08,0x00,0x00,0x40,0x00,
//0x00,0x08,0x00,0x00,0x46,0x20,0x00,0x40,0x08,0x00,0x11,0x88,0x00,0x00,0x40,0x00,
//0x00,0x08,0x00,0x00,0x39,0xC0,0x00,0x40,0x08,0x00,0x0E,0x70,0x00,0x00,0x40,0x00,
//0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x80,0x04,0x00,0x00,0x00,0x00,0x00,0x80,0x00,
//0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x80,0x04,0x00,0x00,0x00,0x00,0x00,0x80,0x00,
//0x00,0x02,0x00,0x00,0x00,0x00,0x01,0x80,0x06,0x00,0x00,0x00,0x00,0x01,0x00,0x00,
//0x00,0x03,0x00,0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x03,0x00,0x00,
//0x00,0x01,0x80,0x00,0x00,0x00,0x02,0x00,0x01,0x00,0x00,0x00,0x00,0x06,0x00,0x00,
//0x00,0x00,0xC0,0x00,0x00,0x00,0x04,0x00,0x00,0x80,0x00,0x00,0x00,0x0C,0x00,0x00,
//0x00,0x00,0x60,0x00,0x00,0x00,0x08,0x00,0x00,0x40,0x00,0x00,0x00,0x18,0x00,0x00,
//0x00,0x00,0x18,0x00,0x00,0x00,0x30,0x00,0x00,0x30,0x00,0x00,0x00,0x60,0x00,0x00,
//0x00,0x00,0x06,0x00,0x00,0x00,0xC0,0x00,0x00,0x0C,0x00,0x00,0x01,0x80,0x00,0x00,
//0x00,0x00,0x01,0x80,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x06,0x00,0x00,0x00,
//0x00,0x00,0x00,0x40,0x00,0x3C,0x00,0x00,0x00,0x00,0xF0,0x00,0x08,0x00,0x00,0x00,
//0x00,0x00,0x00,0xF0,0x00,0x60,0x00,0x00,0x00,0x00,0x18,0x00,0x3C,0x00,0x00,0x00,
//0x00,0x00,0x00,0xE0,0x00,0x30,0x00,0x00,0x00,0x00,0x30,0x00,0x1C,0x00,0x00,0x00,
//0x00,0x10,0x03,0x80,0x00,0x58,0x00,0x00,0x00,0x00,0x68,0x00,0x07,0x00,0x20,0x00,
//0x00,0x1E,0x07,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x48,0x00,0x03,0x81,0xE0,0x00,
//0x00,0x10,0x1B,0x00,0x01,0x88,0x00,0x00,0x00,0x00,0x46,0x00,0x03,0x60,0x20,0x00,
//0x03,0xF0,0x22,0x04,0x03,0x04,0x00,0x00,0x00,0x00,0x83,0x00,0x81,0x10,0x3F,0x00,
//0x03,0x80,0x46,0x18,0x02,0x08,0x00,0x00,0x00,0x00,0x41,0x00,0x61,0x88,0x07,0x00,
//0x00,0x80,0x84,0x30,0x03,0x18,0x00,0x00,0x00,0x00,0x63,0x00,0x30,0x84,0x04,0x00,
//0x00,0x40,0x84,0x20,0x01,0xE0,0x00,0x00,0x00,0x00,0x1E,0x00,0x10,0x84,0x08,0x00,
//0x00,0x40,0x9C,0xC0,0x00,0x80,0x00,0x00,0x00,0x00,0x04,0x00,0x0C,0xE4,0x08,0x00,
//0x00,0x40,0x87,0x80,0x01,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x07,0x84,0x08,0x00,
//0x00,0x80,0xA3,0x00,0x41,0x00,0x00,0x00,0x00,0x00,0x02,0x08,0x03,0x14,0x04,0x00,
//0x00,0x00,0xA0,0x00,0x32,0x00,0x00,0x00,0x00,0x00,0x01,0x30,0x00,0x14,0x00,0x00,
//0x00,0x00,0x60,0x00,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0xA0,0x00,0x18,0x00,0x00,
//0x00,0x00,0x20,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x10,0x00,0x00,
//0x00,0x00,0x10,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x20,0x00,0x00,
//0x00,0x00,0x18,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x60,0x00,0x00,
//0x00,0x00,0x37,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x03,0xB0,0x00,0x00,
//0x00,0x00,0x21,0xFC,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0xFE,0x10,0x00,0x00,
//0x00,0x00,0x21,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x41,0x02,0x10,0x00,0x00,
//0x00,0x00,0x22,0x03,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x01,0x10,0x00,0x00,
//0x00,0x00,0x1C,0x01,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x00,0xE0,0x00,0x00,
//0x00,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x00,0x00,0x00,0x00,
//0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};
//uint8_t  Photo3[] = 
//{
///*--  调入了一幅图像：F:\开始学习单片机\芯片资料\IloveU_s.bmp  --*/
///*--  宽度x高度=128x64  --*/
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x66,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x7E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};
//uint8_t  Photo4[] = 
//{
///*--  调入了一幅图像：这是您新建的图像  --*/
///*--  宽度x高度=128x64  --*/
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0xD0,0xF7,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x40,0xB0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x80,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x02,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x80,0x00,0x48,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x40,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x04,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x30,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x10,0x00,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x10,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x10,0xBA,0x05,0x00,0x01,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x48,0x05,0x00,0x40,0xA4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x04,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x04,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x04,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x04,0x00,0x00,0x05,0x0D,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x04,0x01,0x00,0x01,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x5C,0xB4,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x80,0x00,0x0B,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x04,0x01,0x0C,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x06,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x80,0x00,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x01,0x80,0x01,0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x60,0x9A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x0E,0x22,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x02,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x40,0x1A,0x25,0xA4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x20,0x11,0x94,0x02,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
//};

#endif



