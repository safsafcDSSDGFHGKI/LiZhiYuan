#include "gpio.h"

/*-----------------------------------------------------------------------

  GPIO_Mode_AIN                      ģ������
  GPIO_Mode_IN_FLOATING              �������� 
  GPIO_Mode_IPD                      ��������
  GPIO_Mode_IPU                      ��������
  GPIO_Mode_Out_OD                   ��©���
  GPIO_Mode_Out_PP                   �������
  GPIO_Mode_AF_OD                    ���ÿ�©���
  GPIO_Mode_AF_PP                    �����������

-----------------------------------------------------------------------*/


/*-----------------------------------------------------------------------
LCD12864_KEY_Congigure  			 	: ���ܰ�����ʼ��
�������                   			����
                                  

-----------------------------------------------------------------------*/
void LCD12864_KEY_Congigure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                        // �����ṹ��
	RCC_APB2PeriphClockCmd(KFB_KEY_Clock, ENABLE);              // ����GPIOAʱ��
																															
  GPIO_InitStructure.GPIO_Pin = KFB_KEY_Pin;              		// �������ź�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               // ����GPIO��ģʽ
  GPIO_Init(KFB_KEY_Port, &GPIO_InitStructure);               // ��ʼ���ṹ��
}


void LCD12864_LED_BACK(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                        // �����ṹ��
	RCC_APB2PeriphClockCmd(KFB_KEY_Clock, ENABLE);              // ����GPIOAʱ��
																															
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;              		// �������ź�
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;               // ����GPIO��ģʽ
  GPIO_Init(KFB_KEY_Port, &GPIO_InitStructure);               // ��ʼ���ṹ��
}
