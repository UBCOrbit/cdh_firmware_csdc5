#include <stm32h7xx_hal.h>

#include "hardware/gpio.h"
#include "hardware/init.h"

/**
 * @brief Initialize peripherals and the HAL.
 *
 * This is temporary, and will be refactored into a more robust system for
 * initializing GPIOs.
 */
void hardware_init() { HAL_Init(); }

/**
 * @brief Stop the HAL from initializing the SysTick.
 *
 * We want to do it ourselves, later, when the scheduler is ready.
 */
HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority) {
    return HAL_OK; // We'll configure this once the scheduler is ready.
}
