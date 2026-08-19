#ifndef _ECODER_H
#define _ECODER_H

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void ecoder_Init(void);
int16_t Get_CNT(void);
int16_t Get_Speed(void);

#endif
