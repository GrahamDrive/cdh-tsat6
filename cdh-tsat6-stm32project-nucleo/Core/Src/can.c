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
// INCLUDES and Constants
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "can.h"


const uint8_t MAX_CAN_DATA_LENGTH = 8;
const uint8_t receivedDestinationIdMask = 0x3;
const uint8_t SourceID = 0x3; // The ID number of the device MAX VALUE: 0x3
const uint16_t receivedPriorityMask = 0x7F0;

uint8_t receivedDestinationId; // ID of Received Message
CAN_TxHeaderTypeDef TxMessage;
CAN_RxHeaderTypeDef RxMessage; // Received Message Header
uint32_t            TxMailbox; // Transmit Mailbox
uint8_t             RxData[8]; // Received data
const unsigned long QueueLength = 64;
const unsigned long ItemSize = sizeof( struct CANMessage_t * );
QueueHandle_t can_rx_queue;
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
	can_rx_queue = xQueueCreate( QueueLength, ItemSize);
}


/**
 * @brief Used to send messages over CAN
 * @param hcan1 The CANBUS object to send the message over\
 * @param message A 8 byte message
 */
void CAN_transmit_message(CAN_HandleTypeDef *hcan1, CANMessage_t myMessage)
{
	// TX Message Parameters
	uint16_t ID = (myMessage.priority << 4) | (SourceID << 2) | (myMessage.DestinationID);
	uint8_t message[8] = {myMessage.command, myMessage.data[0], myMessage.data[1], myMessage.data[2], myMessage.data[3], myMessage.data[4], myMessage.data[5],myMessage.data[6]};

	TxMessage.StdId = ID;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = MAX_CAN_DATA_LENGTH;
	HAL_CAN_AddTxMessage(hcan1,&TxMessage,message,&TxMailbox);
}

void CAN_MESSAGE_RECEIVED(CAN_HandleTypeDef *hcan1){

	// Message Sent To Queue
	/* Get RX message */
	HAL_CAN_GetRxMessage(hcan1, CAN_RX_FIFO0, &RxMessage, RxData);
	receivedDestinationId = receivedDestinationIdMask & RxMessage.StdId;
	if(receivedDestinationId == SourceID){
		// Either send to OS Queue or Handle
		// Below is the CDH solution
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		HAL_Delay(500);
		// LED OFF
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
		HAL_Delay(500);
	}
}
