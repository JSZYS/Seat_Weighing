/**
 ******************************************************************************
 * @file    sit_handle.c
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
#include "sit_handle.h"
#include "NV040DS.h"
#include "sensor.h"

/*----------------------------------------------------------------------------*/
/* Configure xxxx                                                             */
/*----------------------------------------------------------------------------*/

#define NOT_SIT_VALUE 30 //以下的值需要修改

/**
 * @brief 坐姿判断
 *
 * @param sit_data
 * @return sit_state_enum
 */
sit_state_enum sit_state_handle(void)
{
  u8 x = 0;
  u8 y = 0;
  u8 i = 0;
  // u8 temp = 0;
  u16 ad_axis_base = 0;
  u16 sit_buf[64];

  u16 effective_sig_count = 0;
  u16 left_sum = 0;   /* 左边四列 */
  u16 right_sum = 0;  /* 右边四列 */
  u16 front_sum = 0;  /* 前四行 */
  u16 after_sum = 0;  /* 后四行 */

  u16 left_front_sum = 0; /* 左边前三行 */
  u16 right_front_sum = 0;/* 右边前三行 */
  u16 left_after_sum = 0; /* 左边后五行 */
  u16 right_after_sum = 0;/* 右边后五行 */

  u16 five_to_six_line_sum = 0;
  u16 seven_to_eight_line_sum = 0;

  for (y = 0; y < 8; y++)
  {
    for (x = 0; x < 8; x++)
    {
      ad_axis_base = y * 32 + x * 2;
      sit_buf[y * 8 + x] = (sensor_ad_buf[ad_axis_base] + sensor_ad_buf[ad_axis_base + 1] + sensor_ad_buf[ad_axis_base + 16] + sensor_ad_buf[ad_axis_base + 17]) >> 2;
    }
  }

  for (i = 0; i < 64; i++)
  {
    if (sit_buf[i] > NOT_SIT_VALUE)
    {
      effective_sig_count++;
    }
  }

  /* 调试数据 ***************************************************************/
  #if 0
  // if (effective_sig_count > 10)
  // {
    printf("\n-------------------- 16x16 dot adc value --------------------\n");
    for (i = 0; i < 16; i++)
    {
      temp = i * 16;
      printf("%4u,%4u,%4u,%4u,", sensor_ad_buf[temp + 0], sensor_ad_buf[temp + 1], sensor_ad_buf[temp + 2], sensor_ad_buf[temp + 3]);
      printf("%4u,%4u,%4u,%4u,", sensor_ad_buf[temp + 4], sensor_ad_buf[temp + 5], sensor_ad_buf[temp + 6], sensor_ad_buf[temp + 7]);
      printf("%4u,%4u,%4u,%4u,", sensor_ad_buf[temp + 8], sensor_ad_buf[temp + 9], sensor_ad_buf[temp + 10], sensor_ad_buf[temp + 11]);
      printf("%4u,%4u,%4u,%4u\n", sensor_ad_buf[temp + 12], sensor_ad_buf[temp + 13], sensor_ad_buf[temp + 14], sensor_ad_buf[temp + 15]);
    }

    printf("\n================= 16x16 to 8x8 dot adc value ================\n");
    for (i = 0; i < 8; i++)
    {
      temp = i * 8;
      printf("%4u,%4u,%4u,%4u,", sit_buf[temp + 0], sit_buf[temp + 1], sit_buf[temp + 2], sit_buf[temp + 3]);
      printf("%4u,%4u,%4u,%4u\n",  sit_buf[temp + 4], sit_buf[temp + 5], sit_buf[temp + 6], sit_buf[temp + 7]);
    }
    
  // }
  #endif

  if (effective_sig_count < 15)
  {
    return SIT_STATE_NOT;
  }
  /**********************************
    0   1   2	  3   4   5   6   7
    8   9   10  11  12  13  14  15
    16  17  18  19  20  21  22  23
    24  25  26  27  28  29  30  31
    32  33  34  35  36  37  38  39
    40  41  42  43  44  45  46  47
    48  49  50  51  52  53  54  55
    56  57  58  59  60  61  62  63
  **********************************/
  for (i = 0; i < 64; i++)
  {
    if (i % 8 <= 3)
    {
      left_sum += sit_buf[i];
      if (i <= 19)
      {
        left_front_sum += sit_buf[i];
      }
      else
      {
        left_after_sum += sit_buf[i];
      }
    }
    else
    {
      right_sum += sit_buf[i];
      if (i <= 23)
      {
        right_front_sum += sit_buf[i];
      }
      else
      {
        right_after_sum += sit_buf[i];
      }
    }

    if (i <= 23)
    {
      front_sum += sit_buf[i];
    }
    else
    {
      after_sum += sit_buf[i];
      if ((i >= 32) && (i <= 47))
      {
        five_to_six_line_sum += sit_buf[i];
      }
      else if ((i >= 48) && (i <= 63))
      {
        seven_to_eight_line_sum += sit_buf[i];
      }
    }
  }

  /* test */
  #if 0
  printf("\n left: %6u, right: %6u, front: %6u, after: %6u\n", left_sum, right_sum, front_sum, after_sum);
  printf("  l_f: %6u,   r_f: %6u,   l_a: %6u,   r_a: %6u\n", left_front_sum, right_front_sum, left_after_sum, right_after_sum);
  printf("lf/rf: %6.3f\n", (float)left_front_sum / (float)right_front_sum);
  printf("f_t_s: %6u, s_t_e: %6u,   eff: %u\n", five_to_six_line_sum, seven_to_eight_line_sum, effective_sig_count);
  printf("f_t_s/s_t_e: %6.3f, front/after: %6.3f\n", (float)five_to_six_line_sum / (float)seven_to_eight_line_sum, (float)front_sum / (float)after_sum);
  #endif

  /*************************** 坐姿判断 *************************/
  /* 左右二郎腿判断 */
  if (left_front_sum > right_front_sum)
  {
    /* 右翘二郎腿：将右脚翘到左脚上面 */
    if (right_front_sum < 100)
    {
      return SIT_STATE_RIGHT_LEG;
    }
    else if ((float)left_front_sum / (float)right_front_sum >= 10.0f)
    {
      return SIT_STATE_RIGHT_LEG;
    }
  }
  else
  {
    /* 左翘二郎腿：将左脚翘到右脚上面 */
    if (left_front_sum < 100)
    {
      return SIT_STATE_LEFT_LEG;
    }
    else if ((float)right_front_sum / (float)left_front_sum >= 10.0f)
    {
      return SIT_STATE_LEFT_LEG;
    }
  }

  /* 左右倾判断 */
  if (left_sum > right_sum)
  {
    /* 左倾 */
    if ((right_sum > 0) && ((float)left_sum / (float)right_sum) >= 2.20f)
    {
      return SIT_STATE_LEFT;
    }
  }
  else
  {
    /* 右倾 */
    if ((left_sum > 0) && ((float)right_sum / (float)left_sum) >= 2.20f)
    {
      return SIT_STATE_RIGHT;
    }
  }
  
  /* 前后倾判断 */
  // if (front_sum > after_sum)
  if (after_sum > front_sum)
  {
    /* 前倾 */
    if ((after_sum > 0) && ((float)front_sum / (float)after_sum) >= 0.50f)
    {
      return SIT_STATE_FRONT;
    }
  }
  
  /* 后躺 */
  if (five_to_six_line_sum > seven_to_eight_line_sum)
  {
    if ((seven_to_eight_line_sum > 0) && ((float)five_to_six_line_sum / (float)seven_to_eight_line_sum < 1.20f) && ((float)front_sum / (float)after_sum < 0.40f))
    {
      return SIT_STATE_AFTER;
    }
  }
  else
  {
    return SIT_STATE_AFTER;
  }
  
  /* 正坐 */
  return SIT_STATE_NORMAL;
}

/**
 * @brief 坐姿变化播报
 * 
 * @param _state 
 */
void sit_state_nvds(sit_state_enum _state)
{
  if (last_sit_state != sit_state)
  {
    // printf("last: %u, now: %u", last_sit_state, sit_state);
    last_sit_state = sit_state;
    switch (sit_state)
    {
    /* 正坐 */
    case SIT_STATE_NORMAL:
      nvds_run(0);
      break;
    /* 前坐 */
    case SIT_STATE_FRONT:
      nvds_run(1);
      break;
    /* 后坐 */
    case SIT_STATE_AFTER:
      nvds_run(2);
      break;
    /* 左翘二郎腿 */
    case SIT_STATE_LEFT_LEG:
      nvds_run(3);
      break;
    /* 右翘二郎腿 */
    case SIT_STATE_RIGHT_LEG:
      nvds_run(4);
      break;
    /* 左倾 */
    case SIT_STATE_LEFT:
      nvds_run(5);
      break;
    /* 右倾 */
    case SIT_STATE_RIGHT:
      nvds_run(6);
      break;
    /* 未坐 */
    case SIT_STATE_NOT:
      break;

    default:
      break;
    }
  }
}

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
