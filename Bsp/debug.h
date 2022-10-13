/**
  ******************************************************************************
  * @file    debug.h
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H__
#define __DEBUG_H__

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Defines -------------------------------------------------------------------*/

/* Prototypes-----------------------------------------------------------------*/

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num);

void hex2string(char *hex, char *ascII, int len, int *newlen);
void pritf_sys_info(void);
void debug_sensor_adc(void);

#endif /* __DEBUG_H */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
