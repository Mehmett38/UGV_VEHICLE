/*
 * rcReceiver.c
 *
 *  Created on: Jan 23, 2024
 *      Author: Mehmet Dincer
 */


#include "rcReceiver.h"


static void UGV_rcDutyCalculate(HAL_TIM_ActiveChannel HAL_TIM_ACTIVE_CHANNEL);


uint8_t tim2FirstCap[TIM2_CHANNEL_NUMBER];
uint32_t tim2IcVal1[TIM2_CHANNEL_NUMBER];
uint32_t tim2IcVal2[TIM2_CHANNEL_NUMBER];
uint32_t tim2Difference[TIM2_CHANNEL_NUMBER];
uint32_t tim2Width[TIM2_CHANNEL_NUMBER];

RcChannel rcChannel_s;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
uint8_t rcActive = 0;

//!< counter ratio calculation and rc available controller
float mFactor = 100000/REF_CLOCK;

/**
 * @brief initialize timer2 as as input capture mode, and enable interrupts
 * @return none
 */
void UGV_rcReceiverInit()
{
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_3);
	  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_4);

	  rcChannel_s.channel1 = CHANNEL_MIDDLE;
	  rcChannel_s.channel2 = CHANNEL_MIDDLE;
	  rcChannel_s.channel3 = CHANNEL_MIDDLE;
	  rcChannel_s.channel4 = CHANNEL_MIDDLE;
}


/**
 * @brief timer rising and falling edge interrupt callback function
 * @param[in] timer base address
 * @return none
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		rcActive = 1;

		//!< channel1 calculation
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			UGV_rcDutyCalculate(HAL_TIM_ACTIVE_CHANNEL_1);
		}

		else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			UGV_rcDutyCalculate(HAL_TIM_ACTIVE_CHANNEL_2);
		}

		else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
		{
			UGV_rcDutyCalculate(HAL_TIM_ACTIVE_CHANNEL_3);
		}

		else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
		{
			UGV_rcDutyCalculate(HAL_TIM_ACTIVE_CHANNEL_4);
		}
	}
}

/**
 * @brief firstly send the rising edge interrupt and take the that time,
 * secondly send the falling edge interrupt after calculate the this duration
 * actually pwm duty must be 0-100, to ensure this we set prescale 9000 but this is not
 * possible for 16 bit so range think as duty * 100
 *
 * @param[in] active channel number
 * @return none
 */
static void UGV_rcDutyCalculate(HAL_TIM_ActiveChannel HAL_TIM_ACTIVE_CHANNEL)
{
	uint16_t *channelPtr = &rcChannel_s.channel1;

	uint8_t index = (HAL_TIM_ACTIVE_CHANNEL == HAL_TIM_ACTIVE_CHANNEL_1) ? 0 :
			        (HAL_TIM_ACTIVE_CHANNEL == HAL_TIM_ACTIVE_CHANNEL_2) ? 1 :
			        (HAL_TIM_ACTIVE_CHANNEL == HAL_TIM_ACTIVE_CHANNEL_3) ? 2 :
			        (HAL_TIM_ACTIVE_CHANNEL == HAL_TIM_ACTIVE_CHANNEL_4) ? 3 : 100;

	if(tim2FirstCap[index] == 0)
	{
		//!< channel values -> 0-4-8-12 that is four time index
		tim2IcVal1[index] = HAL_TIM_ReadCapturedValue(&htim2, index * 4);
		tim2FirstCap[index] = 1;
	}
	else
	{
		tim2IcVal2[index] = HAL_TIM_ReadCapturedValue(&htim2, index * 4);

		if(tim2IcVal2[index] > tim2IcVal1[index])
		{
			tim2Difference[index] = tim2IcVal2[index] - tim2IcVal1[index];
		}
		else
		{
			tim2Difference[index] = (0xFFFFFFFF - tim2IcVal1[index]) + tim2IcVal2[index];
		}


		channelPtr[index] = tim2Difference[index] * mFactor;
		tim2FirstCap[index] = 0;
	}
}






















