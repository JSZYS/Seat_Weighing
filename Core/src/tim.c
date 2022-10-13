/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

void std_tim3_init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  /* ��ʱ�� TIM3 ��ʼ�� */
  /* Tout = (TIM_Period + 1)*(TIM_Prescaler + 1)/Tclk */
  /* Tout= ((1999+1)*( 71+1))/72 = 2000us = 2ms */
  TIM_TimeBaseStructure.TIM_Period = 1999;                     // �����Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler = 71;                   // ����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // ����ʱ�ӷָ�
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM ���ϼ���
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             // ��ʼ�� TIM3
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);                  // ��������ж�
  
  /* �ж����ȼ� NVIC ���� */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           // TIM3 �ж�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; // ǿռ���ȼ� 3 ��
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // �����ȼ� 0 ��
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ ͨ����ʹ��
  NVIC_Init(&NVIC_InitStructure);                           // ��ʼ�� NVIC �Ĵ���
  TIM_Cmd(TIM3, ENABLE);                                    // ʹ�� TIM3
}

/******************* (C) COPYRIGHT 2022 GP��Nano ***************END OF FILE*****/
