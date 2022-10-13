/**
  ******************************************************************************
  * @file    xxx.c
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
#include "hx711.h"

/*----------------------------------------------------------------------------*/
/* Configure xxxx                                                             */
/*----------------------------------------------------------------------------*/
#define HX711_1_SCK_H()   GPIO_WriteBit(TC2_Port, TC2_Pin, Bit_SET)
#define HX711_1_SCK_L()   GPIO_WriteBit(TC2_Port, TC2_Pin, Bit_RESET)
#define HX711_1_OUT_H()   GPIO_WriteBit(TC1_Port, TC1_Pin, Bit_SET)
#define HX711_1_OUT_L()   GPIO_WriteBit(TC1_Port, TC1_Pin, Bit_RESET)
#define HX711_1_OUT_R()   GPIO_ReadInputDataBit(TC1_Port, TC1_Pin)

#define HX711_2_SCK_H()   GPIO_WriteBit(TC6_Port, TC6_Pin, Bit_SET)
#define HX711_2_SCK_L()   GPIO_WriteBit(TC6_Port, TC6_Pin, Bit_RESET)
#define HX711_2_OUT_H()   GPIO_WriteBit(TC5_Port, TC5_Pin, Bit_SET)
#define HX711_2_OUT_L()   GPIO_WriteBit(TC5_Port, TC5_Pin, Bit_RESET)
#define HX711_2_OUT_R()   GPIO_ReadInputDataBit(TC5_Port, TC5_Pin)

#define HX711_3_SCK_H()   GPIO_WriteBit(TC14_Port, TC14_Pin, Bit_SET)
#define HX711_3_SCK_L()   GPIO_WriteBit(TC14_Port, TC14_Pin, Bit_RESET)
#define HX711_3_OUT_H()   GPIO_WriteBit(TC15_Port, TC15_Pin, Bit_SET)
#define HX711_3_OUT_L()   GPIO_WriteBit(TC15_Port, TC15_Pin, Bit_RESET)
#define HX711_3_OUT_R()   GPIO_ReadInputDataBit(TC15_Port, TC15_Pin)

#define HX711_4_SCK_H()   GPIO_WriteBit(TC12_Port, TC12_Pin, Bit_SET)
#define HX711_4_SCK_L()   GPIO_WriteBit(TC12_Port, TC12_Pin, Bit_RESET)
#define HX711_4_OUT_H()   GPIO_WriteBit(TC11_Port, TC11_Pin, Bit_SET)
#define HX711_4_OUT_L()   GPIO_WriteBit(TC11_Port, TC11_Pin, Bit_RESET)
#define HX711_4_OUT_R()   GPIO_ReadInputDataBit(TC11_Port, TC11_Pin)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u32 hx711_value_fifo[4][9] = {0};
u8 hx711_1_fifo_index = 0;

u32 get_hx711_1_value(void) 
{
  u32 value = 0;
  u16 count = 0;

  // HX711_1_OUT_H();
  delay_us(10);
  HX711_1_SCK_L();
  while (HX711_1_OUT_R());
  /* 25位 增益128 */
  for (count = 0; count < 24; count++)
  {
    HX711_1_SCK_H();
    delay_us(5);
    HX711_1_SCK_L();
    if (HX711_1_OUT_R())
      value |= 1;
    value = value << 1;
  }
  HX711_1_SCK_H();
  value = value ^ 0x800000; //第25个脉冲下降沿来时，转换数据
  delay_us(10);
  HX711_1_SCK_L();

  if (value & 0x800000)
  {
    value &= 0x7FFFFF;
  }
  else
  {
    value = 0;
  }

  return value;
}

/**
 * @brief Get the hx711 2 value object
 * 
 * @return u32 
 */
u32 get_hx711_2_value(void)
{
  u32 value = 0;
  u16 count = 0;

  // HX711_2_OUT_H();
  delay_us(10);
  HX711_2_SCK_L();

  while (HX711_2_OUT_R());

  /* 25位 增益128 */
  for (count = 0; count < 24; count++)
  {
    HX711_2_SCK_H();
    delay_us(5);
    HX711_2_SCK_L();

    if (HX711_2_OUT_R())
      value |= 1;

    value = value << 1;
  }
  HX711_2_SCK_H();
  value = value ^ 0x800000;
  delay_us(10);
  HX711_2_SCK_L();

  if (value & 0x800000)
  {
    value &= 0x7FFFFF;
  }
  else
  {
    value = 0;
  }

  return value;
}

/**
 * @brief Get the hx711 3 value object
 * 
 * @return u32 
 */
u32 get_hx711_3_value(void)
{
  u32 value = 0;
  u16 count = 0;

  // HX711_3_OUT_H();
  delay_us(10);
  HX711_3_SCK_L();
  while (HX711_3_OUT_R());
  for (count = 0; count < 24; count++)
  {
    HX711_3_SCK_H();
    delay_us(5);
    HX711_3_SCK_L();
    if (HX711_3_OUT_R())
      value |= 1;
    value = value << 1;
  }
  HX711_3_SCK_H();
  value = value ^ 0x800000;
  delay_us(10);
  HX711_3_SCK_L();

  if (value & 0x800000)
  {
    value &= 0x7FFFFF;
  }
  else
  {
    value = 0;
  }

  return value;
}

/**
 * @brief Get the hx711 4 value object
 * 
 * @return u32 
 */
u32 get_hx711_4_value(void)
{
  u32 value = 0;
  u16 count = 0;

  // HX711_4_OUT_H();
  delay_us(10);
  HX711_4_SCK_L();
  while (HX711_4_OUT_R());
  for (count = 0; count < 24; count++)
  {
    HX711_4_SCK_H();
    delay_us(5);
    HX711_4_SCK_L();
    if (HX711_4_OUT_R())
      value |= 1;
    value = value << 1;
  }
  HX711_4_SCK_H();
  value = value ^ 0x800000;
  delay_us(10);
  HX711_4_SCK_L();

  if (value & 0x800000)
  {
    value &= 0x7FFFFF;
  }
  else
  {
    value = 0;
  }

  return value;
}







/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
