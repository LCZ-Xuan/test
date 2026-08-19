#include "Key.h"
#include "tim.h"

uint8_t TIMFlag=0;

/**
  * @brief  开关初始化
  * @param  无
  * @retval 无
  */
void Key_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim2);
}

/**
  * @brief  定时器回调函数，用于检测开关状态
  * @param  无
  * @retval 无
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef*htim)
{
    if(htim==&htim2)
    {
        static GPIO_PinState pre_Status=GPIO_PIN_SET;
        GPIO_PinState now_Status=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
        if(pre_Status==GPIO_PIN_SET&&now_Status==GPIO_PIN_RESET)
        {
            TIMFlag=1;
        }
        pre_Status=now_Status;
    }
}

/**
  * @brief  获取开关状态
  * @param  无
  * @retval 返回开关状态，1代表按下
  */
uint8_t Key_Get(void)
{
    int temp=TIMFlag;
    TIMFlag=0;
    return temp;
}