#include <stm32h7xx_hal.h>

#include "interrupts.h"

extern "C" void xPortSysTickHandler();

void handle_systick() {
    HAL_IncTick();
    xPortSysTickHandler();
}
