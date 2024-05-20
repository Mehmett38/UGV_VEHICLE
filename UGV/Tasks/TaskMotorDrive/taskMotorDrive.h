/*
 * taskMotorDrive.h
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#ifndef TASKS_TASKMOTORDRIVE_TASKMOTORDRIVE_H_
#define TASKS_TASKMOTORDRIVE_TASKMOTORDRIVE_H_


//<<<<<<<<<<<<<<-LIBRARIES->>>>>>>>>>>>>>
#include "FreeRTOS.h"
#include "task.h"
#include "ugvDef.h"
#include "MotorDrive.h"
#include "rcReceiver.h"
#include "ledControl.h"
#include "Servo/cameraServo.h"

//<<<<<<<<<<<<<<<<<<-MACROS->>>>>>>>>>>>>>>>>
#define TASK_MOT_DRIVE_PRIORITY					(UGV_TASK_PRIORITY_HIGH)

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
extern TaskHandle_t hTaskMotDrive_s;

//<<<<<<<<<<<<<<-FUNCTION PROTOTYPES->>>>>>>>>>>>>>
void taskMotorDrive(void *arg);

#endif /* TASKS_TASKMOTORDRIVE_TASKMOTORDRIVE_H_ */
