#include <stm32h7xx_hal.h>

#include "interrupts.h"

extern "C" void xPortSysTickHandler();

void handle_systick() {
    HAL_IncTick();
    xPortSysTickHandler();
}

#if TRILLIUM == 1
const int led_pin = GPIO_PIN_14;
#elif TRILLIUM == 2
const int led_pin = GPIO_PIN_7;
#elif TRILLIUM == 3
const int led_pin = GPIO_PIN_0;
#endif

bool led = false;

void handle_exti15_10_irq() {
    HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    HAL_EXTI_D1_ClearFlag(13);
}
