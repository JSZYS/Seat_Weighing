/**
 ******************************************************************************
 * @file    stm_flash.c
 * @brief
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 oogrow.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm_flash.h"
#include "store.h"

/*----------------------------------------------------------------------------*/
/* Configure xxxx                                                             */
/*----------------------------------------------------------------------------*/


u16 stm_flash_read_half_word(u32 faddr)
{
  return *(vu16 *)faddr;
}

/**
 * @brief 写 flash 
 * 
 * @param _addr 
 * @param _data 
 * @param size 
 */
void stm_flash_write(u32 _addr, u8 *_data, u32 _size)
{
  u32 i = 0;
  u16 value = 0;
  _addr |= STM32_FLASH_BASE;

  if (_addr < STM32_FLASH_BASE || (_addr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
    return; //非法地址

  FLASH_Unlock(); //解锁

  for (i = 0; i < _size; i += 2)
  {
    if (i + 1 >= _size)
    {
      value = 0 | _data[i];
    }
    else
    {
      value = (_data[i + 1] << 8) | _data[i];
    }

    if (_addr % STM_SECTOR_SIZE == 0)
    {
      FLASH_ErasePage(_addr); //擦除这个扇区
    }

    FLASH_ProgramHalfWord(_addr, value);
    _addr += 2; //地址增加2.
  }

  FLASH_Lock(); //上锁
}

/**
 * @brief 读 flash
 * 
 * @param _addr 
 * @param _data 
 * @param size 
 */
void stm_flash_read(u32 _addr, u8 *_data, u32 _size)
{
  u32 i;
  u16 value = 0;
  _addr |= STM32_FLASH_BASE;

  if (_addr < STM32_FLASH_BASE || (_addr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
    return; //非法地址

  for (i = 0; i < _size; i += 2)
  {
    value = stm_flash_read_half_word(_addr); //读取2个字节.
    _data[i] = value & 0xFF;
    if (i + 1 < _size)
    {
      _data[i + 1] = (value & 0xFF00) >> 8;
    }
    _addr += 2; //偏移2个字节.
  }
}

/**
 * @brief 页擦除 flash
 * 
 * @param _addr 
 * @param size 
 */
void stm_flash_erase_page(u32 _addr, u32 _size)
{
  u32 i = 0;
  _addr |= STM32_FLASH_BASE;

  if (_addr < STM32_FLASH_BASE || (_addr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
    return; //非法地址

  FLASH_Unlock(); //解锁

  for (i = 0; i < (_size / STM_SECTOR_SIZE); i++)
  {
    FLASH_ErasePage(_addr);   //擦除这个扇区
    _addr += STM_SECTOR_SIZE; //地址增加2.
  }

  FLASH_Lock(); //上锁
}


void read_flash_param(void)
{
  stm_flash_read(STM32_FLASH_PARAM, (uint8_t*)&param, sizeof(param));
  last_sit_state = param.run_sit_status;
}

void save_flash_param(void)
{
  param.run_sit_status = last_sit_state;
  stm_flash_write(STM32_FLASH_PARAM, (uint8_t*)&param, sizeof(param));
}

// void test_flash(void)
// {
//   u8 flash_read_buf[10] = {0};
//   u8 flash_write_buf[10] = {0};
//   u8 i = 0;

//   STMFLASH_ErasePage(0xF800, 1 * STM_SECTOR_SIZE);
//   STMFLASH_Read(0xF800, flash_read_buf, 10);
//   for (i = 0; i < 10; i++)
//   {
//     flash_write_buf[i] = i;
//   }
//   STMFLASH_Write(0xF800, flash_write_buf, 10);
//   STMFLASH_Read(0xF800, flash_read_buf, 10);
//   for (i = 0; i < 10; i++)
//   {
//   }
//   STMFLASH_ErasePage(0xF800, 1 * STM_SECTOR_SIZE);
//   STMFLASH_Read(0xF800, flash_read_buf, 10);
// }

/******************* (C) COPYRIGHT 2022 oogrow ***************END OF FILE*****/
