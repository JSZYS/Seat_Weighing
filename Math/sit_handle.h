/**
  ******************************************************************************
  * @file    sit_handle.h
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIT_HANDLE_H__
#define __SIT_HANDLE_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Defines -------------------------------------------------------------------*/

/* Prototypes-----------------------------------------------------------------*/

typedef enum {false = 0, true = !false} bool;

typedef enum{
  SIT_STATE_NORMAL    = 0, /* ���� */
  SIT_STATE_FRONT     = 1, /* ǰ�� */
  SIT_STATE_AFTER     = 2, /* �� */
  SIT_STATE_LEFT_LEG  = 3, /* ���̶����� */
  SIT_STATE_RIGHT_LEG = 4, /* ���̶����� */
  SIT_STATE_LEFT      = 5, /* ���� */
  SIT_STATE_RIGHT     = 6, /* ���� */
  SIT_STATE_NOT 		  = 10 /* δ�� */
} sit_state_enum;

sit_state_enum sit_state_handle(void);
void sit_state_nvds(sit_state_enum _state);


#endif /* __SIT_HANDLE_H__ */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
