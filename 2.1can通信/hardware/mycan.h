#ifndef _MYCAN_H
#define _MYCAN_H

extern CAN_HandleTypeDef hcan;

void mycan_Init(void);
void mycan_Receive(uint32_t *ID, uint8_t *length, uint8_t *Data);
uint8_t mycan_ReceiveFlag(void);
void mycan_SendData(uint32_t ID,uint8_t length,uint8_t *Data);
#endif
