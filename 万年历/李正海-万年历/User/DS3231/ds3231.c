#include "ds3231.h"
#include "iic.h"
/*-----------------------------------------------------------------------
IIC_writeOneByte           		  : IIC写数据到IIC器件
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
void IIC_WriteOneByte(uint8_t Addr,uint8_t Data)
{
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(IIC_WriteAddress);                                          // 发送器件地址+写（0）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr);                                                      // 写入数据到器件
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Data);                                                      // 写入数据到器件
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_Stop();                                                               // 产生停止信号
}

/*-----------------------------------------------------------------------
IIC_ReadOneByte           		  : 从器件中读出数据
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
uint8_t IIC_ReadOneByte(uint8_t Addr)
{
	uint8_t IIC_Value;
	
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(IIC_WriteAddress);                                          // 发送器件地址+写（0）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号

	IIC_WriteByte(Addr);                                                      // 发送寄存器地址
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(IIC_ReadAddress);                                           // 发送器件地址+读（1）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	
	IIC_Value = IIC_ReadByte();                                               // 读出数据
	IIC_NACK();                                                               // 非应答信号
	IIC_Stop();                                                               // 产生停止信号
	return IIC_Value;
}

/*-----------------------------------------------------------------------
IIC_WriteMultiByte            	: 写多个数据到器件
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
void IIC_WriteMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num)
{
	uint8_t i;                                                          
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(IIC_WriteAddress);                                          // 发送器件地址+写（0）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr);                                                      // 写入数据到器件
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	
	for(i=0;i<num;i++)                                                        // 循环写入多个数据
	{
		IIC_WriteByte(Arry[i]);                                                 // 写入数据到器件
		while(IIC_WaitACK());                                                   // 等待从机产生应答信号	
	}
	IIC_Stop();                                                               // 产生停止信号

}
/*-----------------------------------------------------------------------
IIC_ReadMultiByte           		: 从器件中读出多个数据
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
void IIC_ReadMultiByte(uint8_t *Arry,uint8_t Addr,uint8_t num)
{
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(IIC_WriteAddress);                                          // 发送器件地址+写（0）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr);                                                      // 发送寄存器地址
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(IIC_ReadAddress);                                           // 发送器件地址+读（1）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	while(num)
	{
		if(num == 1)
		{
			*Arry = IIC_ReadByte();                                               // 读出数据
			IIC_NACK();                                                           // 非应答信号
		}
		else
		{
			*Arry = IIC_ReadByte();                                               // 读出数据
			IIC_ACK();                                                            // 非应答信号		 
		}
		num --;                                                                 // 数据长度-1
		Arry ++;                                                                // 数组地址+1
	}
	IIC_Stop();                                                               // 产生停止信号
}

/*-----------------------------------------------------------------------
IIC_GetTemp                 		: 获取温度
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
void IIC_GetTemp(uint8_t *Arry)
{
	IIC_WriteOneByte(0x0E,0x27);                                              // 向控制寄存器中写入数据，启动温度传输，使能闹钟1和闹钟2，产生中断信号
	
	*Arry = IIC_ReadOneByte(0x11);                                            // 获取温度高八位
	*(Arry+1) = IIC_ReadOneByte(0x12);                                        // 获取温度低八位
}

