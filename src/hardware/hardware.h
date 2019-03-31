#pragma once

#include <stdint.h>

/**
 * @brief Interface for anything that can be toggled on or off to save power.
 */
class Hardware {
public:
    /**
     * @brief Power on the peripheral.
     */
    virtual void init() = 0;

    /**
     * @brief Power off the peripheral.
     */
    virtual void deinit() = 0;
};
