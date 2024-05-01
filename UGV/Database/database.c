/*
 * database.c
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */



#include "database.h"


QueueHandle_t sensorDataQueue = NULL;
LoraTransmit loraTx;
LoraTransmit loraRx;

void databaseQueueInit(uint16_t len, uint16_t size)
{
	sensorDataQueue = xQueueCreate(len, size);
}
