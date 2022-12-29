#include "usart.h"

/*-----------------------------------------------------------------------
USART1_Init  			 	    			  : USART1��ʼ������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void USART1_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // ����GPIO�ṹ��
  USART_InitTypeDef    USART_InitStructure;                                              // �������ڽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                                  // ����GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);                                 // �򿪴��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                                              // USATR1_TX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // ���ó����츴�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // �ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                                 // ��ʼ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                             // USART1_RX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // ���óɸ�������Ҳ�������óɴ���������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	                                               // ��ʼ������
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // ��żʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // ��Ӳ��������
  USART_Init(USART1, &USART_InitStructure);                                              // ��ʼ������
//  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	                                       // ʹ�ܴ��ڽ����ж�
	USART_Cmd(USART1,ENABLE);                                                              // ʹ�ܴ���1
}

/*-----------------------------------------------------------------------
USART2_Init  			 	    			  : USART2��ʼ������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void USART2_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // ����GPIO�ṹ��
  USART_InitTypeDef    USART_InitStructure;                                              // �������ڽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);                                  // ����GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);                                 // �򿪴��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                                              // USATR2_TX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // ���ó����츴�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // �ٶ�50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);                                                 // ��ʼ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                                              // USART2_RX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // ���óɸ�������Ҳ�������óɴ���������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	                                               // ��ʼ������
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // ��żʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // ��Ӳ��������
  USART_Init(USART2, &USART_InitStructure);                                              // ��ʼ������
//  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	                                       // ʹ�ܴ��ڽ����ж�
	USART_Cmd(USART2,ENABLE);                                                              // ʹ�ܴ���2
}

/*-----------------------------------------------------------------------
USART3_Init  			 	    			  : USART3��ʼ������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void USART3_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // ����GPIO�ṹ��
  USART_InitTypeDef    USART_InitStructure;                                              // �������ڽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);                                  // ����GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);                                 // �򿪴��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                             // USATR3_TX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // ���ó����츴�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // �ٶ�50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);                                                 // ��ʼ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                             // USART3_RX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // ���óɸ�������Ҳ�������óɴ���������
	GPIO_Init(GPIOB, &GPIO_InitStructure);	                                               // ��ʼ������
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // ��żʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // ��Ӳ��������
  USART_Init(USART3, &USART_InitStructure);                                              // ��ʼ������
//  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	                                       // ʹ�ܴ��ڽ����ж�
	USART_Cmd(USART3,ENABLE);                                                              // ʹ�ܴ���3
}

/*-----------------------------------------------------------------------
USART4_Init  			 	    			  : USART4��ʼ������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void USART4_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // ����GPIO�ṹ��
  USART_InitTypeDef    USART_InitStructure;                                              // �������ڽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);                                  // ����GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);                                  // �򿪴��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                              // USATR4_TX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // ���ó����츴�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // �ٶ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);                                                 // ��ʼ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                                              // USART4_RX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // ���óɸ�������Ҳ�������óɴ���������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	                                               // ��ʼ������
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // ��żʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // ��Ӳ��������
  USART_Init(UART4, &USART_InitStructure);                                               // ��ʼ������
//  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	                                        // ʹ�ܴ��ڽ����ж�
	USART_Cmd(UART4,ENABLE);                                                               // ʹ�ܴ���4
}

/*-----------------------------------------------------------------------
USART5_Init  			 	    			  : USART4��ʼ������
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void USART5_Init(uint32_t Band_Rate)
{
	GPIO_InitTypeDef     GPIO_InitStructure;                                               // ����GPIO�ṹ��
  USART_InitTypeDef    USART_InitStructure;                                              // �������ڽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);                                  // ����GPIOCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);                                  // ����GPIODʱ��

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);                                  // �򿪴��������ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                                             // USATR5_TX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                                        // ���ó����츴�����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                      // �ٶ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);                                                 // ��ʼ������

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                                              // USART5_RX����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                                  // ���óɸ�������Ҳ�������óɴ���������
	GPIO_Init(GPIOD, &GPIO_InitStructure);	                                               // ��ʼ������
	
	USART_InitStructure.USART_BaudRate = Band_Rate;                                        // ���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                            // 8λ����λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                                 // 1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                                    // ��żʹ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;                          // ���ͺͽ���ģʽ
	USART_InitStructure.USART_HardwareFlowControl  = USART_HardwareFlowControl_None;       // ��Ӳ��������
  USART_Init(UART5, &USART_InitStructure);                                               // ��ʼ������
//  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);	                                        // ʹ�ܴ��ڽ����ж�
	USART_Cmd(UART5,ENABLE);                                                               // ʹ�ܴ���5
}
/*-----------------------------------------------------------------------
fputc       			 	    			  : �ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
	
�������                   			��
                                  

-----------------------------------------------------------------------*/
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);                                                  // ����һ���ֽ����ݵ�����                  
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		                       // �ȴ��������
	
	return (ch);
}

/*-----------------------------------------------------------------------
Usart_SendByte       			 	    : ����һ���ֽ�
	
�������                   			��USARTx,data
                                  

-----------------------------------------------------------------------*/
void Usart_SendByte(USART_TypeDef* pUSARTx, uint8_t data)
{
	USART_SendData(pUSARTx, data);                                                         // USART��������
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );                        // �ȴ��������
}

/*-----------------------------------------------------------------------
Usart_SendHalfWord       			 	: ���������ֽڵ�����
	
�������                   			��USARTx,data
                                  

-----------------------------------------------------------------------*/
void Usart_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t data)
{
	uint8_t temp_h,temp_l;                                                                 // �������ݵĸ߰�λ�͵Ͱ�λ
	
	temp_h = (data&0xff00) >> 8 ;                                                          // ȡ���߰�λ
	temp_l = data&0xff;                                                                    // ȡ���Ͱ�λ
	
	USART_SendData(pUSARTx, temp_h);                                                       // ���͸߰�λ
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );                        // �ȴ��������
	
	USART_SendData(pUSARTx, temp_l);                                                       // ���͵Ͱ�λ
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET );                        // �ȴ��������
}

/*-----------------------------------------------------------------------
Usart_SendArray         			 	: ����8λ���ݵ�����
	
�������                   			��USARTx,num������ĳ��ȣ�
                                  

-----------------------------------------------------------------------*/
void Usart_SendArray(USART_TypeDef* pUSARTx, uint8_t *array,uint8_t num)
{
	uint8_t i;                                                                             // �������i
	for( i=0; i<num; i++ )
  {
		Usart_SendByte(pUSARTx, array[i]);                                                   // ѭ�����������ÿ��Ԫ�ط��ͳ�ȥ
	}
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );                         // �ȴ��������
}

/*-----------------------------------------------------------------------
Usart_SendStr           			 	: �����ַ���
	
�������                   			��USARTx,num
                                  

-----------------------------------------------------------------------*/
void Usart_SendStr(USART_TypeDef* pUSARTx, uint8_t *str)
{
	uint8_t i=0;                                                                           // ����ѭ������i
	do
  {
		Usart_SendByte(pUSARTx, *(str+i));                                                   // ���������ÿһ��Ԫ�أ���ַ+1
		i++;
	}
	while(*(str+i) != '\0');                                                               // �ж��Ƿ��ַ�����β
	while( USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET );                         // �ȴ��������
}

