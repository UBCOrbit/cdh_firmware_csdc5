#pragma once

#include "hardware/hardware.h"

/**
 * @brief Access to the hardware RNG and a psuedorandom generator seeded by it.
 */
class Random : public Hardware {
public:
    void init() override;
    void deinit() override;

    uint32_t generate();

protected:
    RNG_HandleTypeDef handle; //< Handle to the hardware for secure rng.

};
