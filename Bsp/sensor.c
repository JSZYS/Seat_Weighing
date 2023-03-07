/**
 ******************************************************************************
 * @file    sensor.c
 * @brief
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 oogrow.
 * All rights reserved.
 *
 ******************************************************************************
 */

/*----------------------------------------------------------------------------*/
/* Configure sensor                                                           */
/*----------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "sensor.h"
#include "pin.h"
#include "adc.h"
#include "store.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DEBUG_SENSOR 1
#define ADC_LOWEST_VALUE 100

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
const u8 x_axis_list[X_AXIS_NUM] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
const u8 y_axis_list[Y_AXIS_NUM] = {0, 1, 2, 3};

/**
 * @brief adc_input 接 GND 控制
 *
 */
static void ad_input_gnd_on(void)
{
  GPIO_WriteBit(ADC_Rst_Port, ADC_Rst_Pin, Bit_RESET);
}

static void ad_input_gnd_off(void)
{
  GPIO_WriteBit(ADC_Rst_Port, ADC_Rst_Pin, Bit_SET);
}

/**
 * @brief cd 电源控制
 *
 */
static void adc_power_on(void)
{
  GPIO_WriteBit(ADC_Power_Port, ADC_Power_Pin, Bit_RESET);
}

static void adc_power_off(void)
{
  GPIO_WriteBit(ADC_Power_Port, ADC_Power_Pin, Bit_SET);
}

/**
 * @brief y 通道控制
 *
 * @param _ch
 */
static void tc_y_control(uint8_t _ch)
{
  GPIO_WriteBit(TC1_Port, TC1_Pin, (0 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC2_Port, TC2_Pin, (1 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC3_Port, TC3_Pin, (2 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC4_Port, TC4_Pin, (3 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC5_Port, TC5_Pin, (4 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC6_Port, TC6_Pin, (5 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC7_Port, TC7_Pin, (6 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC8_Port, TC8_Pin, (7 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC9_Port, TC9_Pin, (8 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC10_Port, TC10_Pin, (9 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC11_Port, TC11_Pin, (10 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC12_Port, TC12_Pin, (11 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC13_Port, TC13_Pin, (12 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC14_Port, TC14_Pin, (13 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC15_Port, TC15_Pin, (14 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC16_Port, TC16_Pin, (15 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC17_Port, TC16_Pin, (16 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC18_Port, TC16_Pin, (17 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC19_Port, TC16_Pin, (18 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC20_Port, TC16_Pin, (19 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC21_Port, TC16_Pin, (20 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC22_Port, TC16_Pin, (21 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC23_Port, TC16_Pin, (22 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC24_Port, TC16_Pin, (23 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC25_Port, TC16_Pin, (24 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC26_Port, TC16_Pin, (25 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC27_Port, TC16_Pin, (26 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC28_Port, TC16_Pin, (27 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC29_Port, TC16_Pin, (28 == _ch) ? Bit_RESET : Bit_SET);
  GPIO_WriteBit(TC30_Port, TC16_Pin, (29 == _ch) ? Bit_RESET : Bit_SET);
}

/**
 * @brief x-axis 选择
 *
 * @param _x_axis
 */
static void cd_select_x_channel(uint8_t _x_axis)
{
  u8 channel = 0;

  if (_x_axis < 16)
  {
    channel = _x_axis;
    GPIO_WriteBit(CD74HC_EX1_Port, CD74HC_EX1_Pin, Bit_RESET);
    GPIO_WriteBit(CD74HC_EX2_Port, CD74HC_EX2_Pin, Bit_SET);
  }
  else
  {
    channel = _x_axis % 16;
    GPIO_WriteBit(CD74HC_EX1_Port, CD74HC_EX1_Pin, Bit_SET);
    GPIO_WriteBit(CD74HC_EX2_Port, CD74HC_EX2_Pin, Bit_RESET);
  }

  GPIO_WriteBit(CD74HC_SX0_Port, CD74HC_SX0_Pin, (channel & 0x01) ? Bit_SET : Bit_RESET);
  GPIO_WriteBit(CD74HC_SX1_Port, CD74HC_SX1_Pin, (channel & 0x02) >> 1 ? Bit_SET : Bit_RESET);
  GPIO_WriteBit(CD74HC_SX2_Port, CD74HC_SX2_Pin, (channel & 0x04) >> 2 ? Bit_SET : Bit_RESET);
  GPIO_WriteBit(CD74HC_SX3_Port, CD74HC_SX3_Pin, (channel & 0x08) >> 3 ? Bit_SET : Bit_RESET);
}

/**
 * @brief y-axis 选择
 *
 * @param _y_axis
 */
static void cd_select_y_channel(uint8_t _y_axis)
{
  u8 channel = 0;

  if (_y_axis < 16)
  {
    channel = _y_axis;
    GPIO_WriteBit(CD74HC_EY1_Port, CD74HC_EY1_Pin, Bit_RESET);
    GPIO_WriteBit(CD74HC_EY2_Port, CD74HC_EY2_Pin, Bit_SET);
  }
  else
  {
    channel = _y_axis % 16;
    GPIO_WriteBit(CD74HC_EY1_Port, CD74HC_EY1_Pin, Bit_SET);
    GPIO_WriteBit(CD74HC_EY2_Port, CD74HC_EY2_Pin, Bit_RESET);
  }

  GPIO_WriteBit(CD74HC_SY0_Port, CD74HC_SY0_Pin, (channel & 0x01) ? Bit_SET : Bit_RESET);
  GPIO_WriteBit(CD74HC_SY1_Port, CD74HC_SY1_Pin, (channel & 0x02) >> 1 ? Bit_SET : Bit_RESET);
  GPIO_WriteBit(CD74HC_SY2_Port, CD74HC_SY2_Pin, (channel & 0x04) >> 2 ? Bit_SET : Bit_RESET);
  GPIO_WriteBit(CD74HC_SY3_Port, CD74HC_SY3_Pin, (channel & 0x08) >> 3 ? Bit_SET : Bit_RESET);
  tc_y_control(_y_axis);
}

/**
 * @brief 获取传感器所有点 ADC数据
 *
 */
void sensor_get_adc(void)
{
  u8 x = 0;
  u8 y = 0;
  u8 index = 0;
  u16 temp = 0;

  ADC_Cmd(ADC1, ENABLE);
  adc_power_on();
  delay_ms(5);
  for (x = 0; x < X_AXIS_NUM; x++)
  {
    cd_select_x_channel(x_axis_list[x]);
    for (y = 0; y < Y_AXIS_NUM; y++)
    {
      cd_select_y_channel(y_axis_list[y]);
      ad_input_gnd_off();
      delay_us(10);
      ad_input_gnd_on();
      delay_us(20);

      temp = get_adc_average(ADC_Channel_1, 2); // ad值
      if (temp <= ADC_LOWEST_VALUE)
      {
        sensor_ad_buf[index] = 0;
      }
      else
      {
        // sensor_ad_buf[i] = ((40950 / (float)temp) - 10 + 0.005) * 100;
        sensor_ad_buf[index] = temp;
      }
      index++;
    }
  }
  adc_power_off();
  ADC_Cmd(ADC1, DISABLE);
}

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
