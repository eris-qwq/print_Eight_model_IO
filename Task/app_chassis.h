#ifndef APP_CHASSIS_H
#define APP_CHASSIS_H

#include "FreeRTOS.h"
#include "task.h"

#define CHASSIS_TASK_PRIORITY   (tskIDLE_PRIORITY + 2U)
#define CHASSIS_TASK_STACK_SIZE (256U)

/* Chassis control task entry; currently runs infrared line tracking. */
void ChassisTask(void *argument);

#endif
