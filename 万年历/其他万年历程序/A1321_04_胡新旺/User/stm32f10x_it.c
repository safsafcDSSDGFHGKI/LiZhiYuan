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
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "main.h"
#include "bsp_lcd.h"

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



void EXTI0_IRQHandler()
{
	static unsigned char status;
	
	if(EXTI_GetITStatus(EXTI_Line0) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		if(status==0) 
		{
			LEDBLUE_ON;
			ILI9341_Clear(0,0,240,320,macBLUE);
			status = 1;
		}
		else
		{
			LEDBLUE_OFF;
			ILI9341_Clear(0,0,240,320,macBLACK);
			status = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);     //����жϱ�־λ
	}
}

// EXTI Line --> PE4
void macXPT2046_EXTI_INT_FUNCTION ( void )
{ 
  if ( EXTI_GetITStatus ( macXPT2046_EXTI_LINE ) != RESET )
  {	
    ucXPT2046_TouchFlag = !macXPT2046_EXTI_Read();
		
    EXTI_ClearITPendingBit ( macXPT2046_EXTI_LINE );
		
  }
	
}

void EXTI15_10_IRQHandler()
{
	static unsigned char status;
	
	if(EXTI_GetITStatus(EXTI_Line13) != RESET) //ȷ���Ƿ������EXTI Line�ж�
	{
		if(status==0) 
		{
			LEDGREEN_ON;
			ILI9341_Clear(0,0,240,320,macGREEN);
			status = 1;
		}
		else
		{
			LEDGREEN_OFF;
			ILI9341_Clear(0,0,240,320,macBLACK);
			status = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line13);     //����жϱ�־λ
	}
}


void RTC_IRQHandler(void)
{	

	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);  
		RTC_WaitForLastTask();
		
		Read_RTCTime( &RealTime );
	}
}


/*��ʱ���жϷ������ÿ10ms�ж�1��
�������Ͷ�ʱ��ʱ���׼
*/
void TIM2_IRQHandler(void)
{
	static u16 Timer2Cnt;
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
	   Counter_miao_biao++;
	   miao_biao.MiaoB_hour=Counter_miao_biao/360000%24;
       miao_biao.MiaoB_min=Counter_miao_biao/6000%60;
       miao_biao.MiaoB_sec=Counter_miao_biao/100%60;
       miao_biao.MiaoB_s=Counter_miao_biao%100;	
	   Timer2Cnt = (Timer2Cnt+1)%100;
		
	}
}


/*��ʱ���жϷ������ÿ10ms�ж�1��
��ⰴ������¼��������ʱ����ͷ�ʱ��
*/
void TIM6_IRQHandler(void)
{
	static u8 Clicks = 0;				//��������
	static u16 KeyBuf,KeyBufOld,KeyBufOld2,KeySta;
	static u16 Timer6Cnt;
	
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		
		Timer6Cnt = (Timer6Cnt+1)%100;
				
		/*��ȡ����ֵ����¼��������ʱ��(*10ms)*/
		TP_Scan( );
		
		KeyBufOld2 = KeyBufOld;
		KeyBufOld = KeyBuf;
		KeyBuf = KeyScan();
		
		if(KeyBuf==KeyBufOld)
		{
			if(KeyBuf!=0 && KeyBufOld2==0)			//�հ���
			{
				KeySta = 0x80;
				KeyNum = KeyBuf;
			}
			else if(KeyBuf!=0 && KeyBufOld2!=0)	//��ס
			{
				KeySta = 0xc0;
				if(KeyCnt<60)	KeyNum = KeyBuf;
				else if(KeyCnt>=60)	KeyNum = KeyBuf+0x10;
			}
			else if(KeyBuf==0 && KeyBufOld2!=0)	//���ɿ�
			{
				KeySta = 0x40;
				KeyNum = KeyBufOld2;
			}
			else if(KeyBuf==0 && KeyBufOld2==0)	//��ȫ�ɿ�
			{
				KeySta = 0x00;
				KeyNum = KeyBuf;
			}
		}

		if(tp_dev.sta==0x80 || KeySta==0x80)			//�հ���
		{
			KeyCnt = 0; KeyUpCnt = 0;
		}
		else if(tp_dev.sta==0xc0 || KeySta==0xc0)	//��ס
		{
			KeyCnt++;
		}
		else if(tp_dev.sta==0x40)	//���ɿ�
		{
			KeyUpCnt = 0; KeyCnt = 0;
			Clicks++;
		}
		else if(KeySta==0x40)		KeyUpCnt = 0;
		else if(tp_dev.sta==0x00 && KeySta==0x00)	//��ȫ�ɿ�
		{
			KeyUpCnt++;
			if(KeyUpCnt>=60) Clicks = 0;
		}
	}
}


/*��ʱ���жϷ������ÿ80ms�ж�1��
���ڿ�������
*/
void TIM7_IRQHandler(void)
{
	static u16 Timer7Cnt;
	
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		
		Timer7Cnt = (Timer7Cnt+1)%25;
		
		if( Timer7Cnt<8 )
		{
			if( Timer7Cnt%2 == 0 )	
			TIM_CtrlPWMOutputs( TIM1 , ENABLE );
			else 
			TIM_CtrlPWMOutputs( TIM1 , DISABLE );
		}
		else TIM_CtrlPWMOutputs( TIM1 , DISABLE );
	}
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
