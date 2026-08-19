#ifndef _MYADC_H
#define _MYADC_H

#include "main.h"
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

void MyADC_Init(void);
uint16_t Get_ADC(ADC_HandleTypeDef hadc);

#endif
