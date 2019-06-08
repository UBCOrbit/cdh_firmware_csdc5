#include "prandom.h"

#include <hydrogen.h>

PRandom::PRandom(Random &random) {
    while (true) {
        uint32_t seed = random();

        if (hydro_init_buffer_counter < HYDRO_INIT_BUFFER_SIZE) {
            for (
              size_t i = 0;
              i < sizeof(seed) && hydro_init_buffer_counter < HYDRO_INIT_BUFFER_SIZE;
              i++, hydro_init_buffer_counter++
            ) {
                hydro_init_buffer[hydro_init_buffer_counter] = seed & 0xFF;
                seed >>= sizeof(uint8_t);
            }
        } else {
            twister.seed(seed);
            break;
        }
    }
}

uint32_t PRandom::fast() {
    return twister();
}

uint32_t PRandom::secure() {
    return hydro_random_u32();
}
