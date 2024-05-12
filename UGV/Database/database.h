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
	uint8_t numberOfSatellite;
	uint8_t second;
	float longitudeSecond;	//!< this variables are float convert them HEX form

	float speed;				//!< this variables are float convert them HEX form

	float Ax;
	float Ay;

    float Temperature;

    float KalmanAngleX;
    float KalmanAngleY;

	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t month;

    Location locationLat;
    Location locationLong;

	LED_STATE ledState;

	GPS_State gpsState;

	uint8_t crcLsb;
	uint8_t crcMsb;

}LoraTransmit;


extern QueueHandle_t sensorDataQueue;

void databaseQueueInit(uint16_t len, uint16_t size);

#endif /* DATABASE_DATABASE_H_ */
