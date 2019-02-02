#include <FreeRTOS.h>
#include <stm32h7xx_hal.h>
#include <task.h>

#include "clock.h"
#include "hardware_init.h"
#include "os.h"

#if TRILLIUM==1
const int led_pin = GPIO_PIN_0;
#elif TRILLIUM==2
const int led_pin = GPIO_PIN_7;
#elif TRILLIUM==3
const int led_pin = GPIO_PIN_14;
#endif

int main() {
    clock_init();
    hardware_init();

    HAL_GPIO_WritePin(GPIOB, led_pin, GPIO_PIN_SET);

    // Does not return.
    os_init();
}
