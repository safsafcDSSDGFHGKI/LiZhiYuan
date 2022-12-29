/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
//#include "GPIO_Bit_Config.h"
//#include "delay.h"
//#include "gpio.h"
#include "time.h"
#include "usart.h"

extern uint16_t time;
/*----------------------------------------------------------------------------*/


//extern uint8_t LED[8];
//uint8_t i,j;

/*----------------------------------------------------------------------------*/
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/*-----------------------------------------------------------------------
EXTI0_IRQHandler  			 			  : �жϷ�������start_stm32f10x_hd.s��
	
�������                   			����
                                  
��д����                        	��2018��11��19��
����޸�����                  		��2018��11��20��
-----------------------------------------------------------------------*/
//void EXTI2_IRQHandler(void)
//{
////	if(EXTI_GetITStatus(EXTI_Line2) != RESET)             // �ж��ж��Ƿ���
////	{
////		for(i=0;i<8;i++)
////		{
////			GPIO_Write(GPIOC, LED[i]);
////			Delay(1000);
////		}                          
////		EXTI_ClearITPendingBit(EXTI_Line2);                 // ����жϱ�־λ
////	}
//}
/*-----------------------------------------------------------------------
		
	ע��
			�ж�Ƕ�������ϵͳ�δ�ʱ����������ˮ�Ƶ���ʱ��Ƕ�׻�ʧ�ܣ�
			����ռ���ȼ��Ŀ����жϣ������ȼ��Ľ������жϷ�����

-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------
EXTI1_IRQHandler  			 			  : �жϷ�������start_stm32f10x_hd.s��
	
�������                   			����
                                  
��д����                        	��2018��11��19��
����޸�����                  		��2018��11��20��
-----------------------------------------------------------------------*/
//void EXTI4_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line4) != RESET)             // �ж��ж��Ƿ���
//	{
//		LED_BACK = ~LED_BACK;
//		EXTI_ClearITPendingBit(EXTI_Line4);                 // ����жϱ�־λ
//	}
//}

void TIMx_IRQHandler()
{
	if(TIM_GetITStatus(TIMx, TIM_IT_Update) == SET)
	{
		time ++;
//		if(time == 500)
//		{
//			time = 0;
////			printf("X = %d\r\n",time);
//		}
		TIM_ClearITPendingBit(TIMx, TIM_IT_Update);
	}
}
/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
