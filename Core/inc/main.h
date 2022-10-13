/**
  ******************************************************************************
  * @file   : main.h
  * @brief  : 
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* USART2  debug */
#define DEBUG_TX_Port   GPIOA
#define DEBUT_TX_Pin    GPIO_Pin_2

#define DEBUG_RX_Port   GPIOA
#define DEBUT_RX_Pin    GPIO_Pin_3

/* ADC */
#define ADC_In_Port       GPIOA
#define ADC_In_Pin        GPIO_Pin_1

#define ADC_Rst_Port      GPIOB
#define ADC_Rst_Pin       GPIO_Pin_3

#define ADC_Power_Port    GPIOA
#define ADC_Power_Pin     GPIO_Pin_11

/* CAN */
#define CAN_RS_Port   GPIOA
#define CAN_RS_Pin    GPIO_Pin_15

#define CAN_RX_Port   GPIOB
#define CAN_RX_Pin    GPIO_Pin_8

#define CAN_TX_Port   GPIOB
#define CAN_TX_Pin    GPIO_Pin_9

/* x-axis  CD74HC4067 */
#define CD74HC_EX1_Port   GPIOC
#define CD74HC_EX1_Pin    GPIO_Pin_5

#define CD74HC_EX2_Port   GPIOB
#define CD74HC_EX2_Pin    GPIO_Pin_0

#define CD74HC_SX0_Port   GPIOC
#define CD74HC_SX0_Pin    GPIO_Pin_0

#define CD74HC_SX1_Port   GPIOC
#define CD74HC_SX1_Pin    GPIO_Pin_1

#define CD74HC_SX2_Port   GPIOC
#define CD74HC_SX2_Pin    GPIO_Pin_2

#define CD74HC_SX3_Port   GPIOC
#define CD74HC_SX3_Pin    GPIO_Pin_3

/* y-axis  CD74HC4067 */
#define CD74HC_EY1_Port   GPIOC
#define CD74HC_EY1_Pin    GPIO_Pin_9

#define CD74HC_EY2_Port   GPIOC
#define CD74HC_EY2_Pin    GPIO_Pin_8

#define CD74HC_SY0_Port   GPIOA
#define CD74HC_SY0_Pin    GPIO_Pin_4

#define CD74HC_SY1_Port   GPIOA
#define CD74HC_SY1_Pin    GPIO_Pin_5

#define CD74HC_SY2_Port   GPIOA
#define CD74HC_SY2_Pin    GPIO_Pin_6

#define CD74HC_SY3_Port   GPIOA
#define CD74HC_SY3_Pin    GPIO_Pin_7

/* y-axis power */
#define TC1_Port    GPIOC
#define TC1_Pin     GPIO_Pin_13

#define TC2_Port    GPIOC
#define TC2_Pin     GPIO_Pin_14

#define TC3_Port    GPIOC
#define TC3_Pin     GPIO_Pin_15

#define TC4_Port    GPIOA
#define TC4_Pin     GPIO_Pin_0

#define TC5_Port    GPIOC
#define TC5_Pin     GPIO_Pin_4

#define TC6_Port    GPIOB
#define TC6_Pin     GPIO_Pin_1

#define TC7_Port    GPIOB
#define TC7_Pin     GPIO_Pin_10

#define TC8_Port    GPIOB
#define TC8_Pin     GPIO_Pin_11

#define TC9_Port    GPIOB
#define TC9_Pin     GPIO_Pin_12

#define TC10_Port   GPIOB
#define TC10_Pin    GPIO_Pin_13

#define TC11_Port   GPIOB
#define TC11_Pin    GPIO_Pin_14

#define TC12_Port   GPIOB
#define TC12_Pin    GPIO_Pin_15

#define TC13_Port   GPIOC
#define TC13_Pin    GPIO_Pin_6

#define TC14_Port   GPIOC
#define TC14_Pin    GPIO_Pin_7

#define TC15_Port   GPIOA
#define TC15_Pin    GPIO_Pin_12

#define TC16_Port   GPIOC
#define TC16_Pin    GPIO_Pin_10

#define TC17_Port   GPIOC
#define TC17_Pin    GPIO_Pin_11

#define TC18_Port   GPIOC
#define TC18_Pin    GPIO_Pin_12

#define TC19_Port   GPIOD
#define TC19_Pin    GPIO_Pin_2

#define TC20_Port   GPIOB
#define TC20_Pin    GPIO_Pin_4

#define TC21_Port   GPIOB
#define TC21_Pin    GPIO_Pin_5

#define TC22_Port   GPIOB
#define TC22_Pin    GPIO_Pin_6

#define TC23_Port   GPIOB
#define TC23_Pin    GPIO_Pin_7

#define TC24_Port   GPIOA
#define TC24_Pin    GPIO_Pin_8

#define TC25_Port   GPIOA
#define TC25_Pin    GPIO_Pin_9

#define TC26_Port   GPIOB
#define TC26_Pin    GPIO_Pin_2

#define TC27_Port   GPIOA
#define TC27_Pin    GPIO_Pin_2

#define TC28_Port   GPIOA
#define TC28_Pin    GPIO_Pin_3

#define TC29_Port   GPIOA
#define TC29_Pin    GPIO_Pin_10

#define TC30_Port   GPIOA
#define TC30_Pin    GPIO_Pin_15

#endif /* __MAIN_H__ */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
