/*
 * ugvDef.h
 *
 *  Created on: May 1, 2024
 *      Author: Mehmet Dincer
 */

#ifndef HELPER_UGVDEF_H_
#define HELPER_UGVDEF_H_

//<<<<<<<<<<<<<<<<<<<<<<<<<>-LIBRARIES->>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "FreeRTOSConfig.h"
#include "stdint.h"

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<-MACROS->>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<-ENUMS->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef enum{
	UGV_STATUS_OK,
	UGV_STATUS_ERROR,
	UGV_STATUS_BUSY,
	UGV_STATUS_TIMEOUT
}UGV_status_e;

typedef enum{
	UGV_TASK_PRIORIT_IDLE = 0,
	UGV_TASK_PRIORITY_LOW = 15,
	UGV_TASK_PRIORITY_NORMAL = 28,
	UGV_TASK_PRIORITY_HIGH = 40,
	UGV_TASK_PRIORITY_VERY_HIGH = 50,
	UGV_TASK_PRIORITY_REAL_TIME = configMAX_PRIORITIES,
}UGV_TASK_PRIOTY_e;

//<<<<<<<<<<<<<<<<<<<<<<<<<<-STRUCTS->>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



#endif /* HELPER_UGVDEF_H_ */
