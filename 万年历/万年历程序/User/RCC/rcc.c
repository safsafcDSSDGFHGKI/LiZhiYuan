#include "rcc.h"
/*-----------------------------------------------------------------------
HSE_SystemClock  			 				  : �ⲿϵͳʱ�Ӻ���
	
�������                   			��RCC_PLLMul   This parameter can be RCC_PLLMul_x where x:[2,16]  
                                  PLLCLK = 8MHz * RCC_PLLMul_x  (x = 2~16)
��д����                        	��2018��11��18��
����޸�����                  		��2018��11��18��
-----------------------------------------------------------------------*/
void HSE_SystemClock(uint32_t RCC_PLLMul_x)
{
	__IO uint32_t HESStartUp = 0;
	RCC_DeInit();                                                  // ������RCC�Ĵ�������ΪĬ��ֵ
	RCC_HSEConfig(RCC_HSE_ON);                                     // �����ⲿ���߾���HSE�� RCC_HSE_ON ��HSE����ON  RCC_HSE_OFF ��HSE����OFF
	
	HESStartUp = RCC_WaitForHSEStartUp();                          // �ȴ�HSE����
	
	if(HESStartUp == SUCCESS)                                      // ��������ȶ�����
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);        // Ԥȡָ����ʹ��
		FLASH_SetLatency(FLASH_Latency_2);                           // ���ô�����ʱֵ
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 														 // ����AHBʱ��=ϵͳʱ�� RCC_SYSCLK_Divx : x= 1,2,4,8,16,32,64,128,256,512
		RCC_PCLK2Config(RCC_HCLK_Div1);                              // ����APB1ʱ�� = HCLK
		RCC_PCLK1Config(RCC_HCLK_Div2);                              // ����APB1ʱ�� = HCLK/2
		                            
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_x);          // ����PLLʱ��Դ����Ƶϵ��
		RCC_PLLCmd(ENABLE);                                          // ʹ��PLL
	  while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)          // ���ָ���ı�־λ�������
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08);                        // ����PLL��Ϊϵͳʱ��Դ
	}
}
/*-----------------------------------------------------------------------
MCO_GPIO_Config  			 				  : MCO�ⲿ�������ú���
	
�������                   			��RCC_PLLMul   This parameter can be RCC_PLLMul_x where x:[2,16]  
                                  PLLCLK = 8MHz * RCC_PLLMul_x  (x = 2~16)
��д����                        	��2018��11��18��
����޸�����                  		��2018��11��18��
-----------------------------------------------------------------------*/
void MCO_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                           // ����GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;											 // ѡ��GPIO8����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;								 //����Ϊ���ù����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;							 //����IO�ķ�ת����Ϊ50M
	GPIO_Init(GPIOA, &GPIO_InitStructure);												 // ��ʼ��GPIOA8
}

