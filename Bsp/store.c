/**
  ******************************************************************************
  * @file    store.c
<<<<<<< HEAD
  * @brief   
=======
  * @brief
>>>>>>> b7fe045 (新版本改为查表方式)
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 oogrow.
  * All rights reserved.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "store.h"

u8 sit_axis = 0;
u8 can_send_state_buf[8];
u32 sys_tim_tick = 0;
u32 sys_com_tick = 0;

<<<<<<< HEAD
u16 sensor_ad_buf[SENSOR_DATE_NUM] = {0};
u32 area_bit_state = 0;

=======
u32 Seat_Weight_Count =  0;
u8 Current_Seat_weight = 0;
u8 Last_Seat_weight = 76;
u8 Seat_weight = 76;

u16 sensor_ad_buf[SENSOR_DATE_NUM] = {0};
u32 area_bit_state = 0;

u32 Seat_Sum, Seat_num[5] = {76, 76, 76, 76, 76};
u8 Seat_Weight_list[70] = {37, 38, 39, 40, 41,         //31~35
                           42, 43, 44, 45, 46,         //36~40
                           47, 48, 49, 50, 51,         //41~45
                           54, 55, 56, 57, 58,         //46~50
                           59, 60, 61, 62, 63,         //51~55
                           64, 65, 66, 67, 68,         //56~60
                           69, 70, 71, 72, 73,         //61~65
                           77, 78, 79, 80, 81,         //66~70
                           82, 83, 84, 85, 86,          //71~75
                           87, 88, 89, 90, 91,          //76~80
                           92, 94, 96, 98, 100,         //81~85
                           102, 103, 104, 105, 106,     //86~90
                           108, 109, 110, 111, 112,     //91~95
                           113, 114, 115, 116, 118      //96~100
                          };


/**************************************************
    Functionn Name:int Abs(int num)
    Author: WL
    Version:    1.0
		Date:2023-03-20
		Description:    Output the absolute value of a number
		Input Parameters:   Enter an integer number
		Return Value:       Returns an absolute value
		Others:NULL
		Calling Functions:  NULL
		History:NULL
**************************************************/
int Abs(int num)
{
    if (num > 0)
    {
        return num;
    }
    else
    {
        return -num;
    }
}

/**************************************************
    Functionn Name:Weight_Filtering(u32 SeatWeight)
    Author: WL
    Version:    1.0
		Date:2023-03-20
		Description:    Weight sliding trial filtering
		Input Parameters:   Enter a 32-bit unsigned number
		Return Value:       NULL
		Others:NULL
		Calling Functions:  Abs()
		History:NULL
**************************************************/
void Weight_Filtering(u32 SeatWeight)
{
    u8 j;
    Current_Seat_weight = SeatWeight;
    if (Abs((int)Current_Seat_weight - (int)Last_Seat_weight) < 10)
    {
        if (Abs((int)Current_Seat_weight - (int)Last_Seat_weight) > 1)
        {
            for (j = 0; j <= 4; j++)
            {
                Seat_Sum +=  Seat_num[j];
            }
            Seat_weight = Seat_Sum / 5;
            Seat_num[Seat_Weight_Count] = Current_Seat_weight;
            Last_Seat_weight = Current_Seat_weight;
            Seat_Sum = 0;

            Seat_Weight_Count ++;
            if (Seat_Weight_Count > 4)
            {
                Seat_Weight_Count = 0;
            }


        }

    }
}


/**************************************************
    Functionn Name:void weight_Checklist()
    Author: WL
    Version:    1.0
		Date:2023-03-20
		Description:    Get the value of weight, look up the table; y = x -31
		Input Parameters:   NULL
		Return Value:       NULL
		Others:NULL
		Calling Functions:  NULL
		History:NULL
**************************************************/
void weight_Checklist()
{
    if (can_send_state_buf[0] <= 30)
    {
        can_send_state_buf[0] = (float)can_send_state_buf[0] * (float)1.25;
    }
    else if (can_send_state_buf[0] > 30 && can_send_state_buf[0] <= 100)
    {
        can_send_state_buf[0] = Seat_Weight_list[can_send_state_buf[0] - 31];
    }
    else
    {
        can_send_state_buf[0] = (float)can_send_state_buf[0] * (float)1.2;
    }
}






>>>>>>> b7fe045 (新版本改为查表方式)
/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
