/**
  ******************************************************************************
  * @file    user_it.c
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "common_inc.h"
#include "store.h"

/**
 * @brief 2ms
 * 
 */
void TIM3_IRQHandler(void)
{
  /* 检查 TIM3 更新中断发生与否 */
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    sys_tim_tick++;
    sys_com_tick++;
  }
}

/**
 * @brief 接涂鸦蓝牙模块
 * 
 */
// void USART1_IRQHandler(void)
// {
//   if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
//   {
//     uart_receive_input(USART_ReceiveData(USART1));
//   }
//   USART_ClearFlag(USART1, USART_FLAG_TC);
// }

/**
 * @brief debug 口
 * 
 */
void USART2_IRQHandler(void)
{
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
    USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    USART_ReceiveData(USART2);
  }
  USART_ClearFlag(USART2, USART_FLAG_TC);
}

/**
  * @brief  This function handles RTC Alarm interrupt request.
  * @param  None
  * @retval None
  */
// void RTC_IRQHandler(void)
// {
//   if(RTC_GetITStatus(RTC_IT_ALR) != RESET)
//   {
//     RTC_ClearITPendingBit(RTC_IT_ALR);           //清除中断标志位
//     RTC_WaitForLastTask();                       //等待操作完成
//   }
// }
/******************* (C) COPYRIGHT 2022 GP·Nano ***************END OF FILE*****/
