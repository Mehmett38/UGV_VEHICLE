/*
 * taskLoraCom.h
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#ifndef TASKS_TASKLORACOM_TASKLORACOM_H_
#define TASKS_TASKLORACOM_TASKLORACOM_H_

#include "FreeRTOS.h"
#include "task.h"
#include "SX1278.h"

//<<<<<<<<<<<<<<<<<<-MACROS->>>>>>>>>>>>>>
#define TASK_LORA_COM_PRIORITY					(UGV_TASK_PRIORITY_NORMAL)
#define TX_TIMEOUT								(2)
#define TX_STATUS								(0)
#define RX_STATUS								(1)

//<<<<<<<<<<<<<<<<<<-GLOBAL VARIABLES->>>>>>>>>>>>>>
extern TaskHandle_t hTaskLoraCom_s;


//<<<<<<<<<<<<<<<<<<-FUNCTION PROTOTYPES->>>>>>>>>>>>>>
void taskLoraCom(void *arg);
void dioIrqCallback();

#endif /* TASKS_TASKLORACOM_TASKLORACOM_H_ */
