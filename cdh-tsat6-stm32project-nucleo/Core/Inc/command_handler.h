#ifndef INCLUDE_COMMAND_HANDLER_H_
#define INCLUDE_COMMAND_HANDLER_H_

#include "stm32l4xx_hal.h"
#include "can.h"

extern CAN_HandleTypeDef hcan1;
extern QueueHandle_t can_rx_queue;

void commandHandlerInit();

void commandProccesor(void *pvParameters);

#endif
