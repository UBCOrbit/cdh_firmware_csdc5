#include "prandom.h"

#include <hydrogen.h>

bool PRandom::init(uint32_t seed) {
    static bool twister_initialized = false;
    if (!twister_initialized) {
        twister.seed(seed);
        twister_initialized = true;
        return false;
    } else {
        static size_t hydro_counter = 0;
        for (size_t i = 0; i < sizeof(seed); i++) {
            if (hydro_counter + i >= HYDRO_INIT_BUFFER_SIZE) { 
                return true;
            }
            hydro_init_buffer[hydro_counter + i] = seed & 0xFF;
            seed >>= sizeof(uint8_t);
        }
        hydro_counter += sizeof(seed);
        return hydro_counter >= HYDRO_INIT_BUFFER_SIZE;
    }
    return true;
}

uint32_t PRandom::fast() {
    return twister();
}

uint32_t PRandom::secure() {
    return hydro_random_u32();
}
