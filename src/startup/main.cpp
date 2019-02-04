#include "hardware/clock.h"
#include "hardware/init.h"
#include "os/os.h"
#include "util/random.h"

int main() {
    clock_init();
    hardware_init();
    rng_init();

    // Does not return.
    os_init();
}
