/*
 * taskMotorDrive.c
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */


#include "taskMotorDrive.h"
#include "database.h"

TaskHandle_t hTaskMotDrive_s;
extern LoraTransmit loraTx;

void taskMotorDrive(void *arg)
{
	TickType_t xLastWakeTime = 0;
	const TickType_t xFrequency = 20;
	xLastWakeTime = xTaskGetTickCount();
	float azimuthAngle = 0.0f;

	for(;;)
	{
		  if((rcChannel_s.channel1>=(CHANNEL_DOWN-CHANNEL_ERROR)) && (rcChannel_s.channel1<=(CHANNEL_UP + CHANNEL_ERROR)) &&
		     (rcChannel_s.channel2>=(CHANNEL_DOWN-CHANNEL_ERROR)) && (rcChannel_s.channel2<=(CHANNEL_UP + CHANNEL_ERROR)) &&
			 (rcChannel_s.channel3>=(CHANNEL_DOWN-CHANNEL_ERROR)) && (rcChannel_s.channel3<=(CHANNEL_UP + CHANNEL_ERROR)) &&
			 (rcChannel_s.channel4>=(CHANNEL_DOWN-CHANNEL_ERROR)) && (rcChannel_s.channel4<=(CHANNEL_UP + CHANNEL_ERROR)))
		  {
			  UGV_motorDrive(&rcChannel_s, azimuthAngle);
			  UGV_cameraServoSetAngle(&rcChannel_s);
		  }
		  else
		  {
			  NVIC_SystemReset();
		  }

		vTaskDelayUntil(&xLastWakeTime, xFrequency);
	}
}
