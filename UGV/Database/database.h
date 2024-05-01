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
#include "gps.h"

typedef struct{
	uint16_t azimuth;

	uint8_t latitudeDegree;	//!< this variables are float convert them HEX form
	uint8_t latitudeMinute;	//!< this variables are float convert them HEX form
	float latitudeSecond;	//!< this variables are float convert them HEX form

	uint8_t longitudeDegree;	//!< this variables are float convert them HEX form
	uint8_t longitudeMinute;	//!< this variables are float convert them HEX form
	float longitudeSecond;	//!< this variables are float convert them HEX form

	uint8_t numberOfSatellite;

	uint32_t speed;				//!< this variables are float convert them HEX form

	LED_STATE ledState;

	GPS_State gpsState;

	uint8_t crcLsb;
	uint8_t crcMsb;

//	uint8_t azimuthLsb;
//	uint8_t azimuthMsb;
//
//	uint8_t latitudeDegree;
//	uint8_t latitudeMinute;
//	uint8_t latitudeSecond;

//	uint8_t longitudeDegree;
//	uint8_t longitudeMinute;
//	uint8_t longitudeSecond;

//	uint8_t numberOfSatellite;

//	uint8_t height;
//	uint32_t speed;
}LoraTransmit;


extern QueueHandle_t sensorDataQueue;

void databaseQueueInit(uint16_t len, uint16_t size);

#endif /* DATABASE_DATABASE_H_ */
