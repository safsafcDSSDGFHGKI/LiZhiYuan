#include "at24c32.h"
#include "iic.h"
#include "usart.h"

/*-----------------------------------------------------------------------
AT24C32_WriteOneByte            : IIC写数据到AT24C32器件
	
输入参数                   			：uint16_t Addr,uint8_t Data  (AT24C32 是12位地址)
                                  

-----------------------------------------------------------------------*/
void AT24C32_WriteOneByte(uint16_t Addr,uint8_t Data)
{
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(AT24C32_WriteAddr);                                         // 发送器件地址+写（0）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr>>8);                                                   // 写入器件地址高八位
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr&0xFF);                                                 // 写入器件地址低八位
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Data);                                                      // 写入数据到器件
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_Stop();                                                               // 产生停止信号
}

/*-----------------------------------------------------------------------
AT24C32_ReadOneByte             : 从AT24C32中读取数据
	
输入参数                   			：uint16_t Addr (AT24C32 是12位地址)
                                  

-----------------------------------------------------------------------*/
uint8_t AT24C32_ReadOneByte(uint16_t Addr)
{
	uint8_t AT24C32_Value;                                                    // 存放读出的数据值

	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(AT24C32_WriteAddr);                                         // 发送器件地址+写（0）
	IIC_WaitACK();                                                            // 等待从机产生应答信号
	IIC_WriteByte(Addr>>8);                                                   // 发送寄存器地址
	IIC_WaitACK();	                                                          // 等待从机产生应答信号
	IIC_WriteByte(Addr&0xFF);                                                 // 发送寄存器地址
	IIC_WaitACK();                                                            // 等待从机产生应答信号
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(AT24C32_ReadAddr);                                          // 发送器件地址+读（1）
	IIC_WaitACK();                                                            // 等待从机产生应答信号
	AT24C32_Value = IIC_ReadByte();                                           // 读出数据
	IIC_NACK();                                                               // 非应答信号
	IIC_Stop();                                                               // 产生停止信号
	
	return AT24C32_Value;                                                     // 返回读出的值
}

/*-----------------------------------------------------------------------
AT24C32_PageWrite               : 页写入数据
	
输入参数                   			：uint16_t Addr,uint8_t *Page_Arry,uint8_t num (n不能大于32，否则会从头覆盖字节)
                                  

-----------------------------------------------------------------------*/
void AT24C32_PageWrite(uint16_t Addr,uint8_t *Page_Arry,uint8_t num)
{
	uint8_t i;
	if(num>32) num = 32;
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(AT24C32_WriteAddr);                                         // 发送器件地址+写（0）
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr>>8);                                                   // 写入器件地址高八位
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	IIC_WriteByte(Addr&0xFF);                                                 // 写入器件地址低八位
	while(IIC_WaitACK());                                                     // 等待从机产生应答信号
	for(i=0;i<num;i++)                                                        // 循环写入多个数据
	{
		IIC_WriteByte(Page_Arry[i]);                                            // 写入数据到器件
		while(IIC_WaitACK());                                                   // 等待从机产生应答信号	
	}
	IIC_Stop();                                                               // 产生停止信号
}

/*-----------------------------------------------------------------------
AT24C32_PageRead                : 页读取数据
	
输入参数                   			：uint16_t Addr,uint8_t *Page_Arry,uint8_t num (n不能大于32，否则会从头覆盖字节)
                                  

-----------------------------------------------------------------------*/
void AT24C32_PageRead(uint16_t Addr,uint8_t *Page_Arry,uint8_t num)
{
	if(num>32) num = 32;
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(AT24C32_WriteAddr);                                         // 发送器件地址+写（0）
	IIC_WaitACK();                                                            // 等待从机产生应答信号
	IIC_WriteByte(Addr>>8);                                                   // 发送寄存器地址
	IIC_WaitACK();	                                                          // 等待从机产生应答信号
	IIC_WriteByte(Addr&0xFF);                                                 // 发送寄存器地址
	IIC_WaitACK();                                                            // 等待从机产生应答信号
	IIC_Start();                                                              // IIC起始信号
	IIC_WriteByte(AT24C32_ReadAddr);                                          // 发送器件地址+读（1）
	IIC_WaitACK(); 
	while(num)
	{
		if(num == 1)
		{
			*Page_Arry = IIC_ReadByte();                                          // 读出数据
			IIC_NACK();                                                           // 非应答信号
		}
		else
		{
			*Page_Arry = IIC_ReadByte();                                          // 读出数据
			IIC_ACK();                                                            // 非应答信号		 
		}
		num --;                                                                 // 数据长度-1
		Page_Arry ++;                                                           // 数组地址+1
	}
	IIC_Stop();                                                               // 产生停止信号
}




