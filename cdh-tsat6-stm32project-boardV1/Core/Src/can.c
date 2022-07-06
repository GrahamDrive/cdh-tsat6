//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2022
//
// License:
//  Available under MIT license.
//
// Repository:
//  Github: https://github.com/UMSATS/cdh-tsat6
//
// File Description:
//  Functions for CAN initialization, message reception, and message transmission. Received messages are read into a Queue, which
//  can be handled by a dedicated task.
//
// History
// 2022-05-25 by Graham Driver
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>

#include "can.h"


CAN_TxHeaderTypeDef TxMessage;
CAN_RxHeaderTypeDef RxMessage;
uint32_t            TxMailbox;
uint8_t             RxData[8];
HAL_StatusTypeDef 	returnCode;

/**
 * @brief Boots the CAN Bus
 * 
 * @return HAL_StatusTypeDef 
 */
void boot_CAN(CAN_HandleTypeDef *hcan1){

	HAL_CAN_Start(hcan1); // Turn on CANBus

	HAL_CAN_ActivateNotification(hcan1, CAN_IT_RX_FIFO0_MSG_PENDING );

	// TX Message Parameters
	TxMessage.StdId = ID;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = MAX_CAN_DATA_LENGTH;
}


/**
 * @brief Used to send messages over CAN
 * @param hcan1 The CANBUS object to send the message over\
 * @param message A 8 byte message
 */
void CAN_transmit_message(CAN_HandleTypeDef *hcan1, uint8_t message[])
{
  HAL_CAN_AddTxMessage(hcan1,&TxMessage,message,&TxMailbox);
}

void CAN_MESSAGE_RECEIVED(CAN_HandleTypeDef *hcan1){
	/* Get RX message */
	uint8_t testResponse[8] = {8,7,6,5,4,3,2,1};
	HAL_Delay(100);
	CAN_transmit_message(hcan1, testResponse);
	  return;
}


