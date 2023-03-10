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

static u8 fac_us = 0;  // us延时倍乘数
static u16 fac_ms = 0; // ms延时倍乘数

void SysTick_Init(u8 SYSCLK)
{
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
  fac_us = SYSCLK / 8;
  fac_ms = (u16)fac_us * 1000;
}

//延时nus
// nus为要延时的us数.
void delay_us(uint32_t nus)
{
  uint32_t temp;
  SysTick->LOAD = nus * fac_us;             //时间加载
  SysTick->VAL = 0x00;                      //清空计数器
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
  do
  {
    temp = SysTick->CTRL;
  } while ((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //关闭计数器
  SysTick->VAL = 0X00;                            //清空计数器
}

// 延时nms
// 注意nms的范围
// SysTick->LOAD为24位寄存器,所以,最大延时为:
// nms<=0xffffff*8*1000/SYSCLK
// SYSCLK单位为Hz,nms单位为ms
// 对72M条件下,nms<=1864
void delay_ms(u16 nms)
{
  uint32_t temp;
  SysTick->LOAD = (uint32_t)nms * fac_ms;   //时间加载(SysTick->LOAD为24bit)
  SysTick->VAL = 0x00;                      //清空计数器
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //开始倒数
  do
  {
    temp = SysTick->CTRL;
  } while ((temp & 0x01) && !(temp & (1 << 16))); //等待时间到达
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;      //关闭计数器
  SysTick->VAL = 0X00;                            //清空计数器
}

/**
 * @brief 系统软件复位
 * 
 */
void sys_soft_reset(void)
{
  __set_FAULTMASK(1); //关闭所有中断
  NVIC_SystemReset(); //复位
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
