#include "command_handler.h"

TaskHandle_t commandProcessorTaskHandle;


void commandHandlerInit(){
	xTaskCreate(
				commandProccesor,	// Function to be called
				"Command Processor", // Name of Task
				((2 * sizeof( struct CANMessage_t * ))/32), // Stack Size
				NULL, // Parameter to pass to function
				tskIDLE_PRIORITY, // Task Priority
				&commandProcessorTaskHandle); // Task Handle
}

void commandProccesor(void *pvParameters){
	while(1){
		//Received Message
		CANMessage_t receivedMessage;
		if(uxQueueMessagesWaiting(can_rx_queue)){
			xQueueReceive(can_rx_queue, &receivedMessage, 0);
			CAN_transmit_message(&hcan1, receivedMessage);
		}
	}
}
