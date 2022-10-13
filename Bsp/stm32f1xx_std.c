/**
 ******************************************************************************
 * @file    user_it.c
 * @brief
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_std_def.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static u8 fac_us = 0;  // us��ʱ������
static u16 fac_ms = 0; // ms��ʱ������

void SysTick_Init(u8 SYSCLK)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
  fac_us = SYSCLK / 8;
  fac_ms = (u16)fac_us * 1000;
}

//��ʱnus
// nusΪҪ��ʱ��us��.
void delay_us(uint32_t nus)
{
  uint32_t temp;
  SysTick->LOAD = nus * fac_us;             //ʱ�����
  SysTick->VAL = 0x00;                      //��ռ�����
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //��ʼ����
  do
  {
    temp = SysTick->CTRL;
  } while ((temp & 0x01) && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //�رռ�����
  SysTick->VAL = 0X00;                            //��ռ�����
}

// ��ʱnms
// ע��nms�ķ�Χ
// SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
// nms<=0xffffff*8*1000/SYSCLK
// SYSCLK��λΪHz,nms��λΪms
// ��72M������,nms<=1864
void delay_ms(u16 nms)
{
  uint32_t temp;
  SysTick->LOAD = (uint32_t)nms * fac_ms;   //ʱ�����(SysTick->LOADΪ24bit)
  SysTick->VAL = 0x00;                      //��ռ�����
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //��ʼ����
  do
  {
    temp = SysTick->CTRL;
  } while ((temp & 0x01) && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //�رռ�����
  SysTick->VAL = 0X00;                            //��ռ�����
}

/**
 * @brief ϵͳ�����λ
 * 
 */
void sys_soft_reset(void)
{
  __set_FAULTMASK(1); //�ر������ж�
  NVIC_SystemReset(); //��λ
}

// u32 get_times(void)
// {
// 	return sys_tim1s_tick;
// }

// void set_times(u32 _tick)
// {
// 	sys_tim1s_tick = _tick;
// }
/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
