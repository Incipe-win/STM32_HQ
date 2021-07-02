/**
 ******************************************************************************
 * @file    FMC_SDRAM/stm32f4xx_it.c
 * @author  MCD Application Team
 * @version V1.0.1
 * @date    11-November-2013
 * @brief   Main Interrupt Service Routines.
 *         This file provides template for all exceptions handler and
 *         peripherals interrupt service routine.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "delay.h"
#include "exti.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "system.h"
#include "uart.h"

/** @addtogroup STM32F429I_DISCOVERY_Examples
 * @{
 */

/** @addtogroup FMC_SDRAM
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 * @param  None
 * @retval None
 */
void NMI_Handler(void) {}

/**
 * @brief  This function handles Hard Fault exception.
 * @param  None
 * @retval None
 */
void HardFault_Handler(void) {
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1) {
  }
}

/**
 * @brief  This function handles Memory Manage exception.
 * @param  None
 * @retval None
 */
void MemManage_Handler(void) {
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1) {
  }
}

/**
 * @brief  This function handles Bus Fault exception.
 * @param  None
 * @retval None
 */
void BusFault_Handler(void) {
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1) {
  }
}

/**
 * @brief  This function handles Usage Fault exception.
 * @param  None
 * @retval None
 */
void UsageFault_Handler(void) {
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1) {
  }
}

/**
 * @brief  This function handles Debug Monitor exception.
 * @param  None
 * @retval None
 */
void DebugMon_Handler(void) {}

/**
 * @brief  This function handles SVCall exception.
 * @param  None
 * @retval None
 */
void SVC_Handler(void) {}

/**
 * @brief  This function handles PendSV_Handler exception.
 * @param  None
 * @retval None
 */
void PendSV_Handler(void) {}

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void) {}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f429_439xx.s).                         */
/******************************************************************************/

/**
 * @}
 */

/**
 * @}
 */

// void EXTI4_IRQHandler(void) {
//   if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
//     GPIO_ResetBits(GPIOE, LED1_PIN);
//     delay_ms(1000);
//     GPIO_SetBits(GPIOE, LED1_PIN);
//     EXTI_ClearITPendingBit(EXTI_Line4);
//   }
// }

// void EXTI9_5_IRQHandler(void) {
//   if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
//     GPIO_ResetBits(GPIOE, LED2_PIN);
//     delay_ms(1000);
//     GPIO_SetBits(GPIOE, LED2_PIN);
//     EXTI_ClearITPendingBit(EXTI_Line5);
//   } else if (EXTI_GetFlagStatus(EXTI_Line6) != RESET) {
//     GPIO_ResetBits(GPIOE, LED3_PIN);
//     delay_ms(1000);
//     GPIO_SetBits(GPIOE, LED3_PIN);
//     EXTI_ClearITPendingBit(EXTI_Line6);
//   }
// }

void EXTI4_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
    BEEP = !BEEP;
    EXTI_ClearITPendingBit(EXTI_Line4);
  }
}

void EXTI9_5_IRQHandler(void) {
  if (EXTI_GetITStatus(EXTI_Line5) != RESET) {
    GPIO_ResetBits(GPIOE, LED2_PIN);
    delay_ms(1000);
    GPIO_SetBits(GPIOE, LED2_PIN);
    EXTI_ClearITPendingBit(EXTI_Line5);
  } else if (EXTI_GetFlagStatus(EXTI_Line6) != RESET) {
    GPIO_ResetBits(GPIOE, LED3_PIN);
    delay_ms(1000);
    GPIO_SetBits(GPIOE, LED3_PIN);
    EXTI_ClearITPendingBit(EXTI_Line6);
  }
}

// void USART1_IRQHandler(void) {
//   u8 res;
//   if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
//     res = USART_ReceiveData(USART1);
//     USART_SendData(USART3, res);
//     USART_SendData(USART1, res);
//     while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
//       ;
//   }
// }

void USART1_IRQHandler(void) {
  u8 res;
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
    res = USART_ReceiveData(USART1);
    if (res == '2') {
      LED2 = !LED2;
    } else if (res == '3') {
      LED3 = !LED3;
    }
    USART_SendData(USART1, res);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
      ;
  }
}

void USART3_IRQHandler(void) {
  u8 res;
  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
    res = USART_ReceiveData(USART3);
    USART_SendData(USART6, res);
    USART_SendData(USART1, res);
    while (USART_GetFlagStatus(USART6, USART_FLAG_TC) != SET)
      ;
  }
}

void USART6_IRQHandler(void) {
  u8 res;
  if (USART_GetITStatus(USART6, USART_IT_RXNE) != RESET) {
    res = USART_ReceiveData(USART6);
    USART_SendData(USART1, res);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
      ;
  }
}

void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    LED1 = !LED1;
  }
}

//定时器3中断服务程序
// TIM3中断
void TIM3_IRQHandler(void) {
  //检查TIM3更新中断发生与否
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
    //清除TIMx更新中断标志
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    LED2 = !LED2;
  }
}

void TIM4_IRQHandler(void) {
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    LED3 = !LED3;
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
