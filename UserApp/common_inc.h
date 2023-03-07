#ifndef __COMMON_INC_H
#define __COMMON_INC_H


#include "stm32f1xx_std_def.h"
#include "main.h"

#include "pin.h"
#include "debug.h"
#include "store.h"
#include "can_com.h"
#include "hx711.h"

/* Defines -------------------------------------------------------------------*/
#define UART_DEBUG 1
/* Prototypes-----------------------------------------------------------------*/

extern u8 sys_wake_state;
extern u32 sys_tim1s_tick;

void user_main(void);

#endif

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
