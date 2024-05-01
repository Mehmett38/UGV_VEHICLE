/*
 * taskSensor.h
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#ifndef TASKS_TASKSENSOR_TASKSENSOR_H_
#define TASKS_TASKSENSOR_TASKSENSOR_H_

//<<<<<<<<<<<<<<<<<<-LIBRARIES->>>>>>>>>>>>>>>>>
#include "FreeRTOS.h"
#include "task.h"
#include "ugvDef.h"

//<<<<<<<<<<<<<<<<<<-MACROS->>>>>>>>>>>>>>>>>
#define TASK_SENSOR_PRIORITY					(UGV_TASK_PRIORITY_VERY_HIGH)

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
extern TaskHandle_t hTaskSensor_s;

//<<<<<<<<<<<<<<-FUNCTION PROTOTYPES->>>>>>>>>>>>>>
void taskSensor(void *arg);


#endif /* TASKS_TASKSENSOR_TASKSENSOR_H_ */
