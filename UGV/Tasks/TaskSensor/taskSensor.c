/*
 * taskSensor.c
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#include "taskSensor.h"
#include "QMC/QMC5883/qmc5883.h"
#include "database.h"
#include "MotorDrive.h"
#include "gps.h"
#include "crc15.h"
#include "mpu6050.h"
#include "QMC/Kalman/kalman_filter.h"

//<<<<<<<<<<<<<<<<<<-STATIC FUNCTIONS->>>>>>>>>>>>>>
static uint16_t qmcProc();
static LED_STATE ledProc();
static uint16_t crcProc(void * ptr, uint16_t len);
volatile uint32_t gpsPreviousHead;
extern uint32_t gpsIrqTime;

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
TaskHandle_t hTaskSensor_s;
extern Qmc hqmc;
extern LoraTransmit loraTx;
extern GPS gps;
uint16_t azim;
MPU6050_t MPU6050;
kalman_state hKalmanXangle;
kalman_state hKalmanYangle;

//<<<<<<<<<<<<<<-FUNCTION PROTOTYPES->>>>>>>>>>>>>>
void taskSensor(void *arg)
{
	TickType_t xLastWakeTime = 0;
	const TickType_t xFrequency = 10;
	xLastWakeTime = xTaskGetTickCount();

	kalman1_init(&hKalmanXangle, 0, 5e0);
	kalman1_init(&hKalmanYangle, 0, 5e0);

	for(;;)
	{
		//!< get azimuth from the qmc5883
		loraTx.azimuth = qmcProc();
		loraTx.ledState = ledProc();

		//!< get the gyro inf
		MPU6050_Read_All(&hi2c3, &MPU6050);
		loraTx.Ax = MPU6050.Ax;
		loraTx.Ay = MPU6050.Ay;
		loraTx.Temperature = MPU6050.Temperature;

		loraTx.KalmanAngleX = kalman1_filter(&hKalmanXangle, MPU6050.KalmanAngleX);
		loraTx.KalmanAngleY = kalman1_filter(&hKalmanYangle, MPU6050.KalmanAngleY);

		//!< control the gps ready?
		if(gps.gpsState == POSITION_FIXED && gps.day != 0 && ((HAL_GetTick() - gpsIrqTime) < 500))
		{
			loraTx.gpsState = POSITION_FIXED;
			loraTx.latitudeDegree = gps.latitudeDegree;
			loraTx.latitudeMinute = gps.latitudeMinute;
			loraTx.latitudeSecond = gps.latitudeSecond;

			loraTx.longitudeDegree = gps.longitudeDegree;
			loraTx.longitudeMinute = gps.longitudeMinute;
			loraTx.longitudeSecond = gps.longitudeSecond;

			loraTx.numberOfSatellite = gps.numberOfSatellite;
			loraTx.second = gps.second;
			loraTx.minute = gps.minute;
			loraTx.hour = gps.hour;
			loraTx.day = gps.day;
			loraTx.month = gps.month;
			loraTx.locationLat = gps.locationLat;
			loraTx.locationLong = gps.locationLong;

			loraTx.speed = gps.speed;
		}
		else
		{
			loraTx.gpsState = NO_CONNECTION;
		}

		gpsPreviousHead = ringBuff.head;

		uint16_t crc = crcProc(&loraTx, sizeof(loraTx) - 4);
		loraTx.crcLsb = (crc >> 0) & 0xFF;
		loraTx.crcMsb = (crc >> 8) & 0xFF;

		xQueueGenericSend(sensorDataQueue, &loraTx, 5, queueSEND_TO_FRONT);

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

/**
 * @brief take the azimuth angle
 * @return azimuthn angle
 */
static uint16_t qmcProc()
{
	uint16_t azimuthAngle = 0;
	if(UGV_isDataReady(&hqmc))
	{
		azimuthAngle = (uint16_t)UGV_getAzimuth(&hqmc);
	}

	return azimuthAngle;
}

/**
 * @brief set or reset the led status according the rf transmitter signal
 * @return led status
 */
static LED_STATE ledProc()
{
	LED_STATE ledState = LEDS_OFF;

	//!< set the leds
	if((rcChannel_s.channel3>=(CHANNEL_DOWN-CHANNEL_ERROR)) && (rcChannel_s.channel1<=(CHANNEL_UP + CHANNEL_ERROR)))
	{
		ledState = UGV_ledControl(&rcChannel_s);
	}
	else
	{
		NVIC_SystemReset();
	}

	return ledState;
}

/**
 * @brief calculate the crc of the message up to len index
 * @return 16 bit crc value
 */
static uint16_t crcProc(void * ptr, uint16_t len)
{
	return AE_pec15((uint8_t*)ptr, len);
}
