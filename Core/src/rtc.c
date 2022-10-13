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

  PWR_BackupAccessCmd(ENABLE);                   //运行操作后备区域

  BKP_DeInit();                                  //复位后备区域

  // RCC_LSEConfig(RCC_LSE_ON);                     //使能低速外部时钟(LSE)
	RCC_LSICmd(ENABLE);
  while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

  // RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);        //选择LSE作为RTC时钟源
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

  RCC_RTCCLKCmd(ENABLE);                         //使能RTC时钟

  RTC_WaitForSynchro();                          //等待同步
  RTC_WaitForLastTask();                         //等待操作完成

  RTC_ITConfig(RTC_IT_ALR, ENABLE);              //使能闹钟中断
  RTC_WaitForLastTask();                         //等待操作完成

  // RTC_SetPrescaler(32767);                       //分频值: RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
  RTC_SetPrescaler(39999);
	RTC_WaitForLastTask();                         //等待操作完成

  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //主优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        //从优先级
  NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief 
 * 
 */
void std_rtc_set_alarm(u32 _alarm)
{
  RTC_SetCounter(0);                             //初始设置Counter = 0
  RTC_WaitForLastTask();                         //等待操作完成

  RTC_SetAlarm(_alarm);                               //闹钟时间
  RTC_WaitForLastTask();                         //等待操作完成
}

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
