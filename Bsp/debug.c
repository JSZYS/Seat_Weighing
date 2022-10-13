/**
  ******************************************************************************
  * @file    user_it.c
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
#include "debug.h"
#include <string.h>
#include "store.h"

/*****************  ����һ���ֽ� **********************/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
  USART_SendData(pUSARTx, ch);
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

/****************** ����8λ������ ************************/
void Usart_SendArray(USART_TypeDef *pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;

  for (i = 0; i < num; i++)
  {
    Usart_SendByte(pUSARTx, array[i]);
  }
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
  unsigned int k = 0;
  do
  {
    Usart_SendByte(pUSARTx, *(str + k));
    k++;
  } while (*(str + k) != '\0');

  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord(USART_TypeDef *pUSARTx, uint16_t ch)
{
  uint8_t temp_h, temp_l;

  temp_h = (ch & 0XFF00) >> 8;
  temp_l = ch & 0XFF;

  USART_SendData(pUSARTx, temp_h);
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);

  USART_SendData(pUSARTx, temp_l);
  while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
  USART_SendData(USART2, (uint8_t)ch);

  while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);

  return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
  while (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET);

  return (int)USART_ReceiveData(USART2);
}

/*************************************************
Function: 		hex2string
Description: 	hex�ַ�����ת����string�ַ���������printf��ʾ��
Input: 			hex:ԭ�ַ�����
                len:hex����ĳ���
Output: 		ascII:������ַ���
                newlen:������ַ�������
Return:
*************************************************/
void hex2string(char *hex, char *ascII, int len, int *newlen)
{
  int i = 0;
  char newchar[100] = {0};
  *newlen=len*3;
  for (i = 0; i< len; i++)
  {
    sprintf(newchar,"%02X ", hex[i]);
    strcat(ascII, newchar);
  }
}

void pritf_sys_info(void)
{
  printf("\n \\ | /\n");
  printf("- GP -  Car After Seat System\n");
  printf(" / | \\  V%d.%d.%d build   %s %s\n", CS_VERSION, CS_SUBVERSION, CS_REVISION, __DATE__, __TIME__);
  printf(" 2022 - xxxx Copyright by GP-Nano team\n");
  printf("\n");
}

void debug_sensor_adc(void)
{
  u8 temp[8] = {0xfe, 0x00, 0x60, 0x62, 0, 24, 4};
  u8 i = 0;

  for (i = 0; i < 7; i++)
  {
    Usart_SendByte(USART2, temp[i]);
  }
  
  for (i = 0; i < 96; i++)
  {
    Usart_SendHalfWord(USART2, sensor_ad_buf[i]);
  }
}

/******************* (C) COPYRIGHT 2022 GP��Nano ***************END OF FILE*****/
