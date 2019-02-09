#pragma once

#include <random>

#include "hardware/hardware.h"

/**
 * @brief Access to the hardware RNG and a psuedorandom generator seeded by it.
 */
class Random : public Hardware {
public:
    void init() override;
    void deinit() override;
    uint32_t idle_power() override;

    uint32_t operator()();
    // Sorry! No secure random number generation for now while I sort out
    // blocking operations.

protected:
    RNG_HandleTypeDef handle; //< Handle to the hardware for secure rng.
    std::mt19937 twister; //< Pseudorandom number generate state for fast rng.
};
