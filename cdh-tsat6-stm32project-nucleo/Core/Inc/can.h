#ifndef INCLUDE_CAN_H_
#define INCLUDE_CAN_H_
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
//  Functions for CAN initialization, message reception, and message transmission.
//
// History
// 2022-05-25 by Graham Driver
// - Created/Adapted from tsat5.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// INCLDUES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "stm32l4xx_hal.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// STRUCTS
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct{
	uint8_t priority; // Priority of the message MAX VALUE: 0x1F
	uint8_t DestinationID; // The ID number of the destination device MAX VALUE: 0x3
	uint8_t command;	// The command value
	uint8_t data[7];	// Message
} CANMessage_t;
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


void boot_CAN(CAN_HandleTypeDef *hcan1); // Initializes and Starts the CAN


void CAN_transmit_message(
		CAN_HandleTypeDef *hcan1, // CAN object
		CANMessage_t myMessage
);


void CAN_MESSAGE_RECEIVED(CAN_HandleTypeDef *hcan1);    // Interrupt handler for CAN BUS
#endif /* INCLUDE_CAN_H_ */
