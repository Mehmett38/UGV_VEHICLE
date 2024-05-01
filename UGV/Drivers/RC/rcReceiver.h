/*
 * rcReceiver.h
 *
 *  Created on: Jan 23, 2024
 *      Author: Mehmet Dincer
 */

#ifndef RCRECEIVER_H_
#define RCRECEIVER_H_


#include "stm32f4xx_hal.h"


#define TIM2_CHANNEL_NUMBER		(4)			//!< use 4 channel from timer2
#define TIM_CLOCK           	(90000000)	//!< apb1: timer base frequency
#define PRESCALAR  				(900)		//!< timer prescaler value
#define REF_CLOCK			 	(TIM_CLOCK/(PRESCALAR))
#define CHANNEL_MIDDLE			(1525)

typedef struct{
	uint16_t channel1;
	uint16_t channel2;
	uint16_t channel3;
	uint16_t channel4;
}RcChannel;

extern RcChannel rcChannel_s;
extern uint8_t rcActive;				//!< check for rc controller is active


void UGV_rcReceiverInit();


#endif /* RCRECEIVER_H_ */
