#ifndef INCLUDE_COMMAND_HANDLER_H_
#define INCLUDE_COMMAND_HANDLER_H_
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
//  The main command handler for the CAN bus transmissions.
//
// History
// 2022-10-03 by Graham Driver
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "stm32l4xx_hal.h"
#include "can.h"

extern CAN_HandleTypeDef hcan1;
extern QueueHandle_t can_rx_queue;

void commandHandlerInit();

void commandProccesor(void *pvParameters);

#endif
