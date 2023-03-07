
一、工程说明：
  1、创建时间：2022年10月12
  2、开发环境：MDK-ARM V5.33.0.0
  3、工程版本：V1.0.0
  4、目标芯片：STM32F103RCTC

二、下载注意事项：

三、实现功能概述
  1、读取四个压力传感器的adc值，转换成体重，单位 Kg, 保留两位小数。
  2、CAN 通信，100ms间隔发送数据，两字节，顶点两位小数。

四、程序设计

五、通信协议
1、CAN 通信，波特率 500k, 只发送数据给客户端，使用标准帧。
2、通信间隔 100ms，控制器内不需要接120Ω终端电阻。
3、发送数据格式：
  Msg ID  Length   Data   CRC
  0x30C     2       2B    2B
  2B 数据：
  2B 重量数据，无符号整型，顶点两位小数

六、传感器
  总共四个传感器：
            量程         系数         SCK     OUT
  传感器1： 300 Kg    1.6524 mv/v     TC6      TC5
  传感器2： 300 Kg    1.7418 mv/v     TC2      TC1
  传感器3： 300 Kg    1.7064 mv/v     TC14     TC15
  传感器4： 500 Kg    1.7715 mv/v     TC12      TC11

  HX711 模块:
  R1=20K; R2=8.2K; VBG=1.265V
  VAVDD=VBG(R1+R2)/R2=1.265*(20+8.2)/8.2=4.350365853 = 4.35
  (为了降低功耗，该电压只在采样时刻才有输出， 因此用万用表读取的值可能低于 4.35v ，因为万用表测量的是有效值。)

  传感器1：
  在VAVDD=4.35V 供电下，300kg最大输出电压是 4.35 * 1.65=24 mv/v = 7.18794mv
  经过128倍放大后，最大电压为：7.18794mv * 128 = 920.05632 mv = 920.06mv
  经过 AD 转换后输出的24bit数字值最大为：920.06mv * 0xffffff / 4350 = 3548516       16777215

16777216




  // do
  // {
  //   if (!HX711_1_OUT_R())
  //   {
  //     break;
  //   }
  //   count++;
  // } while (count < 0xff00);

  // if (count >= 0xff00)
  // {
  //   return 0; /* time out */
  // }


  // hx711_value_fifo[0][8] = hx711_value_fifo[0][8] - hx711_value_fifo[0][hx711_1_fifo_index] + value;
  // hx711_value_fifo[0][hx711_1_fifo_index] = value;
  // hx711_1_fifo_index = (hx711_1_fifo_index + 1) % 8;

  // return (hx711_value_fifo[0][8] >> 3);


      if (hx711_adc[0] != 0)
      {
        hx711_weigh[0] = ((float)(hx711_adc[0] + 24486)) / 19.43030f + 1.5;
      }
      if (hx711_adc[1] != 0)
      {
        hx711_weigh[1] = ((float)(hx711_adc[1] + 3915)) / 25.92766f;
      }
      if (hx711_adc[2] > 41794)
      {
        hx711_weigh[2] = ((float)(hx711_adc[2] - 41794)) / 25.97048f;
      }
      if (hx711_adc[3] != 0)
      {
        hx711_weigh[3] = ((float)(hx711_adc[3] + 2540)) / 25.185042f;
      }
/******* Copyright (C)2022 zint. All Rights Reserved ******* END OF FILE *******/
