#include "hardware/clock.h"
#include "hardware/init.h"
#include "hardware/uart.h"
#include "os/os.h"

UART uart{UART::U3, 9600, GPIO::D, 8, 9};
GPIO led{GPIO::B, 7, GPIO::OutputPP, GPIO::None, 0};

void init_func();
StaticTask<128> init_task{"INIT", 0, init_func};

/**
 * @brief Main entry point for Trillium's firmware.
 *
 * This is the main entry point of the firmware, where execution starts.  Note
 * that the scheduler isn't running when this function starts, so that all the
 * low-level initializatoin of the clock, hardware, and other things may happen
 * undisturbed.
 *
 * Before this function is called, a few things happen in @file
 * startup/startup.s:
 * - The C runtime is initialized:
 *  - Zero-initialized globals are zeroed out in RAM.
 *  - Initialized globals' starting values are copied out of FLASH.
 * - Global C++ constructors are called (important).
 *
 * @return int This function never returns, because the scheduler starts.
 */
int main() {
    clock_init();
    hardware_init();

    init_task.start();

    // Does not return.
    os_init();
}

void init_func() {
    uart.init();
    uart.transmit((uint8_t *)"Hello!", 6).block();

    led.init();
    led.set(true);

    init_task.stop();
}
