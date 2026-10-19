#include "app_main.h"
#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    app_main();

    /* The scheduler only returns when it cannot start. Keep the motors safe. */
    while (1) {
    }
}


