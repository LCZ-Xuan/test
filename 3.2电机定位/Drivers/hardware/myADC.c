#include "myADC.h"

void MyADC_Init(void)
{
    ADC_ChannelConfTypeDef ADC_Channel_Init;

    ADC_Channel_Init.Channel = ADC_CHANNEL_1;
    ADC_Channel_Init.Rank = ADC_REGULAR_RANK_1;
    ADC_Channel_Init.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1, &ADC_Channel_Init);

    ADC_Channel_Init.Channel = ADC_CHANNEL_2;
	HAL_ADC_ConfigChannel(&hadc2, &ADC_Channel_Init);

	HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc2);
}

uint16_t Get_ADC(ADC_HandleTypeDef hadc)
{
    HAL_ADC_Start(&hadc);

    if (HAL_ADC_PollForConversion(&hadc, 100) == HAL_OK) {
        return HAL_ADC_GetValue(&hadc);
    }
    return 0;
}


