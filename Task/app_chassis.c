#include "app_chassis.h"

#include "app_irtracking.h"
#include "bsp_at8236.h"

void ChassisTask(void *argument)
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
