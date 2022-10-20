/**
  ******************************************************************************
  * @file    /UserApp/user_main.c 
  * @author  oogrow
  * @version V1.0.0
  * @date    2022-09-01
  * @brief   user main program body
  ******************************************************************************
  * @attention
  * STM32F103RCT6
  * LQFP64
  * Flash 256kbByte
  * RAM 48kByte
  * IO 37
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "common_inc.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/
/**
  * @brief  User Main program.
  * @param  None
  * @retval None
  */
void user_main(void)
{
  u32 hx711_adc[4] = {0};
  u16 hx711_weigh[4] = {0};
  u16 total_weight = 0;
  u16 last_total_weight = 0;

  // float temp16 = 0;

  // pritf_sys_info();

  /* Infinite loop */
  for (;;)
  {
    if (sys_tim_tick > 20) /* 2 * 20 = 40ms */
    {
      sys_tim_tick = 0;

      hx711_adc[0] = get_hx711_1_value();
      hx711_adc[1] = get_hx711_2_value();
      hx711_adc[2] = get_hx711_3_value();
      hx711_adc[3] = get_hx711_4_value();
    }

    if (sys_com_tick > 50) /* 100ms */
    {
      hx711_weigh[0] = 0;
      hx711_weigh[1] = 0;
      hx711_weigh[2] = 0;
      hx711_weigh[3] = 0;

      if (hx711_adc[0] != 0)
      {
        // hx711_weigh[0] = ((float)(hx711_adc[0] + 24486)) / 19.43f + 920;
        hx711_weigh[0] = ((float)(hx711_adc[0] + 68688)) / 23.75f;
      }
      if (hx711_adc[1] != 0)
      {
        // hx711_weigh[1] = ((float)(hx711_adc[1] + 3915)) / 25.93f;
        hx711_weigh[1] = ((float)(hx711_adc[1] + 12700)) / 26.12f;
      }
      if (hx711_adc[2] > 41794)
      {
        // hx711_weigh[2] = ((float)(hx711_adc[2] - 41794)) / 25.22f;
        hx711_weigh[2] = ((float)(hx711_adc[2] + 32486)) / 32.42f;
      }
      if (hx711_adc[3] != 0)
      {
        // hx711_weigh[3] = ((float)(hx711_adc[3] + 2540)) / 25.18f;
        hx711_weigh[3] = ((float)(hx711_adc[3] + 23488)) / 14.98f;
      }

      // // 单位是 g
      // if (hx711_adc[0] != 0)
      // {
      //   hx711_weigh[0] = (float)hx711_adc[0] / 15.14f + 0.05;
      // }
      // if (hx711_adc[1] != 0)
      // {
      //   hx711_weigh[1] = (float)hx711_adc[1] / 15.96f + 0.05;
      // }
      // if (hx711_adc[2] > 0)
      // {
      //   hx711_weigh[2] = (float)hx711_adc[2] / 15.64f + 0.05 - 2630;
      // }
      // if (hx711_adc[3] != 0)
      // {
      //   hx711_weigh[3] = (float)hx711_adc[3] / 16.23f + 0.05;
      // }

      total_weight = (hx711_weigh[0] + hx711_weigh[1] + hx711_weigh[2] + hx711_weigh[3]) / 10;

      if (total_weight > last_total_weight)
      {
        if ((total_weight - last_total_weight) > 5)
        {
          last_total_weight = total_weight;
        }
      }
      else
      {
        if ((last_total_weight - total_weight) > 5)
        {
          last_total_weight = total_weight;
        }
      }
      
      /**
       * last_total_weight
       * 单位为kg，定点两位小数，变化超过0.05kg才改变，
       * 
       */
      can_send_state_buf[0] = last_total_weight >> 8;
      can_send_state_buf[1] = (u8)last_total_weight;
      can_send_msg(can_send_state_buf, 2);
      sys_com_tick = 0;

    #if 0
      printf("\n HX711 adc and weight. \n");
      printf("\n1 adc: %10u  weight: %u\n", hx711_adc[0], hx711_weigh[0]);
      printf("\n2 adc: %10u  weight: %u\n", hx711_adc[1], hx711_weigh[1]);
      printf("\n3 adc: %10u  weight: %u\n", hx711_adc[2], hx711_weigh[2]);
      printf("\n4 adc: %10u  weight: %u\n", hx711_adc[3], hx711_weigh[3]);
      temp16 = (float)last_total_weight / 100;
      printf("\n---- total weight (kg): %5.2f can msg: %u -----------\n", (temp16 - 0.65), last_total_weight);
    #endif
    }
  }
}

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
