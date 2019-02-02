#include <FreeRTOS.h>
#include <stm32h7xx_hal.h>
#include <task.h>

#include "clock.h"
#include "hardware_init.h"
#include "os.h"

int main() {
    clock_init();
    hardware_init();

    // Does not return.
    os_init();
}
