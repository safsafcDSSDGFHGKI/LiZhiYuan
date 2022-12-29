#ifndef __STRCHINESE_H
#define __STRCHINESE_H

#include "stm32f10x.h"

#define Arry_Wide   128                           // 定义数组宽度，方便改写


uint8_t  Chinese[][Arry_Wide] = 
{
		{ 
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x00,0x01,0xE0,0x00,0x00,0x07,0x80,0x00,
			0x00,0x1C,0x1C,0x00,0x00,0x06,0x1C,0x00,0x00,0x43,0x30,0x00,0x00,0x73,0x20,0x00,0x00,0x31,0x43,0xC0,0x00,0x10,0x7F,0xE0,
			0x02,0x1F,0x81,0xF0,0x03,0xE6,0x01,0x80,0x06,0x07,0x02,0x00,0x06,0x06,0x0C,0x00,0x0C,0x04,0xFE,0x00,0x05,0xFF,0xE0,0x00,
			0x00,0xEC,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x18,0xF0,0x00,0x00,0x17,0x30,0x00,0x00,0x30,0x30,0x00,0x00,0x6E,0x60,0x00,
			0x00,0xC1,0xE0,0x00,0x01,0x80,0xE0,0x00,0x03,0x01,0xF0,0x00,0x06,0x07,0x1E,0x00,0x08,0x0C,0x0F,0xC0,0x00,0x70,0x03,0xFC,
			0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00
	  },/*"爱",0*/
		{
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x00,0x07,0x80,0x00,
			0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x3F,0x80,0x00,0x03,0xF8,0x00,0x00,0x3F,0x00,0x00,
			0x03,0xE1,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0x80,0x00,0x00,0xC1,0x80,0x00,0x00,0x21,0x80,0x00,0x00,0x13,0x00,0x00,
			0x00,0x0B,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x0F,0x80,0x00,0x00,0x1D,0xC0,0x00,0x00,0x38,0xE0,0x00,
			0x00,0xE0,0x78,0x00,0x07,0x80,0x3F,0x00,0x08,0x00,0x1F,0xF0,0x00,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		},/*"文",0*/
		
		{
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x06,0x00,0x00,
			0x00,0x06,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x06,0x0C,0x00,0x00,0x07,0xFF,0x00,0x07,0xFE,0x07,0x80,0x07,0x84,0x07,0x00,
			0x02,0x04,0x06,0x00,0x03,0x04,0x06,0x00,0x03,0x1F,0xCE,0x00,0x03,0x7C,0x0C,0x00,0x01,0x04,0x0C,0x00,0x01,0x04,0x08,0x00,
			0x01,0x04,0x78,0x00,0x01,0xFF,0xF0,0x00,0x01,0x84,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x04,0x00,0x20,
			0x00,0x06,0x00,0x20,0x00,0x06,0x00,0x30,0x00,0x03,0x80,0xF0,0x00,0x01,0xFF,0xE0,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		},/*"电",2*/
		{
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x00,0x00,0x01,0xFE,0x00,
			0x00,0xFE,0x1E,0x00,0x00,0x70,0x1C,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x40,0x00,0x00,0x03,0x80,0x00,
			0x00,0x01,0x80,0x00,0x00,0x01,0x8F,0xF8,0x00,0x07,0xFF,0xF8,0x0F,0xFF,0xC0,0x00,0x1F,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,
			0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,
			0x00,0x00,0xC0,0x00,0x00,0x00,0xC0,0x00,0x00,0x01,0xC0,0x00,0x00,0x1F,0xC0,0x00,0x00,0x0F,0x80,0x00,0x00,0x03,0x80,0x00,
			0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00
		},/*"子",3*/


	{0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00},/*"王",0*/
	{0x08,0x40,0x08,0x40,0x08,0x40,0x13,0xF8,0x10,0x40,0x30,0x80,0x37,0xFE,0x50,0x80,0x91,0x00,0x13,0xF8,0x10,0x08,0x11,0x10,0x10,0xA0,0x10,0x40,0x10,0x20,0x10,0x20},/*"传",0*/
	{0x00,0x00,0xF9,0xFC,0x09,0x04,0x09,0x04,0x09,0xFC,0x78,0x20,0x40,0x20,0x43,0xFE,0x42,0x22,0x7A,0x22,0x0B,0xFE,0x08,0x20,0x08,0x24,0x08,0x22,0x57,0xFE,0x20,0x02},/*"强",0*/
		
	{0x11,0x08,0x15,0x48,0x25,0x48,0x45,0x50,0x97,0xDE,0x10,0x24,0x20,0x14,0x6F,0xD4,0xA0,0x14,0x27,0x94,0x24,0x94,0x24,0xA8,0x24,0xC8,0x24,0x94,0x28,0x14,0x30,0x22},/*"微",0*/
	{0x08,0x40,0x08,0x20,0x0B,0xFE,0x10,0x00,0x10,0x00,0x31,0xFC,0x30,0x00,0x50,0x00,0x91,0xFC,0x10,0x00,0x10,0x00,0x11,0xFC,0x11,0x04,0x11,0x04,0x11,0xFC,0x11,0x04},/*"信",1*/
	{0x00,0x80,0x04,0x80,0x04,0x80,0x08,0x40,0x08,0x40,0x10,0x20,0x20,0x10,0x42,0x08,0x82,0x06,0x04,0x00,0x04,0x40,0x08,0x20,0x10,0x20,0x3F,0xF0,0x10,0x10,0x00,0x00},/*"公",2*/
	{0x01,0x00,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x10,0x10,0x28,0x28,0xC8,0x26,0x08,0x20,0x08,0x20,0x08,0x20,0x14,0x50,0x12,0x50,0x22,0x88,0x41,0x04,0x82,0x02},/*"众",3*/
	{0x00,0x00,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x00,0x00,0xFF,0xFE,0x08,0x00,0x10,0x00,0x1F,0xF0,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0xA0,0x00,0x40},/*"号",4*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x30,0x00,0x30,0x00,0x00,0x00,0x00,0x00},/*"：",5*/
	
	{0x00,0x08,0x01,0xFC,0x7E,0x10,0x22,0x10,0x11,0x20,0x7F,0xFE,0x42,0x02,0x82,0x04,0x7F,0xF8,0x04,0x00,0x07,0xF0,0x0A,0x10,0x11,0x20,0x20,0xC0,0x43,0x30,0x1C,0x0E},/*"爱",0*/
	{0x02,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x10,0x10,0x10,0x10,0x08,0x20,0x08,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x30,0x18,0xC0,0x06},/*"文",1*/
	{0x01,0x00,0x01,0x00,0x01,0x00,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x0A,0x01,0x02,0x01,0x02,0x00,0xFE},/*"电",2*/
	{0x00,0x00,0x7F,0xF8,0x00,0x10,0x00,0x20,0x00,0x40,0x01,0x80,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x05,0x00,0x02,0x00},/*"子",3*/
		
		

};

uint8_t  Num32x16[][64] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x2F,0xF4,0x30,0x0C,0x38,0x1C,
	0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x30,0x0C,0x20,0x04,
	0x30,0x0C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x0C,
	0x30,0x04,0x2F,0xF8,0x1F,0xFC,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*0*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0xC0,0x01,0xC0,0x03,0xC0,0x03,0xC0,
	0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x01,0xC0,0x00,0xC0,0x00,0x40,
	0x00,0xC0,0x01,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,
	0x03,0xC0,0x01,0xC0,0x00,0xC0,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, /*1*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x0F,0xF4,0x00,0x0C,0x00,0x1C,
	0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x0C,0x0F,0xF4,0x1F,0xF8,
	0x2F,0xF0,0x30,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,
	0x38,0x00,0x30,0x00,0x2F,0xF0,0x1F,0xF8,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00},  /*2*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x0F,0xF4,0x00,0x0C,0x00,0x1C,
	0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x0F,0xEC,0x1F,0xF4,
	0x0F,0xEC,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,
	0x00,0x1C,0x00,0x0C,0x0F,0xF4,0x1F,0xF8,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00},  /*3*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x04,0x30,0x0C,0x38,0x1C,0x38,0x1C,0x38,0x1C,
	0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x37,0xEC,0x2F,0xF4,0x07,0xEC,
	0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,
	0x00,0x1C,0x00,0x1C,0x00,0x0C,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*4*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x2F,0xF0,0x30,0x00,0x38,0x00,
	0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x37,0xF8,0x2F,0xF4,0x1F,0xEC,
	0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,
	0x00,0x0C,0x0F,0xF4,0x1F,0xF8,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*5*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x2F,0xF0,0x30,0x00,0x38,0x00,
	0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x38,0x00,0x37,0xE0,0x2F,0xF4,0x37,0xEC,
	0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,
	0x30,0x0C,0x2F,0xF4,0x1F,0xF8,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*6*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x0F,0xF4,0x00,0x0C,0x00,0x1C,
	0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x0C,
	0x00,0x04,0x00,0x0C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,
	0x00,0x1C,0x00,0x1C,0x00,0x0C,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},   /*7*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x2F,0xF4,0x30,0x0C,0x38,0x1C,
	0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x37,0xEC,0x2F,0xF4,
	0x37,0xEC,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,
	0x30,0x0C,0x2F,0xF4,0x1F,0xF8,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},   /*8*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xFC,0x1F,0xF8,0x2F,0xF4,0x30,0x0C,0x38,0x1C,
	0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x38,0x1C,0x37,0xEC,0x2F,0xF4,
	0x1F,0xEC,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,0x00,0x1C,
	0x00,0x0C,0x0F,0xF4,0x1F,0xF8,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*9*/
		
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,
	0x03,0xC0,0x03,0xC0,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*":"*/
	
	{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x03,0xC0,0x00,0x00,0x00,0x00,0x0C,0x30,0x12,0x48,0x21,0x84,0x20,0x04,
	0x10,0x08,0x08,0x10,0x04,0x20,0x02,0x40,0x01,0x80,0x00,0x00,0x0C,0x30,0x0C,0x30,
	0x0C,0x30,0x0C,0x30,0x0C,0x30,0x0F,0xF0,0x07,0xE0,0x00,0x00,0x00,0x00,0x00,0x00},
	
		{
					/*--  文字:  立  --*/
			/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
			0x02,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x10,0x10,0x10,
			0x08,0x20,0x08,0x20,0x04,0x40,0x04,0x40,0x04,0x80,0x00,0x00,0xFF,0xFE,0x00,0x00,

			/*--  文字:  春  --*/
			/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
			0x01,0x00,0x01,0x00,0x7F,0xFC,0x01,0x00,0x3F,0xF8,0x02,0x00,0xFF,0xFE,0x08,0x20,
			0x10,0x10,0x2F,0xE8,0xC8,0x26,0x08,0x20,0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,
		},
		
		{/*--  文字:  雨  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFC,0x41,0x04,0x41,0x04,
	0x49,0x44,0x45,0x24,0x41,0x04,0x49,0x44,0x45,0x24,0x41,0x04,0x41,0x14,0x40,0x08,

	/*--  文字:  水  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x08,0x01,0x08,0x7D,0x90,0x05,0xA0,0x09,0x40,
	0x09,0x40,0x11,0x20,0x11,0x10,0x21,0x08,0x41,0x06,0x81,0x00,0x05,0x00,0x02,0x00,},
		
	{/*--  文字:  惊  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x10,0x40,0x10,0x20,0x13,0xFE,0x10,0x00,0x18,0x00,0x55,0xFC,0x51,0x04,0x51,0x04,
	0x11,0xFC,0x10,0x20,0x11,0x28,0x11,0x24,0x12,0x22,0x14,0x22,0x10,0xA0,0x00,0x40,

	/*--  文字:  蛰  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x10,0x80,0x10,0x80,0x7B,0xF0,0x10,0x90,0x19,0x90,0x70,0x94,0x11,0x54,0x56,0x0C,
	0x21,0x00,0x1F,0xF0,0x11,0x10,0x11,0x10,0x1F,0xF0,0x01,0x08,0x7F,0xFC,0x00,0x04,},

	{/*--  文字:  春  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x7F,0xFC,0x01,0x00,0x3F,0xF8,0x02,0x00,0xFF,0xFE,0x08,0x20,
	0x10,0x10,0x2F,0xE8,0xC8,0x26,0x08,0x20,0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,

	/*--  文字:  分  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x00,0x04,0x40,0x04,0x20,0x08,0x20,0x10,0x10,0x20,0x08,0x40,0x04,0x9F,0xE2,
	0x04,0x20,0x04,0x20,0x04,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x21,0x40,0x40,0x80,},

	{/*--  文字:  清  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x40,0x20,0x40,0x17,0xFC,0x10,0x40,0x83,0xF8,0x40,0x40,0x47,0xFE,0x10,0x00,
	0x13,0xF8,0x22,0x08,0xE3,0xF8,0x22,0x08,0x23,0xF8,0x22,0x08,0x22,0x28,0x02,0x10,

	/*--  文字:  明  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x00,0x00,0xFC,0x7C,0x84,0x44,0x84,0x44,0x84,0x44,0xFC,0x7C,0x84,0x44,0x84,
	0x44,0x84,0x44,0xFC,0x7C,0x84,0x44,0x84,0x01,0x04,0x01,0x04,0x02,0x14,0x04,0x08,},

	{
	/*--  文字:  谷  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x08,0x20,0x08,0x10,0x11,0x08,0x21,0x04,0x42,0x80,0x04,0x40,0x08,0x20,0x30,0x18,
	0xC0,0x06,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,

	/*--  文字:  雨  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFC,0x41,0x04,0x41,0x04,
	0x49,0x44,0x45,0x24,0x41,0x04,0x49,0x44,0x45,0x24,0x41,0x04,0x41,0x14,0x40,0x08,
	},
	{
	/*--  文字:  立  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x02,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x10,0x10,0x10,
	0x08,0x20,0x08,0x20,0x04,0x40,0x04,0x40,0x04,0x80,0x00,0x00,0xFF,0xFE,0x00,0x00,

	/*--  文字:  夏  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x7F,0xFC,0x02,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,
	0x1F,0xF0,0x08,0x00,0x1F,0xF0,0x28,0x20,0x44,0x40,0x03,0x80,0x1C,0x70,0xE0,0x0E,
	},
	{
	/*--  文字:  小  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x10,0x11,0x08,0x11,0x04,
	0x21,0x04,0x21,0x02,0x41,0x02,0x81,0x02,0x01,0x00,0x05,0x00,0x03,0x00,0x00,0x00,

	/*--  文字:  满  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x08,0x21,0x08,0x17,0xFE,0x11,0x08,0x80,0x00,0x47,0xFE,0x40,0x90,0x10,0x90,
	0x17,0xFE,0x24,0x92,0xE4,0x92,0x25,0x6A,0x26,0x46,0x24,0x02,0x24,0x0A,0x04,0x04,
	},
	{
	/*--  文字:  芒  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x08,0x20,0x08,0x20,0xFF,0xFE,0x08,0x20,0x08,0x20,0x02,0x00,0x01,0x00,0xFF,0xFE,
	0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x0F,0xFC,0x00,0x00,

	/*--  文字:  种  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x08,0x20,0x1C,0x20,0xF0,0x20,0x10,0x20,0x11,0xFC,0xFD,0x24,0x11,0x24,0x31,0x24,
	0x39,0x24,0x55,0xFC,0x55,0x24,0x90,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,
	},
	{
	/*--  文字:  小  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x10,0x11,0x08,0x11,0x04,
	0x21,0x04,0x21,0x02,0x41,0x02,0x81,0x02,0x01,0x00,0x05,0x00,0x03,0x00,0x00,0x00,

	/*--  文字:  暑  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x02,0x00,0x1F,0xD0,0x02,0x20,
	0xFF,0xFE,0x03,0x00,0x0F,0xF0,0x38,0x10,0xCF,0xF0,0x08,0x10,0x0F,0xF0,0x08,0x10,
	},
	{
	/*--  文字:  大  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,
	0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06,

	/*--  文字:  暑  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x02,0x00,0x1F,0xD0,0x02,0x20,
	0xFF,0xFE,0x03,0x00,0x0F,0xF0,0x38,0x10,0xCF,0xF0,0x08,0x10,0x0F,0xF0,0x08,0x10,
	},
	{
	/*--  文字:  立  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x02,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x10,0x10,0x10,
	0x08,0x20,0x08,0x20,0x04,0x40,0x04,0x40,0x04,0x80,0x00,0x00,0xFF,0xFE,0x00,0x00,

	/*--  文字:  秋  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x08,0x40,0x1C,0x40,0xF0,0x40,0x10,0x40,0x11,0x44,0xFD,0x44,0x11,0x48,0x32,0x50,
	0x38,0x40,0x54,0xA0,0x54,0xA0,0x90,0x90,0x11,0x10,0x11,0x08,0x12,0x04,0x14,0x02,
	},
	{
	/*--  文字:  处  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x40,0x10,0x40,0x10,0x40,0x1E,0x40,0x12,0x60,0x22,0x50,0x22,0x48,0x52,0x44,
	0x94,0x44,0x14,0x40,0x08,0x40,0x08,0x40,0x14,0x40,0x23,0x00,0x40,0xFE,0x80,0x00,

	/*--  文字:  暑  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x02,0x00,0x1F,0xD0,0x02,0x20,
	0xFF,0xFE,0x03,0x00,0x0F,0xF0,0x38,0x10,0xCF,0xF0,0x08,0x10,0x0F,0xF0,0x08,0x10,
	},
	{
	/*--  文字:  白  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x02,0x00,0x04,0x00,0x3F,0xF8,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,
	0x3F,0xF8,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x3F,0xF8,0x00,0x00,

	/*--  文字:  露  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x41,0x02,0x9D,0x74,0x01,0x00,0x1D,0x70,0x00,0x40,
	0x7C,0xF8,0x45,0x48,0x7C,0x30,0x11,0xCE,0x5C,0x00,0x50,0xF8,0x5C,0x88,0xE0,0xF8,
	},
	{
	/*--  文字:  秋  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x08,0x00,0x1C,0x40,0xF0,0x40,0x10,0x40,0x11,0x44,0xFD,0x44,0x11,0x48,0x32,0x50,
	0x38,0x40,0x54,0xA0,0x54,0xA0,0x90,0x90,0x11,0x10,0x11,0x08,0x12,0x04,0x14,0x02,

	/*--  文字:  分  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x40,0x04,0x40,0x04,0x20,0x08,0x20,0x10,0x10,0x20,0x08,0x40,0x04,0x9F,0xE2,
	0x04,0x20,0x04,0x20,0x04,0x20,0x08,0x20,0x08,0x20,0x10,0x20,0x21,0x40,0x40,0x80,
	},
	{
	/*--  文字:  寒  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x02,0x00,0x01,0x00,0x7F,0xFE,0x44,0x42,0x9F,0xF4,0x04,0x40,0x3F,0xF8,0x04,0x40,
	0xFF,0xFE,0x08,0x20,0x13,0x10,0x20,0x88,0xC0,0x46,0x06,0x00,0x01,0x80,0x00,0x40,

	/*--  文字:  露  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x41,0x02,0x9D,0x74,0x01,0x00,0x1D,0x70,0x00,0x40,
	0x7C,0xF8,0x45,0x48,0x7C,0x30,0x11,0xCE,0x5C,0x00,0x50,0xF8,0x5C,0x88,0xE0,0xF8,
	},
	{
	/*--  文字:  霜  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x41,0x02,0x9D,0x74,0x01,0x00,0x1D,0x70,0x00,0x00,
	0x08,0xFC,0x7E,0x84,0x18,0xFC,0x2C,0x84,0x4A,0xFC,0x88,0x84,0x08,0xFC,0x08,0x84,

	/*--  文字:  降  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x00,0x7C,0x80,0x44,0xFC,0x49,0x08,0x4A,0x90,0x50,0x60,0x49,0x98,0x4E,0x26,
	0x44,0x20,0x45,0xFC,0x44,0x20,0x6A,0x20,0x53,0xFE,0x40,0x20,0x40,0x20,0x40,0x20,
	},
	{
	/*--  文字:  立  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x02,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x10,0x10,0x10,
	0x08,0x20,0x08,0x20,0x04,0x40,0x04,0x40,0x04,0x80,0x00,0x00,0xFF,0xFE,0x00,0x00,

	/*--  文字:  冬  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x04,0x00,0x04,0x00,0x0F,0xF0,0x10,0x10,0x28,0x20,0x44,0x40,0x03,0x80,0x0C,0x60,
	0x30,0x18,0xC0,0x06,0x07,0x00,0x00,0xC0,0x00,0x20,0x0E,0x00,0x01,0x80,0x00,0x40,
	},
	{
	/*--  文字:  小  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x10,0x11,0x08,0x11,0x04,
	0x21,0x04,0x21,0x02,0x41,0x02,0x81,0x02,0x01,0x00,0x05,0x00,0x03,0x00,0x00,0x00,

	/*--  文字:  雪  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x41,0x02,0x9D,0x74,0x01,0x00,0x1D,0x70,0x00,0x00,
	0x3F,0xF8,0x00,0x08,0x00,0x08,0x1F,0xF8,0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,
	},
	{
	/*--  文字:  大  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,
	0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06,

	/*--  文字:  雪  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x3F,0xF8,0x01,0x00,0x7F,0xFE,0x41,0x02,0x9D,0x74,0x01,0x00,0x1D,0x70,0x00,0x00,
	0x3F,0xF8,0x00,0x08,0x00,0x08,0x1F,0xF8,0x00,0x08,0x00,0x08,0x3F,0xF8,0x00,0x08,
	},
	{
	/*--  文字:  冬  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x04,0x00,0x04,0x00,0x0F,0xF0,0x10,0x10,0x28,0x20,0x44,0x40,0x03,0x80,0x0C,0x60,
	0x30,0x18,0xC0,0x06,0x07,0x00,0x00,0xC0,0x00,0x20,0x0E,0x00,0x01,0x80,0x00,0x40,

	/*--  文字:  至  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x00,0x00,0x7F,0xFC,0x02,0x00,0x04,0x00,0x08,0x20,0x10,0x10,0x3F,0xF8,0x00,0x08,
	0x01,0x00,0x01,0x00,0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00,
	},
	{
	/*--  文字:  小  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x10,0x11,0x08,0x11,0x04,
	0x21,0x04,0x21,0x02,0x41,0x02,0x81,0x02,0x01,0x00,0x05,0x00,0x03,0x00,0x00,0x00,

	/*--  文字:  寒  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x02,0x00,0x01,0x00,0x7F,0xFE,0x44,0x42,0x9F,0xF4,0x04,0x40,0x3F,0xF8,0x04,0x40,
	0xFF,0xFE,0x08,0x20,0x13,0x10,0x20,0x88,0xC0,0x46,0x06,0x00,0x01,0x80,0x00,0x40,
	},
	{
	/*--  文字:  大  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,
	0x02,0x80,0x02,0x80,0x04,0x40,0x04,0x40,0x08,0x20,0x10,0x10,0x20,0x08,0xC0,0x06,

	/*--  文字:  寒  --*/
	/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
	0x02,0x00,0x01,0x00,0x7F,0xFE,0x44,0x42,0x9F,0xF4,0x04,0x40,0x3F,0xF8,0x04,0x40,
	0xFF,0xFE,0x08,0x20,0x13,0x10,0x20,0x88,0xC0,0x46,0x06,0x00,0x01,0x80,0x00,0x40,
	},
	

};

uint8_t  Num16x32[][128] = {
	{0x7F,0x09,0x1E,0x00,0x41,0x09,0x12,0x00,0x7F,0x1F,0x92,0x00,0x41,0x09,0x12,0x00,
	0x7F,0x0F,0x1E,0x00,0x08,0x09,0x12,0x7E,0x48,0x0F,0x12,0x00,0x7F,0x09,0x1E,0x00,
	0x88,0x3F,0xD2,0x00,0x3E,0x00,0x12,0x00,0x08,0x09,0x16,0x00,0xFF,0x90,0xA2,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*星期1*/

	{0x7F,0x09,0x1E,0x00,0x41,0x09,0x12,0x00,0x7F,0x1F,0x92,0x00,0x41,0x09,0x12,0x00,
	0x7F,0x0F,0x1E,0x7C,0x08,0x09,0x12,0x00,0x48,0x0F,0x12,0x00,0x7F,0x09,0x1E,0x00,
	0x88,0x3F,0xD2,0xFE,0x3E,0x00,0x12,0x00,0x08,0x09,0x16,0x00,0xFF,0x90,0xA2,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*2*/

	{0x7F,0x09,0x1E,0x00,0x41,0x09,0x12,0x00,0x7F,0x1F,0x92,0x7C,0x41,0x09,0x12,0x00,
	0x7F,0x0F,0x1E,0x00,0x08,0x09,0x12,0x38,0x48,0x0F,0x12,0x00,0x7F,0x09,0x1E,0x00,
	0x88,0x3F,0xD2,0xFE,0x3E,0x00,0x12,0x00,0x08,0x09,0x16,0x00,0xFF,0x90,0xA2,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*3*/

	{0x7F,0x09,0x1E,0x00,0x41,0x09,0x12,0x00,0x7F,0x1F,0x92,0x00,0x41,0x09,0x12,0xFE,
	0x7F,0x0F,0x1E,0xAA,0x08,0x09,0x12,0xAA,0x48,0x0F,0x12,0xAA,0x7F,0x09,0x1E,0xC6,
	0x88,0x3F,0xD2,0x82,0x3E,0x00,0x12,0xFE,0x08,0x09,0x16,0x00,0xFF,0x90,0xA2,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},   /*4*/

	{0x7F,0x09,0x1E,0x00,0x41,0x09,0x12,0x7C,0x7F,0x1F,0x92,0x10,0x41,0x09,0x12,0x10,
	0x7F,0x0F,0x1E,0x10,0x08,0x09,0x12,0x7C,0x48,0x0F,0x12,0x14,0x7F,0x09,0x1E,0x14,
	0x88,0x3F,0xD2,0x14,0x3E,0x00,0x12,0x14,0x08,0x09,0x16,0x7E,0xFF,0x90,0xA2,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},   /*5*/

	{0x7F,0x09,0x1E,0x00,0x41,0x09,0x12,0x20,0x7F,0x1F,0x92,0x10,0x41,0x09,0x12,0x00,
	0x7F,0x0F,0x1E,0xFE,0x08,0x09,0x12,0x00,0x48,0x0F,0x12,0x28,0x7F,0x09,0x1E,0x28,
	0x88,0x3F,0xD2,0x44,0x3E,0x00,0x12,0x44,0x08,0x09,0x16,0x82,0xFF,0x90,0xA2,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},  /*6*/

	{0x7F,0x09,0x1E,0x7E,0x41,0x09,0x12,0x42,0x7F,0x1F,0x92,0x42,0x41,0x09,0x12,0x42,
	0x7F,0x0F,0x1E,0x42,0x08,0x09,0x12,0x7E,0x48,0x0F,0x12,0x42,0x7F,0x09,0x1E,0x42,
	0x88,0x3F,0xD2,0x42,0x3E,0x00,0x12,0x42,0x08,0x09,0x16,0x42,0xFF,0x90,0xA2,0x7E,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},    /*7*/
	
	
	{0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x20,0x3C,0x20,0x24,0x20,0x27,0xFC,0x24,0x20,0x3D,0x20,0x24,0xA0,0x24,0x10,0x3C,0x10,0x24,0x10,0x00,0x60,0x00,0x20,0x00,0x00},/*"时",7*/
	{0x00,0x00,0x00,0x00,0x0C,0x18,0x05,0xE8,0x10,0x08,0x10,0xC8,0x13,0x48,0x12,0x48,0x13,0xC8,0x12,0x48,0x13,0xC8,0x10,0x48,0x10,0x08,0x00,0x18,0x00,0x08,0x00,0x00},/*"间",8*/
	{0x00,0x00,0x00,0x00,0x18,0x30,0x0C,0xE0,0x00,0xA0,0x00,0xA0,0x09,0x18,0x79,0x20,0x08,0xD0,0x09,0x20,0x08,0xA0,0x0C,0x60,0x18,0x60,0x11,0x98,0x00,0x0E,0x00,0x00},/*"设",9*/
	{0x00,0x00,0x00,0x00,0x01,0xF8,0x0E,0x90,0x0A,0xF0,0x05,0x00,0x01,0xF0,0x06,0x00,0x07,0xE0,0x07,0xA0,0x05,0xA0,0x06,0x40,0x05,0x40,0x07,0xFE,0x38,0x00,0x00,0x00},/*"置",10*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x0F,0x30,0x08,0x20,0x04,0x20,0x05,0xA0,0x06,0x20,0x08,0x20,0x08,0x20,0x09,0xA0,0x06,0x60,0x00,0x20,0x00,0x00,0x00,0x00},/*"日",0*/
	{0x00,0x00,0x00,0x00,0x01,0x00,0x09,0x04,0x0F,0x3C,0x09,0x24,0x0F,0x24,0x09,0x3C,0x0F,0x24,0x09,0xBC,0x7E,0x24,0x09,0x44,0x11,0x44,0x20,0x8C,0x00,0x84,0x01,0x00},/*"期",1*/
	{0x00,0x00,0x00,0x00,0x18,0x30,0x0C,0xE0,0x00,0xA0,0x00,0xA0,0x09,0x18,0x79,0x20,0x08,0xD0,0x09,0x20,0x08,0xA0,0x0C,0x60,0x18,0x60,0x11,0x98,0x00,0x0E,0x00,0x00},/*"设",2*/
	{0x00,0x00,0x00,0x00,0x01,0xF8,0x0E,0x90,0x0A,0xF0,0x05,0x00,0x01,0xF0,0x06,0x00,0x07,0xE0,0x07,0xA0,0x05,0xA0,0x06,0x40,0x05,0x40,0x07,0xFE,0x38,0x00,0x00,0x00},/*"置",3*/

	{0x00,0x00,0x00,0x00,0x08,0x18,0x04,0xE8,0x11,0x08,0x11,0x28,0x1F,0xC8,0x11,0x68,0x17,0xA8,0x15,0x28,0x15,0x68,0x11,0x08,0x21,0x04,0x00,0x1C,0x00,0x08,0x00,0x00},/*"闹",0*/
	{0x00,0x00,0x08,0x00,0x0C,0x20,0x08,0x20,0x0A,0x20,0x14,0x3E,0x13,0xE4,0x2C,0xA4,0x46,0xB8,0x1D,0x60,0x08,0x20,0x0A,0x20,0x0C,0x20,0x08,0x20,0x00,0x20,0x00,0x20},/*"钟",1*/
	{0x00,0x00,0x00,0x00,0x18,0x30,0x0C,0xE0,0x00,0xA0,0x00,0xA0,0x09,0x18,0x79,0x20,0x08,0xD0,0x09,0x20,0x08,0xA0,0x0C,0x60,0x18,0x60,0x11,0x98,0x00,0x0E,0x00,0x00},/*"设",2*/
	{0x00,0x00,0x00,0x00,0x01,0xF8,0x0E,0x90,0x0A,0xF0,0x05,0x00,0x01,0xF0,0x06,0x00,0x07,0xE0,0x07,0xA0,0x05,0xA0,0x06,0x40,0x05,0x40,0x07,0xFE,0x38,0x00,0x00,0x00},/*"置",3*/
						
	{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xF0,0x06,0x40,0x02,0x40,0x02,0x4C,0x7F,0xF0,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x40,0x08,0x40,0x10,0x40,0x00,0x00,0x00,0x00},/*"开",0*/
	{0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0x30,0x07,0xD0,0x04,0x20,0x04,0x60,0x07,0x80,0x04,0x00,0x08,0x10,0x0B,0xF8,0x12,0x10,0x12,0x10,0x23,0xF0,0x00,0x00,0x00,0x00},/*"启",1*/
	{0x00,0x00,0x00,0x40,0x0C,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x18,0x3C,0x2B,0xE0,0x08,0x20,0x08,0x20,0x0C,0x20,0x18,0x20,0x10,0x20,0x00,0x20,0x00,0x20,0x00,0x00},/*"计",2*/
	{0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x20,0x3C,0x20,0x24,0x20,0x27,0xFC,0x24,0x20,0x3D,0x20,0x24,0xA0,0x24,0x10,0x3C,0x10,0x24,0x10,0x00,0x60,0x00,0x20,0x00,0x00},/*"时",3*/



	{		/*--  调入了一幅图像：这是您新建的图像 闹钟开标志  23 --*/
			/*--  宽度x高度=32x16  --*/
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x88,0x00,0x00,0x07,0x98,0x00,
			0x00,0x0D,0xB0,0x00,0x00,0x19,0xA0,0x00,0x00,0x71,0x80,0x00,0x00,0x61,0xBC,0x00,
			0x00,0x61,0xBC,0x00,0x00,0x71,0x80,0x00,0x00,0x19,0xA0,0x00,0x00,0x0D,0xB0,0x00,
			0x00,0x07,0x98,0x00,0x00,0x03,0x88,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	},
	
	{		/*--  调入了一幅图像：这是您新建的图像 闹钟关标志  24  --*/
		/*--  宽度x高度=32x16  --*/
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x07,0x80,0x00,
		0x00,0x0D,0xAE,0x00,0x00,0x19,0x91,0x00,0x00,0x71,0xA8,0x80,0x00,0x61,0xA4,0x80,
		0x00,0x61,0xA2,0x80,0x00,0x71,0x91,0x00,0x00,0x19,0x8E,0x80,0x00,0x0D,0x80,0x00,
		0x00,0x07,0x80,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	},
	
	{0x00,0x00,0x00,0x00,0x08,0x40,0x08,0x20,0x08,0x08,0x0F,0x7C,0x39,0x80,0x0C,0x40,0x08,0x5E,0x1F,0xB0,0x28,0xA0,0x48,0x60,0x08,0x58,0x19,0x8C,0x00,0x00,0x00,0x00},/*"按",25*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x08,0x00,0x08,0x00,0x7F,0x7E,0x08,0x00,0x08,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/* +- ,26*/
		
	{0x00,0x00,0x00,0x40,0x00,0x40,0x11,0x40,0x09,0x50,0x01,0xE0,0x02,0x48,0x1B,0xF0,0x14,0xC0,0x11,0x40,0x11,0x44,0x16,0x3C,0x7C,0x00,0x03,0xFE,0x00,0x18,0x00,0x00},/*"选",27*/
	{0x00,0x00,0x08,0x00,0x08,0x38,0x08,0xD0,0x08,0xA0,0x0C,0x40,0x38,0xB0,0x0D,0x6C,0x0A,0x60,0x38,0xE0,0x48,0x3C,0x0B,0xE0,0x18,0x20,0x08,0x20,0x00,0x40,0x00,0x00},/*"择",28*/
		
	{0x00,0x00,0x00,0x00,0x00,0x20,0x02,0x5C,0x1C,0xA8,0x09,0x10,0x08,0x6C,0x17,0xA4,0x1C,0xB4,0x35,0x64,0x59,0x7C,0x01,0x24,0x01,0x24,0x02,0x04,0x00,0x0C,0x00,0x00},/*"确",29*/
	{0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x11,0xF8,0x1E,0x10,0x10,0x60,0x07,0x80,0x01,0x00,0x0D,0xE0,0x09,0x00,0x0F,0x00,0x11,0x00,0x20,0xF0,0x00,0x3C,0x00,0x00},/*"定",30*/

	
	{0x00,0x00,0x00,0x00,0x00,0x70,0x19,0xB0,0x09,0x60,0x01,0xA0,0x01,0x68,0x79,0x90,0x11,0xE0,0x11,0x18,0x09,0x6C,0x09,0x80,0x76,0x00,0x01,0xFE,0x00,0x00,0x00,0x00},/*"退",31*/
	{0x00,0x00,0x01,0x00,0x01,0x80,0x01,0x00,0x01,0x00,0x19,0x08,0x11,0x08,0x11,0xF0,0x1F,0x10,0x01,0x00,0x11,0x08,0x11,0x08,0x11,0xF8,0x1E,0x10,0x00,0x00,0x00,0x00},/*"出",32*/


	{0x00,0x00,0x00,0x00,0x03,0x00,0x02,0x60,0x05,0x80,0x08,0x80,0x07,0xE0,0x04,0x80,0x05,0xFC,0x3A,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,0x00,0x00},/*"年",33*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xE0,0x02,0x20,0x02,0x20,0x03,0x20,0x02,0x20,0x05,0xA0,0x06,0x20,0x04,0x20,0x08,0x20,0x08,0xE0,0x10,0x60,0x00,0x00,0x00,0x00},/*"月",34*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x07,0xA0,0x04,0x20,0x04,0x20,0x07,0xA0,0x04,0x20,0x04,0x20,0x04,0x20,0x07,0xE0,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00},/*"日",35*/
	{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x1C,0x20,0x14,0x20,0x17,0xF8,0x1C,0x20,0x15,0xA0,0x14,0xA0,0x14,0x20,0x1C,0x20,0x00,0x60,0x00,0x20,0x00,0x00,0x00,0x00},/*"时",36*/
	{0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x80,0x06,0x40,0x04,0x20,0x08,0x30,0x10,0x5C,0x2F,0xE0,0x02,0x40,0x04,0x40,0x04,0x40,0x09,0xC0,0x01,0x80,0x00,0x00,0x00,0x00},/*"分",37*/
	{0x00,0x00,0x00,0x00,0x00,0x40,0x02,0x20,0x0C,0x20,0x04,0x3C,0x1C,0xC0,0x04,0x58,0x0E,0x10,0x14,0x20,0x24,0x20,0x04,0x40,0x04,0x80,0x01,0x00,0x00,0x00,0x00,0x00},/*"秒",38*/
		
	
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x13,0xFF,0x83,0x83,0xFF,0x90,0x00,0x00,0x23,0xFF,0x85,0x43,0xFF,0x88,0x00,  /* 39 */
	0x00,0x43,0xEF,0x89,0x23,0xFF,0x84,0x00,0x00,0x83,0xEF,0x91,0x13,0xFF,0x82,0x00,0x01,0x03,0xEF,0x81,0x03,0xFF,0x81,0x00,0x02,0x03,0x01,0x81,0x03,0x01,0x80,0x80,   /* <+♂->*/
	0x01,0x03,0xEF,0x81,0x03,0xFF,0x81,0x00,0x00,0x83,0xEF,0x81,0x03,0xFF,0x82,0x00,0x00,0x43,0xEF,0x83,0x83,0xFF,0x84,0x00,0x00,0x23,0xFF,0x84,0x43,0xFF,0x88,0x00,
	0x00,0x13,0xFF,0x84,0x43,0xFF,0x90,0x00,0x00,0x00,0x00,0x04,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	},
		
	{
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x08,0x00, /* 40 */
	0x00,0x40,0x10,0x00,0x00,0x00,0x04,0x00,0x00,0x80,0x10,0x00,0x00,0x00,0x02,0x00,0x01,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x02,0x00,0xFE,0x00,0x00,0xFE,0x00,0x80,   /* <+  ->*/
	0x01,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x00,0x80,0x10,0x00,0x00,0x00,0x02,0x00,0x00,0x40,0x10,0x00,0x00,0x00,0x04,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x08,0x00,
	0x00,0x10,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	},
	
	
	{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xF0,0x06,0x40,0x02,0x40,0x02,0x4C,0x7F,0xF0,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x40,0x08,0x40,0x10,0x40,0x00,0x00,0x00,0x00},/*"开",41*/
	
	{0x00,0x00,0x00,0x20,0x00,0x20,0x06,0x40,0x02,0x40,0x00,0xE0,0x07,0x00,0x01,0x00,0x03,0xFC,0x1D,0x00,0x02,0x80,0x02,0x40,0x04,0x20,0x08,0x38,0x10,0x1E,0x00,0x00},/*"关",42*/
		

	{0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x00,0x00,0x0F,0xE0,0x0E,0xE0,0x0E,0xE0,0x08,0x20,0x0E,0xE0,0x0E,0xE0,0x0F,0xE0,0x00,0x00,0x10,0x38,0x20,0x44,0x7F,0xC4,/*∧ 43 48*16*/
	0x20,0x44,0x10,0x38,0x00,0x00,0x0F,0xE0,0x0F,0xE0,0x0F,0xE0,0x08,0x20,0x0F,0xE0,0x0F,0xE0,0x0F,0xE0,0x00,0x00,0x08,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x00,0x00 /*+*/
																																																																																	/*♂*/
	},                                                                                                                                                               /*-*/
																																																																																	 /*∨*/
	
	

	
	{0x01,0x00,0x02,0x80,0x04,0x40,0x08,0x20,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x07,0xC0,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, /* 44 */
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x20,0x04,0x40,0x02,0x80,0x01,0x00,0x00,0x00
	},
	{0x00,0x00,0x00,0x00,0x01,0x00,0x03,0x80,0x05,0x40,0x09,0x20,0x11,0x10,0x01,0x00,0x01,0x00,0x01,0x00,0x03,0x80,0x04,0x40,0x04,0x40,0x04,0x40,0x03,0x80,0x00,0x00},/*45*/
	{0x00,0x00,0x01,0xC0,0x02,0x20,0x02,0x20,0x02,0x20,0x01,0xC0,0x00,0x80,0x00,0x80,0x00,0x80,0x08,0x88,0x04,0x90,0x02,0xA0,0x01,0xC0,0x00,0x80,0x00,0x00,0x00,0x00},/*46*/
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*47*/
		
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x07,0x00,0x00,0x80,0x00,0x80,0x0C,0xB0,0x04,0xC0,0x08,0x80,0x08,0x80,0x08,0x80,0x0F,0xFE,0x30,0x00,0x00,0x00,0x00,0x00},/*"正",48*/	
	{0x00,0x00,0x00,0x00,0x08,0x04,0x08,0xC4,0x0F,0x04,0x11,0x14,0x22,0xD4,0x37,0x54,0x51,0x14,0x11,0xD4,0x13,0x04,0x11,0xC4,0x16,0x04,0x10,0x0C,0x00,0x04,0x00,0x00},/*"倒",49*/
	{0x00,0x00,0x00,0x40,0x0C,0x20,0x00,0x20,0x00,0x20,0x00,0x20,0x18,0x3C,0x2B,0xE0,0x08,0x20,0x08,0x20,0x0C,0x20,0x18,0x20,0x10,0x20,0x00,0x20,0x00,0x20,0x00,0x00},/*"计",50*/
	{0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x20,0x1C,0x20,0x14,0x20,0x17,0xF8,0x1C,0x20,0x15,0xA0,0x14,0xA0,0x14,0x20,0x1C,0x20,0x00,0x60,0x00,0x20,0x00,0x00,0x00,0x00},/*"时",51*/

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x38,0x04,0x44,0x02,0x47,0xFF,0x44,0x02,0x38,0x04,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},/*o-> 52*/
		
	{		/*--  调入了一幅图像：这是您新建的图像  --*/
		/*--  宽度x高度=64x16  --*/
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
		0x3E,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x80,0x00,0x06,0xB0,0x00,
		0x08,0x00,0x00,0x80,0x00,0x02,0xA0,0x00,0x08,0x00,0x00,0x80,0x00,0x02,0xA0,0x00,
		0x08,0x00,0x00,0x80,0x00,0x02,0xA0,0x00,0x08,0x03,0x10,0x81,0x91,0x32,0xA6,0x38,
		0x09,0x14,0x90,0x82,0x51,0x4B,0xE9,0x44,0x09,0x14,0x38,0x82,0x51,0x49,0x49,0x44,
		0x09,0x13,0x10,0x82,0x4A,0x71,0x4E,0x44,0x09,0x10,0x90,0x82,0x4A,0x41,0x48,0x44,
		0x49,0x14,0x90,0x82,0x4E,0x49,0x49,0x44,0x30,0xE3,0x0C,0xF9,0x84,0x31,0x46,0x44,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00                                                                                /* 53 */
	},
	
	
	{0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xF0,0x06,0x40,0x02,0x40,0x02,0x4C,0x7F,0xF0,0x04,0x40,0x04,0x40,0x04,0x40,0x08,0x40,0x08,0x40,0x10,0x40,0x00,0x00,0x00,0x00},/*"开",54*/
	{0x00,0x00,0x00,0x00,0x08,0x20,0x04,0x20,0x08,0x40,0x08,0x48,0x0A,0x8C,0x0E,0xF4,0x7A,0x00,0x14,0x00,0x0C,0xFC,0x04,0x88,0x0A,0x88,0x30,0x70,0x00,0x00,0x00,0x00},/*"始",55*/
	
	{0x00,0x00,0x00,0x40,0x0C,0x40,0x08,0x70,0x08,0xA0,0x10,0xD0,0x30,0xF0,0x50,0x1C,0x13,0xE4,0x10,0x38,0x10,0xC0,0x10,0x40,0x10,0x40,0x00,0x40,0x00,0xC0,0x00,0x00},/*"停",56*/
	{0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x0C,0xF8,0x04,0x80,0x04,0x80,0x04,0x80,0x04,0x80,0x07,0xFE,0x38,0x00,0x00,0x00,0x00,0x00},/*"止",57*/
	{0x00,0x00,0x02,0x00,0x02,0x00,0x05,0xE0,0x0A,0x60,0x15,0xA0,0x05,0xA0,0x06,0x20,0x03,0xC0,0x02,0x00,0x07,0xE0,0x09,0x40,0x10,0x80,0x01,0x60,0x0E,0x1E,0x00,0x00},/*"复",58*/
	{0x00,0x00,0x00,0x00,0x04,0x00,0x04,0xC0,0x08,0x00,0x08,0x00,0x10,0xF0,0x10,0x00,0x28,0x10,0x49,0x20,0x11,0x20,0x10,0x40,0x10,0xFE,0x13,0x00,0x00,0x00,0x00,0x00},/*"位",59*/
		
	
	{0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x11,0xF8,0x1E,0x10,0x10,0x60,0x07,0x80,0x01,0x00,0x0D,0xE0,0x09,0x00,0x0F,0x00,0x11,0x00,0x20,0xF0,0x00,0x3C,0x00,0x00},/*"定",60*/
	{0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x20,0x3C,0x20,0x24,0x20,0x27,0xFC,0x24,0x20,0x3D,0x20,0x24,0xA0,0x24,0x10,0x3C,0x10,0x24,0x10,0x00,0x60,0x00,0x20,0x00,0x00},/*"时",61*/
};
#endif



