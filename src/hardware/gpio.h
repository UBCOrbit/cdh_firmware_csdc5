#pragma once

#include <stm32h7xx_hal.h>

#include "hardware/hardware.h"

/**
 * @brief OO wrapper for GPIOs.
 *
 * Usage example:
 *
 * ```
 * GPIO pin { GPIOB, 14, GPIO::OutputPP, GPIO::None, 0 };
 * pin.set(true); // turn the LED on
 * pin.deinit(); // save some power by switching the output off
 * ```
 */
class GPIO : public Hardware {
public:
    /**
     * @brief All 11 GPIO ports
     */
    enum Port { A, B, C, D, E, F, G, H, I, J, K };

    /**
     * @brief Type-safe mode selection.
     *
     * Technically, this combines both the "mode" field of the GPIO peripheral
     * with the "push-pull" field.
     */
    enum Mode {
        Input = GPIO_MODE_INPUT,
        OutputPP = GPIO_MODE_OUTPUT_PP,
        OutputOD = GPIO_MODE_OUTPUT_OD,
        AlternatePP = GPIO_MODE_AF_PP,
        AlternateOD = GPIO_MODE_AF_OD,
        Analog = GPIO_MODE_ANALOG,
    };

    /**
     * @brief Enumeration for possible resistor configurations.
     */
    enum Resistor {
        None = GPIO_NOPULL,
        Pullup = GPIO_PULLUP,
        Pulldown = GPIO_PULLDOWN,
    };

    GPIO(Port port, uint32_t pin, Mode mode, Resistor res, uint32_t alt);

    void set(bool on);
    bool read();

    void init() override;
    void deinit() override;

protected:
    GPIO_TypeDef *get_regs();

    Port port;
    GPIO_TypeDef *regs; //< Pointer to the GPIO register block.
    uint32_t pin;       //< The pin inside the port.
    Mode mode;          //< Configured mode and push-pull configuration.
    Resistor res; //< Resistor pull-up, pull-down, or floating configuration.
    uint32_t alt; //< Which alternate function is selected.

    static uint8_t pins[11]; //< Number of in-use pins per port.
};
