#include "app_main.h"

#include "app_irtracking.h"
#include "bsp_at8236.h"
#include "bsp_delay.h"

void app_main(void)
{
    /* Keep both drivers idle while the infrared module powers up. */
    init_motor();
    delay_ms(1000);

    while (1) {
        LineWalking();
        delay_ms(IR_TRACKING_PERIOD_MS);
    }
}
