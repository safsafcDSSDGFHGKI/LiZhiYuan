#include "nvic.h"
#include "time.h"
/*-----------------------------------------------------------------------
NVIC_Configure  			 				  : NVIC���ú���
	
�������                   			����
                                  

-----------------------------------------------------------------------*/
void NVIC_Configure(void)
{
	NVIC_InitTypeDef  NVIC_InitStruct;                     		   // �����ṹ��
	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);        		   // �������ȼ�����
//	NVIC_InitStruct.NVIC_IRQChannel = Key_IRQChannel;            // ָ���ж�ͨ���ţ��ο� stm32f10x.h ͷ�ļ�
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;    // ������ռ���ȼ�
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;           // ������Ӧ���ȼ�
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                 // ʹ���ж�ͨ��	
//	NVIC_Init(&NVIC_InitStruct);                                 // ��ʼ��NVIC
	
//	NVIC_InitStruct.NVIC_IRQChannel = Key1_IRQChannel;           // ָ���ж�ͨ���ţ��ο� stm32f10x.h ͷ�ļ�
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;    // ������ռ���ȼ�
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;           // ������Ӧ���ȼ�
//	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                 // ʹ���ж�ͨ��	
//	NVIC_Init(&NVIC_InitStruct); 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_x);                                          // ѡ����
	NVIC_InitStruct.NVIC_IRQChannel = TIMx_IRQn;                                             // �����ж�Դ              
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;                                   // ������ռ���ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;                                          // ���������ȼ�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;                                             // ʹ��
	NVIC_Init(&NVIC_InitStruct);
}



