#pragma once

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
    virtual bool is_on() = 0;

    /**
     * @brief Estimate the idle power consumption of the peripheral.
     *
     * @return uint32_t Power consumption in mW when on.
     */
    virtual uint32_t idle_power() = 0;
};