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

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
TaskHandle_t hTaskSensor_s;
extern Qmc hqmc;
extern LoraTransmit loraTx;
extern GPS gps;
uint16_t azim;

//<<<<<<<<<<<<<<-FUNCTION PROTOTYPES->>>>>>>>>>>>>>
void taskSensor(void *arg)
{
	TickType_t xLastWakeTime = 0;
	const TickType_t xFrequency = 10;
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		//!< get azimuth from the qmc5883
		azim = qmcProc();

		//!< set the leds
		if((rcChannel_s.channel3>=(CHANNEL_DOWN-CHANNEL_ERROR)) && (rcChannel_s.channel1<=(CHANNEL_UP + CHANNEL_ERROR)))
		{
			loraTx.ledState = UGV_ledControl(&rcChannel_s);
		}
		else
		{
			NVIC_SystemReset();
		}

		//!< control the gps ready?
		if(gps.gpsState == POSITION_FIXED && gps.day != 0)
		{
		}

		loraTx.azimuthLsb = (azim >> 0) & 0xFF;
		loraTx.azimuthMsb = (azim >> 8) & 0xFF;

		xQueueGenericSend(sensorDataQueue, &loraTx, 5, queueSEND_TO_FRONT);



		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}

uint16_t qmcProc()
{
	uint16_t azimuthAngle = 0;
	if(UGV_isDataReady(&hqmc))
	{
		azimuthAngle = (uint16_t)((uint32_t)UGV_getAzimuth(&hqmc));
	}

	return azimuthAngle;
}
