#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "GPIO_Bit_Config.h"

#define SDA_IN()   {GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= (uint32_t) 8<<28 ;}   // 将端口设置为上拉输入 PB7
#define SDA_OUT()  {GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= (uint32_t) 3<<28 ;}   // 将端口设置为推挽输出 PB7

#define IIC_SCL     PBout(6)                                                      // SCL端口
#define Read_SDA    PBin(7)                                                       // 读数据
#define Write_SDA   PBout(7)                                                      // 写数据

#define IIC_CLOCK   RCC_APB2Periph_GPIOB                                          // GPIOB时钟
#define IIC_Pin     GPIO_Pin_6|GPIO_Pin_7                                         // IIC的引脚
#define IIC_Port    GPIOB                                                         // GPIOB

void IIC_GPIO_Config(void);                                                       // 模拟IIC引脚配置
void IIC_Start(void);                                                             // IIC起始信号
void IIC_Stop(void);																															// IIC停止信号
uint8_t IIC_WaitACK(void);                                                        // 等待器件产生应答或非应答信号
void IIC_WriteByte(uint8_t IIC_Data);                                             // IIC写八位数据
uint8_t IIC_ReadByte(void);                                                       // IIC读取八位数据
void IIC_ACK(void);                                                               // IIC产生应答信号
void IIC_NACK(void);                                                              // IIC产生非应答信号
//void IIC_WriteOneByte(uint8_t Addr,uint8_t Data);                                 // IIC写数据到IIC器件
//uint8_t IIC_ReadOneByte(uint8_t Addr);                                            // 从器件中读出数据

#endif


