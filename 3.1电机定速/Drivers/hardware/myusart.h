#ifndef _MYUSART_H
#define _MYUSART_H

#include "main.h"

extern UART_HandleTypeDef huart1;
void Send_JustFloat(int16_t target,int16_t actual,int16_t error,int16_t out);

#endif
