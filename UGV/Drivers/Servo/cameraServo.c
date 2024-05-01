/*
 * cameraServo.c
 *
 *  Created on: Apr 28, 2024
 *      Author: Mehmet Dincer
 */


#include "cameraServo.h"

static TIM_HandleTypeDef * hServoTim;
static uint32_t servoChannel;

void UGV_cameraServoInit(TIM_HandleTypeDef * htim, uint32_t channel)
{
	hServoTim = htim;
	servoChannel = channel;
	uint8_t channelOffset = (servoChannel / 4);

	HAL_TIM_PWM_Start(htim, channel);
	*((uint32_t*)((&hServoTim->Instance->CCR1) + channelOffset)) = CAMERA_RESET_CCR1_VAL;

}

void UGV_cameraServoSetAngle(RcChannel * rcChannel_s)
{
	uint8_t channelOffset = (servoChannel / 4);
	float ratio = CAMERA_RESET_CCR1_VAL - CAMERA_MIN_CCR1_VAL;

	if(rcChannel_s->channel3 < (ADC_MIDDLE - ADC_ERROR))
	{
		float ccr1Val = (ADC_MIDDLE - rcChannel_s->channel3 * 1.0f);
		ccr1Val = ( ccr1Val < 0) ? -ccr1Val : ccr1Val;

		ccr1Val = (ccr1Val / (ADC_MIDDLE - ADC_SUB_POINT)) * ratio;

		*((uint32_t*)((&hServoTim->Instance->CCR1) + channelOffset)) = CAMERA_RESET_CCR1_VAL + ccr1Val;
	}
	else if(rcChannel_s->channel3 < (ADC_MIDDLE + ADC_ERROR))
	{
		*((uint32_t*)((&hServoTim->Instance->CCR1) + channelOffset)) = CAMERA_RESET_CCR1_VAL;
	}
	else
	{
		float ccr1Val = (rcChannel_s->channel3 - ADC_MIDDLE * 1.0f);
		ccr1Val = ( ccr1Val < 0) ? -ccr1Val : ccr1Val;

		ccr1Val = (ccr1Val / (ADC_UPPER_POINT - ADC_MIDDLE)) * ratio;

		*((uint32_t*)((&hServoTim->Instance->CCR1) + channelOffset)) = CAMERA_RESET_CCR1_VAL - ccr1Val;
	}
}
