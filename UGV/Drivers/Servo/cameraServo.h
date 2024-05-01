/*
 * cameraServo.h
 *
 *  Created on: Apr 28, 2024
 *      Author: Mehmet Dincer
 */

#ifndef SERVO_CAMERASERVO_H_
#define SERVO_CAMERASERVO_H_

#include "tim.h"
#include "rcReceiver.h"


#define CAMERA_RESET_CCR1_VAL			(60u)
#define CAMERA_MIN_CCR1_VAL				(25)
#define CAMERA_MAX_CCR1_VAL				(95)
#define ADC_ERROR						(3u)
#define ADC_SUB_POINT					(1106)
#define ADC_UPPER_POINT					(1953)
#define ADC_MIDDLE						(1530)

void UGV_cameraServoInit(TIM_HandleTypeDef * htim, uint32_t channel);
void UGV_cameraServoSetAngle(RcChannel * rcChannel_s);

#endif /* SERVO_CAMERASERVO_H_ */
