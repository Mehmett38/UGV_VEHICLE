/*
 * ugvMain.h
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#ifndef MAIN_UGVMAIN_H_
#define MAIN_UGVMAIN_H_

//<<<<<<<<<<<<<<-LIBRARIES->>>>>>>>>>>>>>
#include "stm32f4xx_hal.h"
#include "main.h"
#include "usart.h"
#include "i2c.h"
#include "spi.h"
#include "ugvDef.h"
#include "MotorDrive.h"
#include "ledControl.h"
#include "QMC/QMC5883/qmc5883.h"
#include "pid.h"
#include "cameraServo.h"
#include "crc15.h"
#include "SX1278.h"
#include "gps.h"
#include "FreeRTOS.h"
#include "task.h"
#include "taskMotorDrive.h"
#include "taskLoraCom.h"
#include "taskSensor.h"
#include "database.h"


//<<<<<<<<<<<<<<-FUNCTION PROTOTYPES->>>>>>>>>>>>>>
void ugvMain(void);
void ugvSystemInit();


#endif /* MAIN_UGVMAIN_H_ */
