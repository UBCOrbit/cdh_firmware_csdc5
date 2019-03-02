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
