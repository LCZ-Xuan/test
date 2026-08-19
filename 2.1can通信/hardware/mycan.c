#include "main.h"
#include "mycan.h"

/**
  * @brief  滤波器初始化以及开启can控制器
  * @param  无
  * @retval 无
  */
void mycan_Init(void)
{
CAN_FilterTypeDef filter_Init;

filter_Init.FilterActivation = ENABLE;
filter_Init.FilterBank = 0;
filter_Init.FilterFIFOAssignment = CAN_RX_FIFO0;
filter_Init.FilterIdHigh = 0x0000;
filter_Init.FilterIdLow = 0x0000;
filter_Init.FilterMaskIdHigh = 0x0000;
filter_Init.FilterMaskIdLow = 0x0000;
filter_Init.FilterMode = CAN_FILTERMODE_IDMASK;
filter_Init.FilterScale = CAN_FILTERSCALE_32BIT;
filter_Init.SlaveStartFilterBank = 0;

HAL_CAN_ConfigFilter(&hcan, &filter_Init);

HAL_CAN_Start(&hcan);
}

/**
  * @brief  接受报文
  * @param  接受报文ID
  * @param	接受报文有效长度
  * @param	接受报文数据
  * @retval 无
  */
void mycan_Receive(uint32_t *ID, uint8_t *length, uint8_t *Data)
{
	CAN_RxHeaderTypeDef RxMessage;
	HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxMessage, Data);

	if (RxMessage.IDE == CAN_ID_STD)
		*ID = RxMessage.StdId;
	else
		*ID = RxMessage.ExtId;

	if (RxMessage.RTR == CAN_RTR_DATA)
	{
		*length = RxMessage.DLC;
	}
	else
	{
		*length = 0;    
	}
}

/**
  * @brief  邮箱接受状态
  * @param  无
  * @retval 代表邮箱是否开始接受
  */
uint8_t mycan_ReceiveFlag(void)
{
    if(HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_RX_FIFO0) > 0)
        return 1;
    return 0;
}

/**
  * @brief  发送报文
  * @param  发送报文ID
  * @param  发送报文长度
  * @param 	发送报文首地址
  * @retval 无
  */
void mycan_SendData(uint32_t ID,uint8_t length,uint8_t *Data)
{
    CAN_TxHeaderTypeDef TxHeader;
	uint32_t SendMailbox;
	uint32_t timeout=0;

    TxHeader.StdId = ID;
    TxHeader.ExtId = 0;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = length;

	HAL_CAN_AddTxMessage(&hcan,&TxHeader,Data,&SendMailbox);

	// TME位置1 = 邮箱为空、发送完成
	while( READ_BIT(hcan.Instance->TSR, CAN_TSR_TME0 << SendMailbox) == 0 )
	{
		timeout++;
		if(timeout > 100000) break;
	}
}