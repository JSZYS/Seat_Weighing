/**
  ******************************************************************************
  * @file    xxx.c
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
#include "can.h"

/*----------------------------------------------------------------------------*/
/* Configure xxxx                                                             */
/*----------------------------------------------------------------------------*/

/**
  * @brief  
  * @param  
  * @retval 
  */
void std_can_init(void)
{
	CAN_InitTypeDef CAN_InitStructure;
  CAN_FilterInitTypeDef  CAN_FilterInitStructure;
  // NVIC_InitTypeDef  NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

  CAN_DeInit(CAN1);
  CAN_StructInit(&CAN_InitStructure);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE; /* 非时间触发通信模式 */
  CAN_InitStructure.CAN_ABOM = ENABLE;  /* 软件自动离线管理 */
  CAN_InitStructure.CAN_AWUM = DISABLE; /* 睡眠模式通过软件唤醒 */
  CAN_InitStructure.CAN_NART = DISABLE; /* 禁止报文自动发送 */
  CAN_InitStructure.CAN_RFLM = DISABLE; /* 报文不锁定，新的覆盖旧的 */
  CAN_InitStructure.CAN_TXFP = DISABLE; /* 优先级由报文标识符决定 */
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /* 0 普通模式；1 回环模式 */

  /* CAN Baudrate = 500kBps*/
  /* baudrate = 1/(1tq + tBS1 + tBS2)*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;  /* 重新同步跳跃宽度 */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq; /* 时间段 1 占用时间单位 */
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;  /* 时间段 2 占用时间单位 */
  // CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  /* 重新同步跳跃宽度 */
  // CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq; /* 时间段 1 占用时间单位 */
  // CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;  /* 时间段 2 占用时间单位 */
  CAN_InitStructure.CAN_Prescaler = 4;      /* 分频系数 */
  CAN_Init(CAN1, &CAN_InitStructure);
  
  CAN_FilterInitStructure.CAN_FilterNumber = 0; /* 过滤器0 */
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;  /* 32位ID */
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0002;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;  /* 32位MASK */
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0002;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0; /* FIFO0 */
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;  /* 激活过滤器0 */
  CAN_FilterInit(&CAN_FilterInitStructure);

  /* Configures the NVIC for CAN */
  // CAN_ITConfig(CAN1, CAN_IT_FMP0|CAN_IT_FMP1, ENABLE);      /* FIFO0 消息挂号中断允许. */
  // NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
  // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
  // NVIC_Init(&NVIC_InitStructure);

  // NVIC_InitStructure.NVIC_IRQChannel = CAN1_SCE_IRQn;
  // NVIC_Init(&NVIC_InitStructure);
}

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
