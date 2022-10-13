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
#include "rtc.h"

/*----------------------------------------------------------------------------*/
/* Configure RTC                                                              */
/*----------------------------------------------------------------------------*/

/**
 * @brief 
 * 
 */
void std_rtc_init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  PWR_BackupAccessCmd(ENABLE);                   //���в���������

  BKP_DeInit();                                  //��λ������

  // RCC_LSEConfig(RCC_LSE_ON);                     //ʹ�ܵ����ⲿʱ��(LSE)
	RCC_LSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

  // RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);        //ѡ��LSE��ΪRTCʱ��Դ
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  RCC_RTCCLKCmd(ENABLE);                         //ʹ��RTCʱ��

  RTC_WaitForSynchro();                          //�ȴ�ͬ��
  RTC_WaitForLastTask();                         //�ȴ��������

  RTC_ITConfig(RTC_IT_ALR, ENABLE);              //ʹ�������ж�
  RTC_WaitForLastTask();                         //�ȴ��������

  // RTC_SetPrescaler(32767);                       //��Ƶֵ: RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
  RTC_SetPrescaler(39999);
	RTC_WaitForLastTask();                         //�ȴ��������

  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //�����ȼ�
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief 
 * 
 */
void std_rtc_set_alarm(u32 _alarm)
{
  RTC_SetCounter(0);                             //��ʼ����Counter = 0
  RTC_WaitForLastTask();                         //�ȴ��������

  RTC_SetAlarm(_alarm);                               //����ʱ��
  RTC_WaitForLastTask();                         //�ȴ��������
}

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
