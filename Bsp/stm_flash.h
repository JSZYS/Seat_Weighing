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
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE 256 // ��ѡSTM32��FLASH������С(��λΪK)
#define STM32_FLASH_WREN 1   // ʹ��FLASHд��(0��������;1��ʹ��)

#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE 1024 // byte
#else
  #define STM_SECTOR_SIZE 2048
#endif

#define STM32_FLASH_APP_MAX_SIZE (61 * STM_SECTOR_SIZE) // appFLASH�ռ�

#define STM32_FLASH_BASE 0x08000000        // STM32 FLASH����ʼ��ַ bootloader size: 6k
#define STM32_FLASH_APP1 0x08001800        // STM32 FLASH��APP1��ַ size: 122k 0x1E800
#define STM32_FLASH_APP2 0x08020000        // STM32 FLASH��APP2��ַ size: 122k
#define STM32_FLASH_UPDATE_FLAG 0x0803E800 // STM32 FLASH���������ò�����ַ size: 4k
#define STM32_FLASH_PARAM 0x0803F800       // STM32 FLASH�Ĳ��������ַ size: 2k

/* Prototypes-----------------------------------------------------------------*/

u16 stm_flash_read_half_word(u32 faddr);
void stm_flash_write(u32 _addr, u8 *_data, u32 _size);
void stm_flash_read(u32 _addr, u8 *_data, u32 _size);
void stm_flash_erase_page(u32 _addr, u32 _size);

void read_flash_param(void);
void save_flash_param(void);

#endif /* __STM_FLASH_H__ */

/******************** (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
