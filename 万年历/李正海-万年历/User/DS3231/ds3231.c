#include "ds3231.h"
#include "iic.h"
/*-----------------------------------------------------------------------
IIC_writeOneByte           		  : IICд���ݵ�IIC����
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
void IIC_WriteOneByte(uint8_t Addr,uint8_t Data)
{
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(IIC_WriteAddress);                                          // ����������ַ+д��0��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr);                                                      // д�����ݵ�����
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Data);                                                      // д�����ݵ�����
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_Stop();                                                               // ����ֹͣ�ź�
}

/*-----------------------------------------------------------------------
IIC_ReadOneByte           		  : �������ж�������
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
uint8_t IIC_ReadOneByte(uint8_t Addr)
{
	uint8_t IIC_Value;
	
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(IIC_WriteAddress);                                          // ����������ַ+д��0��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�

	IIC_WriteByte(Addr);                                                      // ���ͼĴ�����ַ
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(IIC_ReadAddress);                                           // ����������ַ+����1��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	
	IIC_Value = IIC_ReadByte();                                               // ��������
	IIC_NACK();                                                               // ��Ӧ���ź�
	IIC_Stop();                                                               // ����ֹͣ�ź�
	return IIC_Value;
}

/*-----------------------------------------------------------------------
IIC_WriteMultiByte            	: д������ݵ�����
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
void IIC_WriteMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num)
{
	uint8_t i;                                                          
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(IIC_WriteAddress);                                          // ����������ַ+д��0��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr);                                                      // д�����ݵ�����
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	
	for(i=0;i<num;i++)                                                        // ѭ��д��������
	{
		IIC_WriteByte(Arry[i]);                                                 // д�����ݵ�����
		while(IIC_WaitACK());                                                   // �ȴ��ӻ�����Ӧ���ź�	
	}
	IIC_Stop();                                                               // ����ֹͣ�ź�

}
/*-----------------------------------------------------------------------
IIC_ReadMultiByte           		: �������ж����������
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
void IIC_ReadMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num)
{
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(IIC_WriteAddress);                                          // ����������ַ+д��0��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	IIC_WriteByte(Addr);                                                      // ���ͼĴ�����ַ
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	
	IIC_Start();                                                              // IIC��ʼ�ź�
	IIC_WriteByte(IIC_ReadAddress);                                           // ����������ַ+����1��
	while(IIC_WaitACK());                                                     // �ȴ��ӻ�����Ӧ���ź�
	while(num)
	{
		if(num == 1)
		{
			*Arry = IIC_ReadByte();                                               // ��������
			IIC_NACK();                                                           // ��Ӧ���ź�
		}
		else
		{
			*Arry = IIC_ReadByte();                                               // ��������
			IIC_ACK();                                                            // ��Ӧ���ź�		 
		}
		num --;                                                                 // ���ݳ���-1
		Arry ++;                                                                // �����ַ+1
	}
	IIC_Stop();                                                               // ����ֹͣ�ź�
}

/*-----------------------------------------------------------------------
IIC_GetTemp                 		: ��ȡ�¶�
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
void IIC_GetTemp(uint8_t *Arry)
{
	IIC_WriteOneByte(0x0E,0x27);                                              // ����ƼĴ�����д�����ݣ������¶ȴ��䣬ʹ������1������2�������ж��ź�
	
	*Arry = IIC_ReadOneByte(0x11);                                            // ��ȡ�¶ȸ߰�λ
	*(Arry+1) = IIC_ReadOneByte(0x12);                                        // ��ȡ�¶ȵͰ�λ
}

