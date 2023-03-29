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
#ifndef __STORE_H__
#define __STORE_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "sensor.h"

/* Defines -------------------------------------------------------------------*/
#define CS_VERSION                      1L          /* < major version number */
#define CS_SUBVERSION                   0L          /* < minor version number */
#define CS_REVISION                     0L         /* < revise version number */

/* Prototypes-----------------------------------------------------------------*/
extern u8 sit_axis;
extern u8 can_send_state_buf[8];
extern u32 sys_tim_tick;
extern u32 sys_com_tick;
extern u16 sensor_ad_buf[96];
extern u32 area_bit_state;

<<<<<<< HEAD
=======
//extern u32 Seat_Weight_Count;
//extern u8 Current_Seat_weight;
//extern u8 Last_Seat_weight;
extern u8 Seat_weight;

extern int Abs(int num);
extern void Weight_Filtering(u32 SeatWeight);
extern void weight_Checklist(void);

>>>>>>> b7fe045 (新版本改为查表方式)

#endif /* __XXXX_H__ */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
