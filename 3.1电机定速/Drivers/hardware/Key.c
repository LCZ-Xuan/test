#include "Key.h"
#include "tim.h"

// 按键结构体
typedef struct {
    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
    GPIO_PinState pre_Status;
    uint8_t flag;
} Key_TypeDef;

// 定义按键数组
Key_TypeDef keys[] = {
    {GPIOB, GPIO_PIN_1, GPIO_PIN_SET, 0},
    {GPIOB, GPIO_PIN_11, GPIO_PIN_SET, 0}
};
#define KEY_COUNT 2

/**
  * @brief  开关初始化
  * @param  无
  * @retval 无
  */
void Key_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim4);
}

/**
  * @brief  按键状态扫描
  * @param  无
  * @retval 无
  */
void MyTIM_Scan(void)
{
    for(uint8_t i = 0; i < KEY_COUNT; i++)
    {
        GPIO_PinState now_Status = HAL_GPIO_ReadPin(keys[i].GPIOx, keys[i].GPIO_Pin);
        
        if(keys[i].pre_Status == GPIO_PIN_SET && now_Status == GPIO_PIN_RESET)
        {
            keys[i].flag = 1;
        }
        keys[i].pre_Status = now_Status;
    }
}

/**
  * @brief  获取按键状态
  * @param  按键的数组下表2
  * @retval 按键状态
  */
uint8_t Key_Get(uint8_t key_id)
{
    uint8_t temp = keys[key_id].flag;
    keys[key_id].flag = 0;
    return temp;
}
