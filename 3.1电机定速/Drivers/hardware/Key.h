#ifndef _KEY_H
#define _KEY_H

#include "main.h"

void Key_Init(void);
void MyTIM_Scan(void);
uint8_t Key_Get(uint8_t key_id);

#endif
