/**
  ******************************************************************************
  * @file    can_com.c
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
#include "can_com.h"

/*----------------------------------------------------------------------------*/
/* Configure xxxx                                                             */
/*----------------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define MSG_ID    0x30C


void can_com_enable(void)
{
  GPIO_WriteBit(CAN_RS_Port, CAN_RS_Pin, Bit_RESET);
}

void can_com_disable(void)
{
  GPIO_WriteBit(CAN_RS_Port, CAN_RS_Pin, Bit_SET);
}


/**
  * @brief  
  * @param  
  * @retval 
  */
u8 can_send_msg(u8 *msg, u8 len)
{
  u8 i = 0;
  u16 cnt = 0;
  CanTxMsg tx_msg;

  tx_msg.StdId = MSG_ID; // 标识符
  tx_msg.IDE = CAN_Id_Standard; // 标准帧
  tx_msg.RTR = CAN_RTR_Data; // 数据帧
  tx_msg.DLC = len; // 要发送的数据长度

  can_com_enable();
  for(i = 0; i < len; i++)
  {
    tx_msg.Data[i] = msg[i];
  }

  do
  {
    if (CAN_TxStatus_NoMailBox != CAN_Transmit(CAN1, &tx_msg))
    {
      break;
    }
    cnt++;
  } while (cnt < 0xff00);
  
  if (cnt < 0xff00)
  {
    return 0;
  }
  
  return 1;
}

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
