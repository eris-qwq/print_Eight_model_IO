#include "app_main.h"

#include "FreeRTOS.h"
#include "app_chassis.h"
#include "bsp_at8236.h"
#include "task.h"

void app_main(void)
{

    //创建任务
    const BaseType_t created = xTaskCreate(ChassisTask,
        "Chassis",
        CHASSIS_TASK_STACK_SIZE,
        NULL,
        CHASSIS_TASK_PRIORITY,
        NULL);


    //开启调度器
    if (created == pdPASS) {
        vTaskStartScheduler();
    }

    //失败保护，并开启B22绿灯快闪提示，正常情况下程序不会运行到这里
    Motor_Set_Pwm(Motor_M1, 0);
    Motor_Set_Pwm(Motor_M3, 0);
}

void vApplicationMallocFailedHook(void)
{
    __asm volatile ("cpsid i");
    for (;;) {
    }
}

void vApplicationStackOverflowHook(TaskHandle_t task, char *task_name)
{
    (void)task;
    (void)task_name;
    __asm volatile ("cpsid i");
    for (;;) {
    }
}
