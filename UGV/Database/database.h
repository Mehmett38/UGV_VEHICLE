/*
 * database.h
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#ifndef DATABASE_DATABASE_H_
#define DATABASE_DATABASE_H_

#include "stdint.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "ledControl.h"

typedef struct{
	uint8_t azimuthLsb;
	uint8_t azimuthMsb;

	uint8_t latitudeDegree;
	uint8_t latitudeMinute;
	uint8_t latitudeSecond;

	uint8_t longitudeDegree;
	uint8_t longitudeMinute;
	uint8_t longitudeSecond;

	uint8_t numberOfSatellite;

	uint8_t height;
	uint8_t speed;

	uint8_t dummy1;
	uint8_t dummy2;
	uint8_t dummy3;

	LED_STATE ledState;

	uint8_t crcLsb;
	uint8_t crcMsb;
}LoraTransmit;


extern QueueHandle_t sensorDataQueue;

void databaseQueueInit(uint16_t len, uint16_t size);

#endif /* DATABASE_DATABASE_H_ */
