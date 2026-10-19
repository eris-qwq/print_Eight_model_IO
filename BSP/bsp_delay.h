#ifndef BSP_DELAY_H
#define BSP_DELAY_H

#include <stdint.h>

/* Blocking delay driven by the 1 ms SysTick interrupt. */
void delay_ms(uint32_t ms);

#endif
