/**
  ******************************************************************************
  * @file    main.c
  * @author  oogrow
  * @version V1.0.0
  * @date    2022-08-10
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "adc.h"
#include "can.h"
#include "common_inc.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* 设置 NVIC 中断分组 2 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* 延迟函数初始化 */
    SysTick_Init(72);

    std_gpio_init();
#if UART_DEBUG
    std_usart2_uart_init();
#endif
    // std_adc_init();
    std_tim3_init();
    std_can_init();

    /* Infinite loop */
    user_main();
    while (1)
    {
    }
}

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
