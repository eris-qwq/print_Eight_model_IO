#include "bsp_delay.h"

static volatile uint32_t delay_remaining_ms;

void delay_ms(uint32_t ms)
{
    delay_remaining_ms = ms;
    while (delay_remaining_ms != 0U) {
    }
}

void SysTick_Handler(void)
{
    if (delay_remaining_ms != 0U) {
        --delay_remaining_ms;
    }
}
