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
void handle_systick() {
    HAL_IncTick();
    xPortSysTickHandler();
}

bool led = false;

void handle_exti15_10_irq() {
    HAL_EXTI_D1_ClearFlag(13);
    led = !led;
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (GPIO_PinState)led);
}
