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

const uint8_t MAX_CAN_DATA_LENGTH = 8;
const uint8_t receivedDestinationIdMask = 0x3;
const uint8_t receivedSourceIdMask = 0xC;
const uint16_t receivedPriorityMask = 0x7F0;
const uint8_t SourceID = 0x3; // The ID number of the device MAX VALUE: 0x3
uint8_t receivedPriority;
uint8_t receivedSourceId;
uint8_t receivedDestinationId;
CAN_TxHeaderTypeDef TxMessage;
CAN_RxHeaderTypeDef RxMessage;
uint32_t            TxMailbox;
uint8_t             RxData[8];
/**
 * @brief Boots the CAN Bus
 * 
 * @return HAL_StatusTypeDef 
 */
void boot_CAN(CAN_HandleTypeDef *hcan1){
	CAN_FilterTypeDef  		sFilterConfig;
	sFilterConfig.FilterIdHigh = 0x0000;
	sFilterConfig.FilterIdLow = 0x0000;
	sFilterConfig.FilterMaskIdHigh = 0x0000;
	sFilterConfig.FilterMaskIdLow = 0x0000;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 14;

	HAL_CAN_ConfigFilter(hcan1, &sFilterConfig);
	HAL_CAN_Start(hcan1); // Turn on CANBus

	HAL_CAN_ActivateNotification(hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}


/**
 * @brief Used to send messages over CAN
 * @param hcan1 The CANBUS object to send the message over\
 * @param message A 8 byte message
 */
void CAN_transmit_message(CAN_HandleTypeDef *hcan1, struct message myMessage)
{
	// TX Message Parameters
	uint16_t ID = (myMessage.priority << 4) | (SourceID << 2) | (myMessage.DestinationID);
	uint8_t message[8] = {myMessage.command, myMessage.argument, myMessage.data[0], myMessage.data[2], myMessage.data[3], myMessage.data[4], myMessage.data[5], myMessage.data[6]};

	TxMessage.StdId = ID;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = MAX_CAN_DATA_LENGTH;
	HAL_CAN_AddTxMessage(hcan1,&TxMessage,message,&TxMailbox);
}

void CAN_MESSAGE_RECEIVED(CAN_HandleTypeDef *hcan1){
	/* Get RX message */
	HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &RxMessage, RxData);
	receivedDestinationId = receivedDestinationIdMask & RxMessage.StdId;
	if(receivedDestinationId == SourceID){
		receivedSourceId = receivedSourceIdMask & RxMessage.StdId;
		receivedPriority = receivedPriorityMask & RxMessage.StdId;
		// Either send to OS Queue or Handle
	}
}


