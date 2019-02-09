#pragma once

#include <stdint.h>
#include <vector>

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

    /**
     * @brief Determine whether the peripheral is enabled or not.
     *
     * @return true Powered on.
     * @return false Powered off.
     */
    bool is_on();

    /**
     * @brief Estimate the idle power consumption of the peripheral.
     *
     * @return uint32_t Power consumption in uW when on.
     */
    virtual uint32_t idle_power() = 0;

protected:
    bool enabled; //< Provide a simple flag to track on/off for subclasses.
};