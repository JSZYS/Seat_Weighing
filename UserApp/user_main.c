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

/*************************************
*函数名：user_main
*描述：用户功能主函数
*参数：null
*返回值：null
**************************************/
void user_main(void)
{
    u32 hx711_adc1[4] = {0};
    u32 hx711_adc2[4] = {0};
    float hx711_weigh1[4] = {0};//压力
    float hx711_weigh2[4] = {0};//拉力
    u32 total_weight = 0;
    u32 last_total_weight = 0;
//    u32 add_weigh[4] = {0};
    static u8 check_adc_flag = 0;

//    float temp16 = 0;

    // pritf_sys_info();

    /* Infinite loop */
    for (;;)
    {
#if 0
        if (sys_tim_tick > 20) /* 2 * 20 = 40ms */
#else
        if (check_adc_flag)
#endif
        {
            sys_tim_tick = 0;
            check_adc_flag = 0;

            hx711_adc1[0] = get_hx711_1_value(&hx711_adc2[0]);
            hx711_adc1[1] = get_hx711_2_value(&hx711_adc2[1]);
            hx711_adc1[2] = get_hx711_3_value(&hx711_adc2[2]);
            hx711_adc1[3] = get_hx711_4_value(&hx711_adc2[3]);
        }

        if (sys_com_tick > 50) /* 100ms */
        {
            check_adc_flag = 1;

            hx711_weigh1[0] = 0;
            hx711_weigh1[1] = 0;
            hx711_weigh1[2] = 0;
            hx711_weigh1[3] = 0;
            hx711_weigh2[0] = 0;
            hx711_weigh2[1] = 0;
            hx711_weigh2[2] = 0;
            hx711_weigh2[3] = 0;


            if (hx711_adc1[0] > 105876)
            {
                // hx711_weigh[0] = ((float)(hx711_adc[0] + 24486)) / 19.43f + 920;
                // hx711_weigh[0] = ((float)(hx711_adc[0] + 68688)) / 23.75f;
                //hx711_weigh[0] = ((float)(hx711_adc[0] + 59572)) / 23.88f;
                //hx711_weigh[0] = ((float)(3696520 - hx711_adc[0])) / 2522.10259f;
                //hx711_weigh[0] = ((float)(hx711_adc[0]) - 48151.08014f) / 18083.25416f;
                //hx711_weigh[0] = ((float)(hx711_adc[0]) - 241250.4382f) / 30119.11213f;
                hx711_weigh1[0] = ((float)(hx711_adc1[0]) - 105876.99462f) / 18077.63917f;
            }
            else
            {
                hx711_weigh2[0] = (105876.99462f - (float)(hx711_adc1[0])) / 18077.63917f;
                if (hx711_adc2[0] > 0)
                {
                    hx711_weigh2[0] += ((float)(hx711_adc2[0]) * 4 + 105876.99462f) / 18077.63917f;
                }
            }

            if (hx711_adc1[1] > 48358)
            {
                // hx711_weigh[1] = ((float)(hx711_adc[1] + 3915)) / 25.93f;
                // hx711_weigh[1] = ((float)(hx711_adc[1] + 12700)) / 26.12f;
                //hx711_weigh[1] = ((float)(hx711_adc[1] + 34251)) / 30.39f;
                hx711_weigh1[1] = ((float)(hx711_adc1[1]) - 48358.69793f) / 17711.3361f;
            }
            else
            {
                hx711_weigh2[1] = (48358.69793f - (float)(hx711_adc1[1])) / 17711.3361f;
                if (hx711_adc2[1] > 0)
                {
                    hx711_weigh2[1] += ((float)(hx711_adc2[1]) * 4 + 48358.69793f) / 17711.3361f;
                }
            }

            if (hx711_adc1[2] > 132594)
            {
                // hx711_weigh[2] = ((float)(hx711_adc[2] - 41794)) / 25.22f;
                // hx711_weigh[2] = ((float)(hx711_adc[2] + 32486)) / 32.42f;
                //hx711_weigh[2] = ((float)(hx711_adc[2] - 15819)) / 27.29f;
                hx711_weigh1[2] = ((float)(hx711_adc1[2]) - 132594.59751f) / 19751.20332f;
            }
            else
            {
                hx711_weigh2[2] = (132594.59751f - (float)(hx711_adc1[2])) / 19751.20332f;
                if (hx711_adc2[2] > 0)
                {
                    hx711_weigh2[2] += ((float)(hx711_adc2[2]) * 4 + 132594.59751f) / 19751.20332f;
                }
            }

            if (hx711_adc1[3] > 117180)
            {
                // hx711_weigh[3] = ((float)(hx711_adc[3] + 2540)) / 25.18f;
                // hx711_weigh[3] = ((float)(hx711_adc[3] + 23488)) / 14.98f;
                //hx711_weigh[3] = ((float)(hx711_adc[3] + 7592)) / 15.80f;
                //add_weigh[3] = (hx711_weigh[3] - 118694) / 0.369f;
                //hx711_weigh[3] = ((float)(hx711_adc[3] - 1876260)) / 5466.05f;
                //hx711_weigh[3] = ((float)(hx711_adc[3] - 1876270)) / 5464.48f;
                hx711_weigh1[3] = ((float)(hx711_adc1[3] - 112822.98985f)) / 15384.56719f;
            }
            else
            {
                hx711_weigh2[3] = (112822.98985f - (float)(hx711_adc1[3])) / 15384.56719f;
                if (hx711_adc2[3] > 0)
                {
                    hx711_weigh2[3] += ((float)(hx711_adc2[3]) * 4 + 112822.98985f) / 15384.56719f;
                }
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

            total_weight = (hx711_weigh1[0] + hx711_weigh1[1] + hx711_weigh1[2] + hx711_weigh1[3])
                           - (hx711_weigh2[0] + hx711_weigh2[1] + hx711_weigh2[2] + hx711_weigh2[3]);

#if 0
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
#else
            last_total_weight = total_weight;
#endif
            /**
             * last_total_weight
             * 单位为kg，定点两位小数，变化超过0.05kg才改变，
             *
             */
#if 0
            can_send_state_buf[0] = last_total_weight >> 8;
            can_send_state_buf[1] = (u8)last_total_weight;
            can_send_msg(can_send_state_buf, 2);
#else
           // can_send_state_buf[0] = last_total_weight;
           can_send_state_buf[1] = last_total_weight;
            if (last_total_weight > 79) //减去座椅本身重量79kg
            {
                can_send_state_buf[0] = last_total_weight - 79;
								if(can_send_state_buf[0] <= 40)
								{
									
									can_send_state_buf[0] = (float)can_send_state_buf[0] * (float)1.25;
								}
								else if(can_send_state_buf[0] > 40 && can_send_state_buf[0] < 100)
								{
									can_send_state_buf[0] = (float)can_send_state_buf[0] * ((float)1.25 - (float)0.15 / 60 * ((float)can_send_state_buf[0] - 40));
								}
								else
								{
									can_send_state_buf[0] = (float)can_send_state_buf[0] * (float)1.10;
								}
            }
            else
            {
                can_send_state_buf[0] = 0;
            }
            can_send_msg(can_send_state_buf, 8);
#endif
            sys_com_tick = 0;

#if 1
            printf("\r\n HX711 adc and weight. \r\n");
            printf("\r\n1 adc1: %10u  adc2: %10u  pressure: %f  pulling force: %f\r\n", hx711_adc1[0], hx711_adc2[0], hx711_weigh1[0], hx711_weigh2[0]);
            printf("\r\n2 adc1: %10u  adc2: %10u  pressure: %f  pulling force: %f\r\n", hx711_adc1[1], hx711_adc2[1], hx711_weigh1[1], hx711_weigh2[1]);
            printf("\r\n3 adc1: %10u  adc2: %10u  pressure: %f  pulling force: %f\r\n", hx711_adc1[2], hx711_adc2[2], hx711_weigh1[2], hx711_weigh2[2]);
            printf("\r\n4 adc1: %10u  adc2: %10u  pressure: %f  pulling force: %f\r\n", hx711_adc1[3], hx711_adc2[3], hx711_weigh1[3], hx711_weigh2[3]);
            printf("\r\n---- total weight (kg): %u -----------\r\n", last_total_weight);
#endif
        }
    }
}

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
