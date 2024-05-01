/*
 * taskLoraCom.c
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */


#include "taskLoraCom.h"
#include "database.h"

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
TaskHandle_t hTaskLoraCom_s;
SX1278_hw_t SX1278_hw;
SX1278_t SX1278;
uint8_t txBuffer[8];
uint8_t rxBuffer[8];

static LoraTransmit loraTx;
static LoraTransmit loraRx;

static int ret;
static int retTx;
static uint8_t txRxMutex = TX_STATUS;

void taskLoraCom(void *arg)
{
	TickType_t xLastWakeTime = 0;
	const TickType_t xFrequency = 25;
	xLastWakeTime = xTaskGetTickCount();

	//initialize lora module
	SX1278_init(&SX1278, 434000000, SX1278_POWER_17DBM, SX1278_LORA_SF_7,
				SX1278_LORA_BW_125KHZ, SX1278_LORA_CR_4_5, SX1278_LORA_CRC_EN, sizeof(loraTx));

	ret = SX1278_LoRaEntryTx(&SX1278, sizeof(loraTx), TX_TIMEOUT);

	for(;;)
	{
		xQueueReceive(sensorDataQueue, &loraTx, 2);

		txRxMutex = TX_STATUS;
		ret = SX1278_LoRaEntryTx(&SX1278, sizeof(loraTx), TX_TIMEOUT);
		retTx = SX1278_LoRaTxPacket(&SX1278, (uint8_t*)&loraTx,
				sizeof(loraTx), TX_TIMEOUT);
		txRxMutex = RX_STATUS;

		ret = SX1278_LoRaEntryRx(&SX1278, sizeof(loraRx), TX_TIMEOUT);

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

/**
 * @brief callback function for the DIO0 pin
 * @return none
 */
void dioIrqCallback()
{
	if(txRxMutex == TX_STATUS)
	{
		return;
	}
	else
	{
		ret = SX1278_available(&SX1278);
		SX1278_read(&SX1278, (uint8_t*)&loraRx, ret);
	}
}







