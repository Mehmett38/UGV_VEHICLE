/*
 * MotorDrive.c
 *
 *  Created on: Feb 4, 2024
 *      Author: Mehmet Dincer
 */


#include "MotorDrive.h"
#include "iwdg.h"


//<<<<<<<<<<<<<<<<<-FUNCTIONS PROTOTYPES->>>>>>>>>>>>>>>>>>
static void motorUpDown(uint16_t adcVal);
static void motorRightLeft(uint16_t adcVal);
uint8_t startFlag;

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>>>>>
RCFilter rcFilterForward;
RCFilter rcFilterBackward;
RCFilter rcFilterRight;
RCFilter rcFilterLeft;
MotorControl motorInf;
float controlSig;
PIDController pid =
{
		.Kp        = PID_KP,
		.Ki        = PID_KI,
		.Kd        = PID_KD,
		.tau       = PID_TAU,
		.limMin    = PID_LIM_MIN,
		.limMax    = PID_LIM_MAX,
		.limMinInt = PID_LIM_MIN_INT,
		.limMaxInt = PID_LIM_MAX_INT,
		.T         = SAMPLE_TIME_S
};

//<<<<<<<<<<<<<<<<<<-FUNCTIONS->>>>>>>>>>>>>>>>>>
/**
 * @brief initialize the timer pwm setting to driver the motor
 * @return none
 */
void UGV_motorInit()
{
	RCFilter_Init(&rcFilterForward, 0.05f, 0.05f);
	RCFilter_Init(&rcFilterBackward, 0.05f, 0.05f);
	RCFilter_Init(&rcFilterRight, 0.65f, 0.65f);
	RCFilter_Init(&rcFilterLeft, 0.65f, 0.65f);

	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 0);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);

    PIDController_Init(&pid);
}

/**
 * @brief read the channel's adc values and call the neaded functions
 * @param[in] rcChannel global variable
 * @return none
 */
void UGV_motorDrive(RcChannel * rcChannel, float azimuthAngle)
{
	//!< rc transmitter lock
	if(startFlag == 0)
	{
		if((rcChannel->channel2<=(CHANNEL_DOWN + CHANNEL_ERROR)) && (rcChannel->channel1>=(CHANNEL_UP - CHANNEL_ERROR)))
		{
			while(!((rcChannel->channel1>=CHANNEL_MIDDLE) && (rcChannel->channel2>=CHANNEL_MIDDLE)))
			{
				HAL_IWDG_Refresh(&hiwdg);
			}
			startFlag = 1;
		}
	}

	if(startFlag)
	{
//		//!< rc transmitter idle state
//		if((rcChannel->channel2 > (CHANNEL_MIDDLE - CHANNEL_ERROR)) &&
//		   (rcChannel->channel2 < (CHANNEL_MIDDLE + CHANNEL_ERROR)))
//		{
//			azimuth = azimuthAngle;
//		}
//		else
//		{
//			PIDController_Update(&pid, azimuth, azimuthAngle);
//
//			if(pid.out >= 0)	// azimuth > azimuthAngle, +, sol tarafa dönderildi
//			{
//				if(rcChannel->channel1 < (CHANNEL_MIDDLE - CHANNEL_ERROR))
//				{
//					rcChannel->channel1 = CHANNEL_MIDDLE + CHANNEL_ERROR;
//					rcChannel->channel1 += (pid.out);
//					rcChannel->channel1 = (rcChannel->channel1 > CHANNEL_UP) ? CHANNEL_UP : rcChannel->channel1;
//				}
//				else if(rcChannel->channel1 < (CHANNEL_MIDDLE + CHANNEL_ERROR))
//				{
//					rcChannel->channel1 = CHANNEL_MIDDLE + CHANNEL_ERROR;
//					rcChannel->channel1 += (pid.out);
//				}
//				else
//				{
//					rcChannel->channel1 = CHANNEL_MIDDLE + CHANNEL_ERROR;
//					rcChannel->channel1 += (pid.out);
//					rcChannel->channel1 = (rcChannel->channel1 > CHANNEL_UP) ? CHANNEL_UP : rcChannel->channel1;
//				}
//			}
//			else				//azimuth < azimuthAngle
//			{
//				if(rcChannel->channel1 < (CHANNEL_MIDDLE - CHANNEL_ERROR))
//				{
//					rcChannel->channel1 = CHANNEL_MIDDLE - CHANNEL_ERROR;
//					rcChannel->channel1 += (pid.out);
//					rcChannel->channel1 = (rcChannel->channel1 < CHANNEL_DOWN) ? CHANNEL_DOWN : rcChannel->channel1;
//				}
//				else if(rcChannel->channel1 < (CHANNEL_MIDDLE + CHANNEL_ERROR))
//				{
//					rcChannel->channel1 = (CHANNEL_MIDDLE - CHANNEL_ERROR);
//					rcChannel->channel1 += (pid.out);
//					rcChannel->channel1 = (rcChannel->channel1 < CHANNEL_DOWN) ? CHANNEL_DOWN : rcChannel->channel1;
//				}
//				else
//				{
//					rcChannel->channel1 = (CHANNEL_MIDDLE - CHANNEL_ERROR);
//					rcChannel->channel1 = (pid.out);
//					rcChannel->channel1 = (rcChannel->channel1 < CHANNEL_DOWN) ? CHANNEL_DOWN : rcChannel->channel1;
//				}
//			}
//		}

		motorUpDown(rcChannel->channel2);
		motorRightLeft(rcChannel->channel1);
	}
}

/**
 * @brief control the motor forward and backward
 * @param[in] read the channel2 adc value
 * @return none
 */
static void motorUpDown(uint16_t adcVal)
{
	float pwmDuty;

	if(adcVal > (CHANNEL_MIDDLE + CHANNEL_ERROR))
	{
		//clear the backward motor's pwm
		RIGHT_MOTOR_BACKWARD(0);
		LEFT_MOTOR_BACKWARD(0);

		// if channel value between 1600 - 1950, pwmDuty can be 0-350
		pwmDuty = adcVal - (CHANNEL_MIDDLE + CHANNEL_ERROR);

		//set the duty map 0-100
		pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 100.0f);
		//limit the duty to 100
		pwmDuty = (pwmDuty > 100)? 100 : pwmDuty;

		//rc filter	pwm duty range 0-100
		pwmDuty = RCFilter_Update(&rcFilterForward, pwmDuty);

		RIGHT_MOTOR_FORWARD((uint8_t)pwmDuty);
		LEFT_MOTOR_FORWARD((uint8_t)pwmDuty);

		motorInf.direction = FORWARD;
		motorInf.forwardPwm = pwmDuty;
	}
	else if((adcVal < (CHANNEL_MIDDLE + CHANNEL_ERROR)) && (adcVal > (CHANNEL_MIDDLE - CHANNEL_ERROR)))
	{
		RIGHT_MOTOR_FORWARD(0);
		LEFT_MOTOR_FORWARD(0);
		RIGHT_MOTOR_BACKWARD(0);
		LEFT_MOTOR_BACKWARD(0);

		RCFilter_Update(&rcFilterForward, 0);
		RCFilter_Update(&rcFilterBackward, 0);

		motorInf.direction = IDLE;
		motorInf.forwardPwm = 0;
	}
	else
	{
		//clear the forward motor's pwm
		RIGHT_MOTOR_FORWARD(0);
		LEFT_MOTOR_FORWARD(0);

		pwmDuty = (CHANNEL_MIDDLE - CHANNEL_ERROR) - adcVal;

		//set the duty map 0-100
		pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 100.0f);
		//limit the duty to 100
		pwmDuty = (pwmDuty > 100)? 100 : pwmDuty;

		//rc filter
		pwmDuty = RCFilter_Update(&rcFilterBackward, pwmDuty);

		RIGHT_MOTOR_BACKWARD((uint8_t)pwmDuty);
		LEFT_MOTOR_BACKWARD((uint8_t)pwmDuty);

		motorInf.direction = BACKWARD;
		motorInf.forwardPwm = pwmDuty;
	}
}

/**
 * @brief control the motor right and left
 * @param[in] read the channel1 adc value
 * @return none
 */
static void motorRightLeft(uint16_t adcVal)
{
	float pwmDuty;
	float rightMotorPwm;
	float leftMotorPwm;

	if(adcVal > (CHANNEL_MIDDLE + CHANNEL_ERROR))
	{
		if(motorInf.direction == FORWARD)
		{
			// if channel value between 1550 - 1950, pwmDuty can be 0-400
			pwmDuty = adcVal - (CHANNEL_MIDDLE + CHANNEL_ERROR);

			//set the duty map 0-100
			pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 100.0f);

			//add and sub %10 percent from the left and right motor
			leftMotorPwm = motorInf.forwardPwm + pwmDuty * 0.7f;
			rightMotorPwm = motorInf.forwardPwm - pwmDuty * 0.7f;

			leftMotorPwm = (leftMotorPwm > 100) ? 100 : leftMotorPwm;
			leftMotorPwm = (leftMotorPwm < 0) ? 0 : leftMotorPwm;

			rightMotorPwm = (rightMotorPwm > 100) ? 100 : rightMotorPwm;
			rightMotorPwm = (rightMotorPwm < 0) ? 0 : rightMotorPwm;

			rcFilterRight.out[0] = rcFilterForward.out[0];
			rcFilterLeft.out[0] = rcFilterForward.out[0];

			rightMotorPwm = RCFilter_Update(&rcFilterRight, rightMotorPwm);
			leftMotorPwm = RCFilter_Update(&rcFilterLeft, leftMotorPwm);

			LEFT_MOTOR_FORWARD(leftMotorPwm);
			RIGHT_MOTOR_FORWARD(rightMotorPwm);
		}
		else if(motorInf.direction == IDLE)
		{
			// if channel value between 1550 - 1950, pwmDuty can be 0-400
			pwmDuty = adcVal - (CHANNEL_MIDDLE + CHANNEL_ERROR);

			//set the duty map 0-90
			pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 90.0f);

			leftMotorPwm = pwmDuty;
			rightMotorPwm = pwmDuty;

			rightMotorPwm = RCFilter_Update(&rcFilterRight, rightMotorPwm);
			leftMotorPwm = RCFilter_Update(&rcFilterLeft, leftMotorPwm);

			LEFT_MOTOR_FORWARD(leftMotorPwm);
			RIGHT_MOTOR_BACKWARD(rightMotorPwm);
		}
		else
		{
			// if channel value between 1550 - 1950, pwmDuty can be 0-400
			pwmDuty = adcVal - (CHANNEL_MIDDLE + CHANNEL_ERROR);

			//set the duty map 0-100
			pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 100.0f);

			//add and sub %10 percent from the left and right motor
			leftMotorPwm = motorInf.forwardPwm + pwmDuty * 0.7f;
			rightMotorPwm = motorInf.forwardPwm - pwmDuty * 0.7f;

			leftMotorPwm = (leftMotorPwm > 100) ? 100 : leftMotorPwm;
			leftMotorPwm = (leftMotorPwm < 0) ? 0 : leftMotorPwm;

			rightMotorPwm = (rightMotorPwm > 100) ? 100 : rightMotorPwm;
			rightMotorPwm = (rightMotorPwm < 0) ? 0 : rightMotorPwm;

			rcFilterRight.out[0] = rcFilterForward.out[0];
			rcFilterLeft.out[0] = rcFilterForward.out[0];

			rightMotorPwm = RCFilter_Update(&rcFilterRight, rightMotorPwm);
			leftMotorPwm = RCFilter_Update(&rcFilterLeft, leftMotorPwm);

			LEFT_MOTOR_BACKWARD(leftMotorPwm);
			RIGHT_MOTOR_BACKWARD(rightMotorPwm);
		}
	}
	else if((adcVal < (CHANNEL_MIDDLE + CHANNEL_ERROR)) && (adcVal > (CHANNEL_MIDDLE - CHANNEL_ERROR)))
	{
		RCFilter_Update(&rcFilterRight, 0);
		RCFilter_Update(&rcFilterLeft, 0);
	}
	else
	{
		if(motorInf.direction == FORWARD)
		{
			// if channel value between 1550 - 1950, pwmDuty can be 0-400
			pwmDuty = (CHANNEL_MIDDLE - CHANNEL_ERROR) - adcVal;

			//set the duty map 0-100
			pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 100.0f);

			//add and sub %10 percent from the left and right motor
			leftMotorPwm = motorInf.forwardPwm - pwmDuty * 0.7f;
			rightMotorPwm = motorInf.forwardPwm + pwmDuty * 0.7f;

			leftMotorPwm = (leftMotorPwm > 100) ? 100 : leftMotorPwm;
			leftMotorPwm = (leftMotorPwm < 0) ? 0 : leftMotorPwm;

			rightMotorPwm = (rightMotorPwm > 100) ? 100 : rightMotorPwm;
			rightMotorPwm = (rightMotorPwm < 0) ? 0 : rightMotorPwm;

			rcFilterRight.out[0] = rcFilterForward.out[0];
			rcFilterLeft.out[0] = rcFilterForward.out[0];

			rightMotorPwm = RCFilter_Update(&rcFilterRight, rightMotorPwm);
			leftMotorPwm = RCFilter_Update(&rcFilterLeft, leftMotorPwm);

			LEFT_MOTOR_FORWARD(leftMotorPwm);
			RIGHT_MOTOR_FORWARD(rightMotorPwm);
		}
		else if(motorInf.direction == IDLE)
		{
			// if channel value between 1550 - 1950, pwmDuty can be 0-400
			pwmDuty = (CHANNEL_MIDDLE - CHANNEL_ERROR) - adcVal;

			//set the duty map 0-90
			pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 90.0f);

			leftMotorPwm = pwmDuty;
			rightMotorPwm = pwmDuty;

			rightMotorPwm = RCFilter_Update(&rcFilterRight, rightMotorPwm);
			leftMotorPwm = RCFilter_Update(&rcFilterLeft, leftMotorPwm);

			LEFT_MOTOR_BACKWARD(leftMotorPwm);
			RIGHT_MOTOR_FORWARD(rightMotorPwm);
		}
		else
		{
			// if channel value between 1550 - 1950, pwmDuty can be 0-400
			pwmDuty = (CHANNEL_MIDDLE - CHANNEL_ERROR) - adcVal;

			//set the duty map 0-100
			pwmDuty = ((pwmDuty / CHANNEL_RANGE) * 100.0f);

			//add and sub %10 percent from the left and right motor
			leftMotorPwm = motorInf.forwardPwm - pwmDuty * 0.7f;
			rightMotorPwm = motorInf.forwardPwm + pwmDuty * 0.7f;

			leftMotorPwm = (leftMotorPwm > 100) ? 100 : leftMotorPwm;
			leftMotorPwm = (leftMotorPwm < 0) ? 0 : leftMotorPwm;

			rightMotorPwm = (rightMotorPwm > 100) ? 100 : rightMotorPwm;
			rightMotorPwm = (rightMotorPwm < 0) ? 0 : rightMotorPwm;

			rcFilterRight.out[0] = rcFilterForward.out[0];
			rcFilterLeft.out[0] = rcFilterForward.out[0];

			rightMotorPwm = RCFilter_Update(&rcFilterRight, rightMotorPwm);
			leftMotorPwm = RCFilter_Update(&rcFilterLeft, leftMotorPwm);

			LEFT_MOTOR_BACKWARD(leftMotorPwm);
			RIGHT_MOTOR_BACKWARD(rightMotorPwm);
		}
	}

}
