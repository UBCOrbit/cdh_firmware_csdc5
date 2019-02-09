#include <stm32h7xx_hal.h>

#include "FreeRTOS.h"
#include "interrupts.h"

extern "C" void xPortSysTickHandler();

/**
 * @brief Handle the Cortex's systick.
 *
 * The frequency of the systick is configured in @ref clock_init
 *
 */
void handle_systick() { xPortSysTickHandler(); }
