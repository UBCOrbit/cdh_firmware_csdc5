#pragma once

#include "hardware/hardware.h"

#include "hardware/hw_access.h"
#include <stm32h7xx_hal.h>

/**
 * @brief Access to the hardware RNG and a psuedorandom generator seeded by it.
 */
class Random : public Hardware {
public:
    Random() { handle.Instance = RNG; }

    void init() override;
    void deinit() override;

    uint32_t operator()();

protected:
    RNG_HandleTypeDef handle; //< Handle to the hardware for secure rng.
};

extern HwOwner<Random> random_instance;