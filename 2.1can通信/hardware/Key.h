#ifndef _KEY_H
#define _KEY_H

#include "main.h"

void Key_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim);
uint8_t Key_Get(void);

#endif
