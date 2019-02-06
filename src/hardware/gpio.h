#pragma once

#include <stm32h7xx_hal.h>

#include "hardware/hardware.h"

/**
 * @brief OO wrapper for GPIOs.
 */
class GPIO : public Hardware {
public:
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

    enum Resistor {
        None = GPIO_NOPULL,
        Pullup = GPIO_PULLUP,
        Pulldown = GPIO_PULLDOWN,
    };

    GPIO(GPIO_TypeDef *port, uint32_t pin, Mode mode, Resistor res,
         uint32_t alt);

    void set(bool on);

    void init() override;
    void deinit() override;

private:
    GPIO_TypeDef *port;
    uint32_t pin;
    Mode mode;
    Resistor res;
    uint32_t alt;
};
