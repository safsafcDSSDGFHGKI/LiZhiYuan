#include "usart.h"

/*-----------------------------------------------------------------------
USART1_Init  			 	    			  : USART1初始化函数
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void USART1_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // 声明GPIO结构体
  USART_InitTypeDef    USART_InitStructure;                                              // 声明串口结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                                  // 开启GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);                                 // 打开串口外设的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                              // USATR1_TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // 配置成推挽复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // 速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                                 // 初始化引脚

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                             // USART1_RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // 配置成浮空输入也可以配置成带上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	                                               // 初始化引脚
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // 奇偶使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // 无硬件流控制
  USART_Init(USART1, &USART_InitStructure);                                              // 初始化配置
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	                                       // 使能串口接收中断
	USART_Cmd(USART1,ENABLE);                                                              // 使能串口1
}

/*-----------------------------------------------------------------------
USART2_Init  			 	    			  : USART2初始化函数
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void USART2_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // 声明GPIO结构体
  USART_InitTypeDef    USART_InitStructure;                                              // 声明串口结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                                  // 开启GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);                                 // 打开串口外设的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                                              // USATR2_TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // 配置成推挽复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // 速度50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                                 // 初始化引脚

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                                              // USART2_RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // 配置成浮空输入也可以配置成带上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	                                               // 初始化引脚
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // 奇偶使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // 无硬件流控制
  USART_Init(USART2, &USART_InitStructure);                                              // 初始化配置
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	                                       // 使能串口接收中断
	USART_Cmd(USART2,ENABLE);                                                              // 使能串口2
}

/*-----------------------------------------------------------------------
USART3_Init  			 	    			  : USART3初始化函数
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void USART3_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // 声明GPIO结构体
  USART_InitTypeDef    USART_InitStructure;                                              // 声明串口结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                  // 开启GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);                                 // 打开串口外设的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                             // USATR3_TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // 配置成推挽复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // 速度50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                                                 // 初始化引脚

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                             // USART3_RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // 配置成浮空输入也可以配置成带上拉输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);	                                               // 初始化引脚
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // 奇偶使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // 无硬件流控制
  USART_Init(USART3, &USART_InitStructure);                                              // 初始化配置
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	                                       // 使能串口接收中断
	USART_Cmd(USART3,ENABLE);                                                              // 使能串口3
}

/*-----------------------------------------------------------------------
USART4_Init  			 	    			  : USART4初始化函数
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void USART4_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // 声明GPIO结构体
  USART_InitTypeDef    USART_InitStructure;                                              // 声明串口结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);                                  // 开启GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);                                  // 打开串口外设的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                              // USATR4_TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // 配置成推挽复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // 速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);                                                 // 初始化引脚

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                              // USART4_RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // 配置成浮空输入也可以配置成带上拉输入
	GPIO_Init(GPIOC, &GPIO_InitStructure);	                                               // 初始化引脚
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // 奇偶使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // 无硬件流控制
  USART_Init(UART4, &USART_InitStructure);                                               // 初始化配置
//  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	                                        // 使能串口接收中断
	USART_Cmd(UART4,ENABLE);                                                               // 使能串口4
}

/*-----------------------------------------------------------------------
USART5_Init  			 	    			  : USART4初始化函数
	
输入参数                   			：无
                                  

-----------------------------------------------------------------------*/
void USART5_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // 声明GPIO结构体
  USART_InitTypeDef    USART_InitStructure;                                              // 声明串口结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);                                  // 开启GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);                                  // 开启GPIOD时钟

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);                                  // 打开串口外设的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                                             // USATR5_TX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // 配置成推挽复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // 速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);                                                 // 初始化引脚

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                                              // USART5_RX引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // 配置成浮空输入也可以配置成带上拉输入
	GPIO_Init(GPIOD, &GPIO_InitStructure);	                                               // 初始化引脚
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // 配置波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8位数据位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1位停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // 奇偶使能
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // 发送和接收模式
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // 无硬件流控制
  USART_Init(UART5, &USART_InitStructure);                                               // 初始化配置
//  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);	                                        // 使能串口接收中断
	USART_Cmd(UART5,ENABLE);                                                               // 使能串口5
}
/*-----------------------------------------------------------------------
fputc       			 	    			  : 重定向c库函数printf到串口，重定向后可使用printf函数
	
输入参数                   			：
                                  

-----------------------------------------------------------------------*/
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);                                                  // 发送一个字节数据到串口                  
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		                       // 等待发送完毕
	
	return (ch);
}

/*-----------------------------------------------------------------------
Usart_SendByte       			 	    : 发送一个字节
	
输入参数                   			：USARTx,data
                                  

-----------------------------------------------------------------------*/
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);                                                         // USART发送数据
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );                        // 等待发送完成
}

/*-----------------------------------------------------------------------
Usart_SendHalfWord       			 	: 发送两个字节的数据
	
输入参数                   			：USARTx,data
                                  

-----------------------------------------------------------------------*/
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data)
{
	uint8_t temp_h,temp_l;                                                                 // 定义数据的高八位和低八位
	
	temp_h = (data&0xff00) >> 8 ;                                                          // 取出高八位
	temp_l = data&0xff;                                                                    // 取出低八位
	
	USART_SendData(pUSARTx, temp_h);                                                       // 发送高八位
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );                        // 等待发送完成
	
	USART_SendData(pUSARTx, temp_l);                                                       // 发送低八位
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );                        // 等待发送完成
}

/*-----------------------------------------------------------------------
Usart_SendArray         			 	: 发送8位数据的数组
	
输入参数                   			：USARTx,num（数组的长度）
                                  

-----------------------------------------------------------------------*/
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num)
{
	uint8_t i;                                                                             // 定义变量i
	for( i=0; i<num; i++ )
  {
		Usart_SendByte(pUSARTx, array[i]);                                                   // 循环把数组里的每个元素发送出去
	}
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );                         // 等待发送完成
}

/*-----------------------------------------------------------------------
Usart_SendStr           			 	: 发送字符串
	
输入参数                   			：USARTx,num
                                  

-----------------------------------------------------------------------*/
void Usart_SendStr(USART_TypeDef* pUSARTx, uint8_t *str)
{
	uint8_t i=0;                                                                           // 定义循环变量i
	do
  {
		Usart_SendByte(pUSARTx, *(str+i));                                                   // 发送数组的每一个元素，地址+1
		i++;
	}
	while(*(str+i) != '\0');                                                               // 判断是否到字符串结尾
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );                         // 等待发送完成
}

