#include "main.h"
#include "ecoder.h"

void ecoder_Init(void)
{
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
    TIM3->CNT=0;
}

int16_t Get_CNT(void)
{
    int16_t temp;
    temp=TIM3->CNT;
    return temp;
}

int16_t Get_Speed(void)
{
	static int16_t last_speed=0;
	
	int16_t speed;
	int16_t cur_speed;
	cur_speed=Get_CNT();
	speed=cur_speed-last_speed;
		
	last_speed=cur_speed;
	return speed;
}
