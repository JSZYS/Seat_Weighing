/**
  ******************************************************************************
  * @file    xxxx.h
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HX711_H__
#define __HX711_H__

/* Includes ------------------------------------------------------------------*/
#include "common_inc.h"

/* Defines -------------------------------------------------------------------*/

/* Prototypes-----------------------------------------------------------------*/
#if 0
u32 get_hx711_1_value(void);
u32 get_hx711_2_value(void);
u32 get_hx711_3_value(void);
u32 get_hx711_4_value(void);
#else
u32 get_hx711_1_value(u32 * channel_b_value);
u32 get_hx711_2_value(u32 * channel_b_value);
u32 get_hx711_3_value(u32 * channel_b_value);
u32 get_hx711_4_value(u32 * channel_b_value);
#endif
#endif /* __HX711_H__ */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
