#ifndef _PWM_H
#define _PWM_H

#include "main.h"
extern TIM_HandleTypeDef htim2;

void PWM_Init(void);
void PWM_Set(int16_t PWM);

#endif
