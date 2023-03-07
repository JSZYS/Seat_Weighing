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
  CAN_InitStructure.CAN_TTCM = DISABLE; /* ��ʱ�䴥��ͨ��ģʽ */
  CAN_InitStructure.CAN_ABOM = ENABLE;  /* ����Զ����߹��� */
  CAN_InitStructure.CAN_AWUM = DISABLE; /* ˯��ģʽͨ��������� */
  CAN_InitStructure.CAN_NART = DISABLE; /* ��ֹ�����Զ����� */
  CAN_InitStructure.CAN_RFLM = DISABLE; /* ���Ĳ��������µĸ��Ǿɵ� */
  CAN_InitStructure.CAN_TXFP = DISABLE; /* ���ȼ��ɱ��ı�ʶ������ */
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /* 0 ��ͨģʽ��1 �ػ�ģʽ */

  /* CAN Baudrate = 500kBps*/
  /* baudrate = 1/(1tq + tBS1 + tBS2)*/
  CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;  /* ����ͬ����Ծ��� */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq; /* ʱ��� 1 ռ��ʱ�䵥λ */
  CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;  /* ʱ��� 2 ռ��ʱ�䵥λ */
  // CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;  /* ����ͬ����Ծ��� */
  // CAN_InitStructure.CAN_BS1 = CAN_BS1_9tq; /* ʱ��� 1 ռ��ʱ�䵥λ */
  // CAN_InitStructure.CAN_BS2 = CAN_BS2_8tq;  /* ʱ��� 2 ռ��ʱ�䵥λ */
  CAN_InitStructure.CAN_Prescaler = 4;      /* ��Ƶϵ�� */
  CAN_Init(CAN1, &CAN_InitStructure);
  
  CAN_FilterInitStructure.CAN_FilterNumber = 0; /* ������0 */
  CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;  /* 32λID */
  CAN_FilterInitStructure.CAN_FilterIdLow = 0x0002;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;  /* 32λMASK */
  CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0002;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0; /* FIFO0 */
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;  /* ���������0 */
  CAN_FilterInit(&CAN_FilterInitStructure);

  /* Configures the NVIC for CAN */
  // CAN_ITConfig(CAN1, CAN_IT_FMP0|CAN_IT_FMP1, ENABLE);      /* FIFO0 ��Ϣ�Һ��ж�����. */
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
