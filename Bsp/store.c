/**
  ******************************************************************************
  * @file    store.c
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
#include "store.h"

u8 sit_axis = 0;
u8 can_send_state_buf[8];
u32 sys_tim_tick = 0;
u32 sys_com_tick = 0;

u16 sensor_ad_buf[SENSOR_DATE_NUM] = {0};
u32 area_bit_state = 0;

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
