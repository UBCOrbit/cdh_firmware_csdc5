#include "hardware/clock.h"
#include "hardware/gpio.h"
#include "hardware/init.h"
#include "hardware/uart.h"
#include "os/os.h"

UART uart{UART::U3, 9600, GPIO_D, 8, 9};
HwAccess<GPIOPort> port_access = GPIO_B.get_access();
GPIOPin pin = port_access->get_pin(8);

void init_func();
StaticTask<4096> init_task{"INIT", 0, init_func};

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

#include "util/i2a.h"

/**
 * The task that runs immediately after the processor starts.  Unlike
 * @ref main, it is safe to use asynchronous or blocking calls here.
 */
void init_func() {
    uart.init();

    pin.configure(GPIOPin::Mode::OutputPP, GPIOPin::Resistor::None, 0);
    for (int i = 0; i < 3; i++) {
        vTaskDelay(1000);
        pin.write(true);
        vTaskDelay(1000);
        pin.write(false);
    }

    uart.transmit("init complete\n\r").block();
    uart.deinit();

    init_task.stop();
}
