#include "rcc.h"
/*-----------------------------------------------------------------------
HSE_SystemClock  			 				  : 外部系统时钟函数
	
输入参数                   			：RCC_PLLMul   This parameter can be RCC_PLLMul_x where x:[2,16]  
                                  PLLCLK = 8MHz * RCC_PLLMul_x  (x = 2~16)
编写日期                        	：2018年11月18日
最后修改日期                  		：2018年11月18日
-----------------------------------------------------------------------*/
void HSE_SystemClock(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HESStartUp = 0;
	RCC_DeInit();                                                  // 将外设RCC寄存器重设为默认值
	RCC_HSEConfig(RCC_HSE_ON);                                     // 设置外部告诉晶振（HSE） RCC_HSE_ON ：HSE晶振ON  RCC_HSE_OFF ：HSE晶振OFF
	
	HESStartUp = RCC_WaitForHSEStartUp();                          // 等待HSE起振
	
	if(HESStartUp == SUCCESS)                                      // 如果晶振稳定就绪
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);        // 预取指缓存使能
		FLASH_SetLatency(FLASH_Latency_2);                           // 设置代码延时值
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 														 // 设置AHB时钟=系统时钟 RCC_SYSCLK_Divx : x= 1,2,4,8,16,32,64,128,256,512
		RCC_PCLK2Config(RCC_HCLK_Div1);                              // 设置APB1时钟 = HCLK
		RCC_PCLK1Config(RCC_HCLK_Div2);                              // 设置APB1时钟 = HCLK/2
		                            
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);          // 设置PLL时钟源及倍频系数
		RCC_PLLCmd(ENABLE);                                          // 使能PLL
	  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)          // 检查指定的标志位设置与否
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08);                        // 设置PLL作为系统时钟源
	}
}
/*-----------------------------------------------------------------------
MCO_GPIO_Config  			 				  : MCO外部引脚配置函数
	
输入参数                   			：RCC_PLLMul   This parameter can be RCC_PLLMul_x where x:[2,16]  
                                  PLLCLK = 8MHz * RCC_PLLMul_x  (x = 2~16)
编写日期                        	：2018年11月18日
最后修改日期                  		：2018年11月18日
-----------------------------------------------------------------------*/
void MCO_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                           // 开启GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;											 // 选择GPIO8引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;								 //设置为复用功能推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							 //设置IO的翻转速率为50M
	GPIO_Init(GPIOA, &GPIO_InitStructure);												 // 初始化GPIOA8
}

