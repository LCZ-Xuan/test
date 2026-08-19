#include "PWM.h"

void PWM_Init(void)
{
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);;
}
void PWM_Set(int16_t PWM)
{
    if(PWM>0)
	{
	    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
	    TIM2->CCR4=PWM;
	}
	else{
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
	    TIM2->CCR4=-PWM;
	}
}
