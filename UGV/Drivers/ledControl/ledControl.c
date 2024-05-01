/*
 * ledControl.c
 *
 *  Created on: Feb 9, 2024
 *      Author: ygork
 */

#include "ledControl.h"
#include "main.h"

LED_STATE UGV_ledControl(RcChannel * rcChannel)
{
	LED_STATE ledState = LEDS_OFF;

	if(rcChannel->channel4 < ( LID_LED_MIDDLE - LID_LED_ERROR))
	{
		HAL_GPIO_WritePin(LID_LED_GPIO_Port, LID_LED_Pin, 0);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
		ledState = LEDS_OFF;
	}
	else if (rcChannel->channel4 < ( LID_LED_MIDDLE + LID_LED_ERROR))
	{
		HAL_GPIO_WritePin(LID_LED_GPIO_Port, LID_LED_Pin, 0);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
		ledState = FRONT_LED_ON;
	}
	else
	{
		HAL_GPIO_WritePin(LID_LED_GPIO_Port, LID_LED_Pin, 1);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
		ledState = ALL_LED_ON;
	}

	return ledState;
}

