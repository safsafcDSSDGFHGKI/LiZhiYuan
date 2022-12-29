#include "iic.h"
#include "usart.h"
/*-----------------------------------------------------------------------
IIC_Delay  			 							  : 大约延时4.9us
	
输入参数                   			：无
                                  

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
IIC_GPIO_Config  			 				  : 模拟IIC引脚配置
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void IIC_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                                       // 声明结构体
	RCC_APB2PeriphClockCmd(IIC_CLOCK, ENABLE);                                 // 开启GPIOA时钟
  GPIO_InitStructure.GPIO_Pin = IIC_Pin;                                     // 设置引脚号
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                           // 设置GPIO的模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                          // 设置IO口的速度
  GPIO_Init(IIC_Port, &GPIO_InitStructure);                                  // 初始化结构体
}

/*-----------------------------------------------------------------------
IIC_Start       			 				  : IIC起始信号
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void IIC_Start(void)
{
	SDA_OUT();                                                                 // SDA设置为输出
	
	IIC_SCL = 1;                                                               // SCL置高 ，当总线空闲的时候SDA和SCA都是高电平信号
	Write_SDA = 1;                                                             // SDA输出高
	IIC_Delay();                                                               // 延时大概4.9us
	Write_SDA = 0;                                                             // SDA输出低
	IIC_Delay();                                                               // 延时大概4.9us
	IIC_SCL = 0;                                                               // SCL置低，钳住IIC总线，准备发送数据
}

/*-----------------------------------------------------------------------
IIC_Stop        			 				  : IIC停止信号
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void IIC_Stop(void)
{
	SDA_OUT();                                                                 // SDA设置为输出
	IIC_SCL = 0;                                                               // SCL置高 ，当总线空闲的时候SDA和SCA都是高电平信号	
	Write_SDA = 0;                                                             // SDA输出低
	IIC_Delay();                                                               // 延时大概4.9us
	IIC_SCL = 1;                                                               // SCL置高 ，当总线空闲的时候SDA和SCA都是高电平信号
	Write_SDA = 1;                                                             // SDA输出高
	IIC_Delay();                                                               // 延时大概4.9us
}

/*-----------------------------------------------------------------------
IIC_WaitACK        			 				: IIC等待对方产生应答还是非应答信号
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
uint8_t IIC_WaitACK(void)
{
	uint8_t Re_Val;                                                            // 返回状态值 1：表示非应答 0：表示应答
	SDA_OUT();                                                                 // SDA设置为输出
	Write_SDA = 1;                                                             // SDA输出高，释放总线控制权
	IIC_Delay();                                                               // 延时大概4.9us
	SDA_IN();                                                                  // SDA 设置为输入模式	
	IIC_SCL = 1;                                                               // SCL置高 

	if(Read_SDA == 1)
	{
		Re_Val = 1;
	}
	else
	{
		Re_Val = 0;
	}	
	IIC_SCL = 0;                                                               // SCL置高 
	IIC_Delay();                                                               // 延时大概4.9us
	
	return Re_Val;
}

/*-----------------------------------------------------------------------
IIC_WriteByte       			 			: IIC写八位数据
	
输入参数                   			：IIC_Data
                                  

-----------------------------------------------------------------------*/
void IIC_WriteByte(uint8_t IIC_Data)
{
	uint8_t i;
	SDA_OUT();                                                                 // SDA设置为输出
	for(i=0;i<8;i++)
	{
		if(IIC_Data & 0x80)                                                      // 判断最高位
		{
			Write_SDA = 1;                                                     
		}
		else
		{
			Write_SDA = 0;                                                     			
		}
	 IIC_Delay();                                                              // 延时大概4.9us
	 IIC_SCL = 1;                                                              // SCL置高 
	 IIC_Delay();                                                              // 延时大概4.9us
	 IIC_SCL = 0;                                                              // SCL置低 
	 if(i == 7)
	 {
		 Write_SDA = 1;                                                          // SDA置高,释放总线
	 }
	 IIC_Data <<= 1;
	 IIC_Delay();                                                              // 延时大概4.9us
	}
}

/*-----------------------------------------------------------------------
IIC_ReadByte       		  	 			: IIC读取八位数据
	
输入参数                   			：IIC_Data
                                  

-----------------------------------------------------------------------*/
uint8_t IIC_ReadByte(void)
{
	uint8_t i;
	uint8_t Value = 0;
	
	SDA_IN();                                                                  // IIC输入模式
	for(i=0;i<8;i++)
	{
		Value <<= 1;
		IIC_SCL = 1;                                                             // SCL置高 
	  IIC_Delay();                                                             // 延时大概4.9us
		if(Read_SDA == 1)
		{
			Value ++;
		}
		IIC_SCL = 0;                                                             // SCL置低
	  IIC_Delay();                                                             // 延时大概4.9us	
	}
	return Value;
}

/*-----------------------------------------------------------------------
IIC_ACK           		  	 			: IIC产生应答信号
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
void IIC_ACK(void)
{
	SDA_OUT();                                                                 // SDA设置为输出
	Write_SDA = 0;                                                     			
	IIC_Delay();                                                               // 延时大概4.9us	
	IIC_SCL = 1;                                                               // SCL置高 
	IIC_Delay();                                                               // 延时大概4.9us	
	IIC_SCL = 0;                                                               // SCL置低
	IIC_Delay();                                                               // 延时大概4.9us	
	Write_SDA = 1;                                                     				 // 释放SDA总线控制权
}

/*-----------------------------------------------------------------------
IIC_NACK           		  	 			: IIC产生非应答信号
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
void IIC_NACK(void)
{
	SDA_OUT();                                                                 // SDA设置为输出
	Write_SDA = 1;                                                     				 // 释放SDA总线控制权
	IIC_Delay();                                                               // 延时大概4.9us	
	IIC_SCL = 1;                                                               // SCL置高 
	IIC_Delay();                                                               // 延时大概4.9us	
	IIC_SCL = 0;                                                               // SCL置低
	IIC_Delay();                                                               // 延时大概4.9us	
}





