#include "at24c32.h"
#include "iic.h"
#include "usart.h"

/*-----------------------------------------------------------------------
AT24C32_WriteOneByte            : IICд���ݵ�AT24C32����
	
�������                   			��uint16_t Addr,uint8_t Data  (AT24C32 ��12λ��ַ)
                                  

-----------------------------------------------------------------------*/
void AT24C32_WriteOneByte(uint16_t Addr,uint8_t Data)
{
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(AT24C32_WriteAddr);                                         // ����������ַ+д��0��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr>>8);                                                   // д��������ַ�߰�λ
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr&0xFF);                                                 // д��������ַ�Ͱ�λ
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Data);                                                      // д�����ݵ�����
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_Stop();                                                               // ����ֹͣ�ź�
}

/*-----------------------------------------------------------------------
AT24C32_ReadOneByte             : ��AT24C32�ж�ȡ����
	
�������                   			��uint16_t Addr (AT24C32 ��12λ��ַ)
                                  

-----------------------------------------------------------------------*/
uint8_t AT24C32_ReadOneByte(uint16_t Addr)
{
	uint8_t AT24C32_Value;                                                    // ��Ŷ���������ֵ

	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(AT24C32_WriteAddr);                                         // ����������ַ+д��0��
	IIC_WaitACK();                                                            // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr>>8);                                                   // ���ͼĴ�����ַ
	IIC_WaitACK();	                                                          // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr&0xFF);                                                 // ���ͼĴ�����ַ
	IIC_WaitACK();                                                            // �ȴ��ӻ�����Ӧ���ź�
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(AT24C32_ReadAddr);                                          // ����������ַ+����1��
	IIC_WaitACK();                                                            // �ȴ��ӻ�����Ӧ���ź�
	AT24C32_Value = IIC_ReadByte();                                           // ��������
	IIC_NACK();                                                               // ��Ӧ���ź�
	IIC_Stop();                                                               // ����ֹͣ�ź�
	
	return AT24C32_Value;                                                     // ���ض�����ֵ
}

/*-----------------------------------------------------------------------
AT24C32_PageWrite               : ҳд������
	
�������                   			��uint16_t Addr,uint8_t *Page_Arry,uint8_t num (n���ܴ���32��������ͷ�����ֽ�)
                                  

-----------------------------------------------------------------------*/
void AT24C32_PageWrite(uint16_t Addr,uint8_t *Page_Arry,uint8_t num)
{
	uint8_t i;
	if(num>32) num = 32;
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(AT24C32_WriteAddr);                                         // ����������ַ+д��0��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr>>8);                                                   // д��������ַ�߰�λ
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr&0xFF);                                                 // д��������ַ�Ͱ�λ
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	for(i=0;i<num;i++)                                                        // ѭ��д��������
	{
		IIC_WriteByte(Page_Arry[i]);                                            // д�����ݵ�����
		while(IIC_WaitACK());                                                   // �ȴ��ӻ�����Ӧ���ź�	
	}
	IIC_Stop();                                                               // ����ֹͣ�ź�
}

/*-----------------------------------------------------------------------
AT24C32_PageRead                : ҳ��ȡ����
	
�������                   			��uint16_t Addr,uint8_t *Page_Arry,uint8_t num (n���ܴ���32��������ͷ�����ֽ�)
                                  

-----------------------------------------------------------------------*/
void AT24C32_PageRead(uint16_t Addr,uint8_t *Page_Arry,uint8_t num)
{
	if(num>32) num = 32;
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(AT24C32_WriteAddr);                                         // ����������ַ+д��0��
	IIC_WaitACK();                                                            // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr>>8);                                                   // ���ͼĴ�����ַ
	IIC_WaitACK();	                                                          // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr&0xFF);                                                 // ���ͼĴ�����ַ
	IIC_WaitACK();                                                            // �ȴ��ӻ�����Ӧ���ź�
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(AT24C32_ReadAddr);                                          // ����������ַ+����1��
	IIC_WaitACK(); 
	while(num)
	{
		if(num == 1)
		{
			*Page_Arry = IIC_ReadByte();                                          // ��������
			IIC_NACK();                                                           // ��Ӧ���ź�
		}
		else
		{
			*Page_Arry = IIC_ReadByte();                                          // ��������
			IIC_ACK();                                                            // ��Ӧ���ź�		 
		}
		num --;                                                                 // ���ݳ���-1
		Page_Arry ++;                                                           // �����ַ+1
	}
	IIC_Stop();                                                               // ����ֹͣ�ź�
}




