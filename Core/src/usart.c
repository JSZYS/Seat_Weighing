/**
  ******************************************************************************
  * @file    usart.c
  * @brief
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 oogrow.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/**
  * @brief  ÅäÖÃÇ¶Ì×ÏòÁ¿ÖÐ¶Ï¿ØÖÆÆ÷NVIC
  * @param  ÎÞ
  * @retval ÎÞ
  */
// static void USART1_NVIC_Configuration(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;

//   NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   NVIC_Init(&NVIC_InitStructure);
// }

static void USART2_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Í¿Ñ»À¶ÑÀÄ£¿é
 * 
 */
// void std_usart1_uart_init(void)
// {
//   // GPIO_InitTypeDef GPIO_InitStructure;
//   USART_InitTypeDef USART_InitStructure;

//   // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//   RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

//   /* USART1 TX */
//   // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//   // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//   // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   // GPIO_Init(GPIOA, &GPIO_InitStructure);

//   /* USART1 RX */
//   // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//   // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//   // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   // GPIO_Init(GPIOA, &GPIO_InitStructure);

//   USART_InitStructure.USART_BaudRate = 9600;
//   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//   USART_InitStructure.USART_StopBits = USART_StopBits_1;
//   USART_InitStructure.USART_Parity = USART_Parity_No ;
//   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//   USART_Init(USART1, &USART_InitStructure);

//   USART1_NVIC_Configuration();

//   USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

//   USART_Cmd(USART1, DISABLE);
// }

/**
 * @brief debug
 * 
 */
void std_usart2_uart_init(void)
{
  // GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  /* USART2 TX */
  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USART2 RX */
  // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  // GPIO_Init(GPIOA, &GPIO_InitStructure);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);

  USART2_NVIC_Configuration();

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  USART_Cmd(USART2, ENABLE);
}

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
