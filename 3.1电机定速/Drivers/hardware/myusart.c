#include "myusart.h"
#include "string.h"

#define CH_COUNT 4
typedef struct 
{
    float fdata[CH_COUNT];
    unsigned char tail[4];
} Frame;

static const uint8_t FRAME_TAIL[4] = {0x00, 0x00, 0x80, 0x7f};


void Send_JustFloat(int16_t target,int16_t actual,int16_t error,int16_t out)
{
    Frame frame_data;
    frame_data.fdata[0] = target;
    frame_data.fdata[1] = actual;
	frame_data.fdata[2] = error;
	frame_data.fdata[3] = out;
    //拷贝帧尾
    memcpy(frame_data.tail, FRAME_TAIL, 4);
    HAL_UART_Transmit(&huart1, (int8_t *)&frame_data, sizeof(Frame), 20);
}
