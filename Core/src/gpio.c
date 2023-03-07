/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

#define GPIO_NUMBER           16u

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void std_gpio_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    /* 下面这三个就是关闭SWJ等相关复用 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    /**************** Configure GPIOA pins *****************/
    // GPIO_InitStruct.GPIO_Pin = TC4_Pin | CD74HC_SY0_Pin | CD74HC_SY1_Pin | CD74HC_SY2_Pin | CD74HC_SY3_Pin |
    //                            TC24_Pin | TC25_Pin | TC29_Pin | ADC_Power_Pin | CAN_RS_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* adc */
    // GPIO_InitStruct.GPIO_Pin = ADC_In_Pin;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
    // GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* UART TX */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    /* UART RX */
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = TC15_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    /**************** Configure GPIOB pins *****************/
    // GPIO_InitStruct.GPIO_Pin = CD74HC_EX2_Pin | TC6_Pin | TC26_Pin | ADC_Rst_Pin | TC20_Pin | TC21_Pin |
    //                            TC22_Pin | TC23_Pin | TC7_Pin | TC8_Pin | TC9_Pin | TC10_Pin |  TC12_Pin;
    GPIO_InitStruct.GPIO_Pin = TC6_Pin | TC12_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = TC11_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN RX */
    GPIO_InitStruct.GPIO_Pin = CAN_RX_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    /* CAN TX */
    GPIO_InitStruct.GPIO_Pin = CAN_TX_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);

    /**************** Configure GPIOC pins *****************/
    // GPIO_InitStruct.GPIO_Pin = CD74HC_SX0_Pin | CD74HC_SX1_Pin | CD74HC_SX2_Pin | CD74HC_SX3_Pin |
    //                            CD74HC_EX1_Pin | TC13_Pin | TC14_Pin | CD74HC_EY2_Pin | CD74HC_EY1_Pin |
    //                            TC16_Pin | TC17_Pin | TC18_Pin | TC2_Pin | TC3_Pin;
    GPIO_InitStruct.GPIO_Pin = TC14_Pin | TC2_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = TC5_Pin | TC1_Pin;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStruct);

    /**************** Configure GPIOD pins *****************/
    // GPIO_InitStruct.GPIO_Pin = TC19_Pin;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    // GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Configure GPIO pin Output Level */
}

/**
  * @brief  Toggles the specified GPIO pin
  * @param  GPIOx: where x can be (A..G depending on device used) to select the GPIO peripheral
  * @param  GPIO_Pin: Specifies the pins to be toggled.
  * @retval None
  */
void std_gpio_toggle_pin(GPIO_TypeDef *GPIOx, u16 GPIO_Pin)
{
    u32 odr;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    assert_param(IS_GET_GPIO_PIN(GPIO_Pin));

    /* get current Ouput Data Register value */
    odr = GPIOx->ODR;

    /* Set selected pins that were at low level, and reset ones that were high */
    GPIOx->BSRR = ((odr & GPIO_Pin) << GPIO_NUMBER) | (~odr & GPIO_Pin);
}

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
