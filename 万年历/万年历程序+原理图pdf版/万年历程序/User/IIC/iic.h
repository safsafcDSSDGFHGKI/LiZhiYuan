#ifndef __IIC_H
#define __IIC_H

#include "stm32f10x.h"
#include "GPIO_Bit_Config.h"

#define SDA_IN()   {GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= (uint32_t) 8<<28 ;}   // ���˿�����Ϊ�������� PB7
#define SDA_OUT()  {GPIOB->CRL &= 0x0fffffff; GPIOB->CRL |= (uint32_t) 3<<28 ;}   // ���˿�����Ϊ������� PB7

#define IIC_SCL     PBout(6)                                                      // SCL�˿�
#define Read_SDA    PBin(7)                                                       // ������
#define Write_SDA   PBout(7)                                                      // д����

#define IIC_CLOCK   RCC_APB2Periph_GPIOB                                          // GPIOBʱ��
#define IIC_Pin     GPIO_Pin_6|GPIO_Pin_7                                         // IIC������
#define IIC_Port    GPIOB                                                         // GPIOB

void IIC_GPIO_Config(void);                                                       // ģ��IIC��������
void IIC_Start(void);                                                             // IIC��ʼ�ź�
void IIC_Stop(void);																															// IICֹͣ�ź�
uint8_t IIC_WaitACK(void);                                                        // �ȴ���������Ӧ����Ӧ���ź�
void IIC_WriteByte(uint8_t IIC_Data);                                             // IICд��λ����
uint8_t IIC_ReadByte(void);                                                       // IIC��ȡ��λ����
void IIC_ACK(void);                                                               // IIC����Ӧ���ź�
void IIC_NACK(void);                                                              // IIC������Ӧ���ź�
//void IIC_WriteOneByte(uint8_t Addr,uint8_t Data);                                 // IICд���ݵ�IIC����
//uint8_t IIC_ReadOneByte(uint8_t Addr);                                            // �������ж�������

#endif


