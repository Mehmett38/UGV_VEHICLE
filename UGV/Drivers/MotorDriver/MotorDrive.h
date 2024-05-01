/*
 * MotorDrive.h
 *
 *  Created on: Feb 4, 2024
 *      Author: Mehmet Dincer
 */

#ifndef MOTORDRIVER_MOTORDRIVE_H_
#define MOTORDRIVER_MOTORDRIVE_H_

#include "stm32f4xx_hal.h"
#include "rcReceiver.h"
#include "RcFilter/rcFilter.h"
#include "PID.h"

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>>>>>
//!< time global variable
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<-MACROS->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define CHANNEL_DOWN				(1100)	//!< controller sub adc read value
#define CHANNEL_MIDDLE				(1525)	//!< controller idle state
#define CHANNEL_UP					(1950)	//!< controller up adc read value
#define CHANNEL_ERROR				(75)	//!< ADC read error
#define CHANNEL_RANGE				((CHANNEL_UP - CHANNEL_MIDDLE - CHANNEL_ERROR) * 1.0f)


//<<<<<<<<<<<<<<<<<<<<<<<<<<<-FUNCTION MACROS->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#define RIGHT_MOTOR_FORWARD(x)		(__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, x))
#define RIGHT_MOTOR_BACKWARD(x)		(__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, x))
#define LEFT_MOTOR_BACKWARD(x)		(__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, x))
#define LEFT_MOTOR_FORWARD(x)		(__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, x))

//<<<<<<<<<<<<<<<<<<<<<<<<<<<-ENUMS->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum{
	FORWARD,
	IDLE,
	BACKWARD
}MotorDirection;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<-STRUCTURE->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef struct{
	MotorDirection direction;
	uint8_t forwardPwm;
	uint8_t backwardPwm;
}MotorControl;


void UGV_motorInit();
void UGV_motorDrive(RcChannel * rcChannel, float azimuthAngle);


#endif /* MOTORDRIVER_MOTORDRIVE_H_ */
