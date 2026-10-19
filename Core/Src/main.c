#include "app_main.h"
#include "ti_msp_dl_config.h"

int main(void)
{
    SYSCFG_DL_init();
    app_main();

    /* app_main() runs forever; keep the CPU safe if it ever returns. */
    while (1) {
    }
}


