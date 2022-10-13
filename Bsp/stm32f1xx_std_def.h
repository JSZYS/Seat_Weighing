/**
  ******************************************************************************
  * @file    led.h
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F1xx_STD_DEF
#define __STM32F1xx_STD_DEF
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stddef.h>
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  HAL Status structures definition
  */
typedef enum
{
  STD_OK       = 0x00U,
  STD_ERROR    = 0x01U,
  STD_BUSY     = 0x02U,
  STD_TIMEOUT  = 0x03U
} STD_StatusTypeDef;

/**
  * @brief  HAL Lock structures definition
  */
typedef enum
{
  STD_UNLOCKED = 0x00U,
  STD_LOCKED   = 0x01U
} STD_LockTypeDef;

/* Exported macro ------------------------------------------------------------*/
#define STD_MAX_DELAY      0xFFFFFFFFU

void SysTick_Init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(uint32_t nus);
u32 get_times(void);
void set_times(u32 _tick);

#endif /* __STM32F1xx_STD_DEF */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
