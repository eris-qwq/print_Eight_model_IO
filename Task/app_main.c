#include "app_main.h"

#include "FreeRTOS.h"
#include "app_irtracking.h"
#include "bsp_at8236.h"
#include "task.h"

#define LINE_TRACKING_TASK_PRIORITY   (tskIDLE_PRIORITY + 2U)
#define LINE_TRACKING_TASK_STACK_SIZE (256U)

static void LineTrackingTask(void *argument)
{
    (void)argument;

    /* Keep both drivers idle while the infrared module powers up. */
    init_motor();
    vTaskDelay(pdMS_TO_TICKS(1000U));

    TickType_t last_wake_time = xTaskGetTickCount();
    const TickType_t period = pdMS_TO_TICKS(IR_TRACKING_PERIOD_MS);

    for (;;) {
        LineWalking();
        vTaskDelayUntil(&last_wake_time, period);
    }
}

void app_main(void)
{
    const BaseType_t created = xTaskCreate(LineTrackingTask,
        "LineTrack",
        LINE_TRACKING_TASK_STACK_SIZE,
        NULL,
        LINE_TRACKING_TASK_PRIORITY,
        NULL);

    if (created == pdPASS) {
        vTaskStartScheduler();
    }

    /* Task creation or scheduler startup failed. Do not leave a motor active. */
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
