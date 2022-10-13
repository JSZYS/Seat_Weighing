/**
 ******************************************************************************
 * @file    xxxx.h
 * @brief
 ******************************************************************************
 * @attention
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM_FLASH_H__
#define __STM_FLASH_H__

/* Includes ------------------------------------------------------------------*/
#include "sit_handle.h"
#include "common_inc.h"

/* Defines -------------------------------------------------------------------*/
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 256 // 所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1   // 使能FLASH写入(0，不是能;1，使能)

#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE 1024 // byte
#else
  #define STM_SECTOR_SIZE 2048
#endif

#define STM32_FLASH_APP_MAX_SIZE (61 * STM_SECTOR_SIZE) // appFLASH空间

#define STM32_FLASH_BASE 0x08000000        // STM32 FLASH的起始地址 bootloader size: 6k
#define STM32_FLASH_APP1 0x08001800        // STM32 FLASH的APP1地址 size: 122k 0x1E800
#define STM32_FLASH_APP2 0x08020000        // STM32 FLASH的APP2地址 size: 122k
#define STM32_FLASH_UPDATE_FLAG 0x0803E800 // STM32 FLASH的升级设置参数地址 size: 4k
#define STM32_FLASH_PARAM 0x0803F800       // STM32 FLASH的参数保存地址 size: 2k

/* Prototypes-----------------------------------------------------------------*/

u16 stm_flash_read_half_word(u32 faddr);
void stm_flash_write(u32 _addr, u8 *_data, u32 _size);
void stm_flash_read(u32 _addr, u8 *_data, u32 _size);
void stm_flash_erase_page(u32 _addr, u32 _size);

void read_flash_param(void);
void save_flash_param(void);

#endif /* __STM_FLASH_H__ */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
