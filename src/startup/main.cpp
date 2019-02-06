#include "hardware/clock.h"
#include "hardware/init.h"
#include "os/os.h"
#include "util/random.h"

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
    rng_init();

    // Does not return.
    os_init();
}
