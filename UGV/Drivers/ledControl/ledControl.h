/*
 * ledControl.h
 *
 *  Created on: Feb 9, 2024
 *      Author: ygork
 */

#ifndef LEDCONTROL_LEDCONTROL_H_
#define LEDCONTROL_LEDCONTROL_H_

#include "stm32f4xx_hal.h"
#include "rcReceiver.h"
#include "main.h"


#define LID_LED_DOWN			(960)
#define LID_LED_MIDDLE			(1525)
#define LID_LED_UP				(2100)
#define LID_LED_ERROR			(50)


typedef enum{
	LEDS_OFF,
	FRONT_LED_ON,
	ALL_LED_ON,
}LED_STATE;


LED_STATE UGV_ledControl(RcChannel * rcChannel);


#endif /* LEDCONTROL_LEDCONTROL_H_ */
