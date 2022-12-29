#include "iic.h"
#include "usart.h"
/*-----------------------------------------------------------------------
IIC_Delay  			 							  : ��Լ��ʱ4.9us
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
static void IIC_Delay(void)
{	
	uint16_t time = 1;
  uint16_t i = 0;
	while(time--)
	{
		i=34;
		while(i--);
	}
}
/*-----------------------------------------------------------------------
IIC_GPIO_Config  			 				  : ģ��IIC��������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void IIC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                                       // �����ṹ��
	RCC_APB2PeriphClockCmd(IIC_CLOCK, ENABLE);                                 // ����GPIOAʱ��
  GPIO_InitStructure.GPIO_Pin = IIC_Pin;                                     // �������ź�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                           // ����GPIO��ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                          // ����IO�ڵ��ٶ�
  GPIO_Init(IIC_Port, &GPIO_InitStructure);                                  // ��ʼ���ṹ��
}

/*-----------------------------------------------------------------------
IIC_Start       			 				  : IIC��ʼ�ź�
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void IIC_Start(void)
{
	SDA_OUT();                                                                 // SDA����Ϊ���
	
	IIC_SCL = 1;                                                               // SCL�ø� �������߿��е�ʱ��SDA��SCA���Ǹߵ�ƽ�ź�
	Write_SDA = 1;                                                             // SDA�����
	IIC_Delay();                                                               // ��ʱ���4.9us
	Write_SDA = 0;                                                             // SDA�����
	IIC_Delay();                                                               // ��ʱ���4.9us
	IIC_SCL = 0;                                                               // SCL�õͣ�ǯסIIC���ߣ�׼����������
}

/*-----------------------------------------------------------------------
IIC_Stop        			 				  : IICֹͣ�ź�
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void IIC_Stop(void)
{
	SDA_OUT();                                                                 // SDA����Ϊ���
	IIC_SCL = 0;                                                               // SCL�ø� �������߿��е�ʱ��SDA��SCA���Ǹߵ�ƽ�ź�	
	Write_SDA = 0;                                                             // SDA�����
	IIC_Delay();                                                               // ��ʱ���4.9us
	IIC_SCL = 1;                                                               // SCL�ø� �������߿��е�ʱ��SDA��SCA���Ǹߵ�ƽ�ź�
	Write_SDA = 1;                                                             // SDA�����
	IIC_Delay();                                                               // ��ʱ���4.9us
}

/*-----------------------------------------------------------------------
IIC_WaitACK        			 				: IIC�ȴ��Է�����Ӧ���Ƿ�Ӧ���ź�
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
uint8_t IIC_WaitACK(void)
{
	uint8_t Re_Val;                                                            // ����״ֵ̬ 1����ʾ��Ӧ�� 0����ʾӦ��
	SDA_OUT();                                                                 // SDA����Ϊ���
	Write_SDA = 1;                                                             // SDA����ߣ��ͷ����߿���Ȩ
	IIC_Delay();                                                               // ��ʱ���4.9us
	SDA_IN();                                                                  // SDA ����Ϊ����ģʽ	
	IIC_SCL = 1;                                                               // SCL�ø� 

	if(Read_SDA == 1)
	{
		Re_Val = 1;
	}
	else
	{
		Re_Val = 0;
	}	
	IIC_SCL = 0;                                                               // SCL�ø� 
	IIC_Delay();                                                               // ��ʱ���4.9us
	
	return Re_Val;
}

/*-----------------------------------------------------------------------
IIC_WriteByte       			 			: IICд��λ����
	
�������                   			��IIC_Data
                                  

-----------------------------------------------------------------------*/
void IIC_WriteByte(uint8_t IIC_Data)
{
	uint8_t i;
	SDA_OUT();                                                                 // SDA����Ϊ���
	for(i=0;i<8;i++)
	{
		if(IIC_Data & 0x80)                                                      // �ж����λ
		{
			Write_SDA = 1;                                                     
		}
		else
		{
			Write_SDA = 0;                                                     			
		}
	 IIC_Delay();                                                              // ��ʱ���4.9us
	 IIC_SCL = 1;                                                              // SCL�ø� 
	 IIC_Delay();                                                              // ��ʱ���4.9us
	 IIC_SCL = 0;                                                              // SCL�õ� 
	 if(i == 7)
	 {
		 Write_SDA = 1;                                                          // SDA�ø�,�ͷ�����
	 }
	 IIC_Data <<= 1;
	 IIC_Delay();                                                              // ��ʱ���4.9us
	}
}

/*-----------------------------------------------------------------------
IIC_ReadByte       		  	 			: IIC��ȡ��λ����
	
�������                   			��IIC_Data
                                  

-----------------------------------------------------------------------*/
uint8_t IIC_ReadByte(void)
{
	uint8_t i;
	uint8_t Value = 0;
	
	SDA_IN();                                                                  // IIC����ģʽ
	for(i=0;i<8;i++)
	{
		Value <<= 1;
		IIC_SCL = 1;                                                             // SCL�ø� 
	  IIC_Delay();                                                             // ��ʱ���4.9us
		if(Read_SDA == 1)
		{
			Value ++;
		}
		IIC_SCL = 0;                                                             // SCL�õ�
	  IIC_Delay();                                                             // ��ʱ���4.9us	
	}
	return Value;
}

/*-----------------------------------------------------------------------
IIC_ACK           		  	 			: IIC����Ӧ���ź�
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
void IIC_ACK(void)
{
	SDA_OUT();                                                                 // SDA����Ϊ���
	Write_SDA = 0;                                                     			
	IIC_Delay();                                                               // ��ʱ���4.9us	
	IIC_SCL = 1;                                                               // SCL�ø� 
	IIC_Delay();                                                               // ��ʱ���4.9us	
	IIC_SCL = 0;                                                               // SCL�õ�
	IIC_Delay();                                                               // ��ʱ���4.9us	
	Write_SDA = 1;                                                     				 // �ͷ�SDA���߿���Ȩ
}

/*-----------------------------------------------------------------------
IIC_NACK           		  	 			: IIC������Ӧ���ź�
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
void IIC_NACK(void)
{
	SDA_OUT();                                                                 // SDA����Ϊ���
	Write_SDA = 1;                                                     				 // �ͷ�SDA���߿���Ȩ
	IIC_Delay();                                                               // ��ʱ���4.9us	
	IIC_SCL = 1;                                                               // SCL�ø� 
	IIC_Delay();                                                               // ��ʱ���4.9us	
	IIC_SCL = 0;                                                               // SCL�õ�
	IIC_Delay();                                                               // ��ʱ���4.9us	
}





