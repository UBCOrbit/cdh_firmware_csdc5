#pragma once

#include <stm32h7xx_hal.h>

#include "hardware/hardware.h"
#include "hardware/hw_access.h"

class GPIOPort;

class GPIOPin {
public:

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

    void configure(Mode mode, Resistor res, uint32_t alt);
    void reset();

    void write(bool on);
    bool read();

private:

    friend class GPIOPort;

    GPIOPin(GPIOPort& port, uint32_t pin): port(port), pin(1 << pin) {}
    GPIOPin(const GPIOPin& p): port(p.port), pin(p.pin), mode(p.mode), res(p.res), alt(p.alt) {}

    GPIOPort& port;
    uint32_t pin;
    Mode mode;
    Resistor res;
    uint32_t alt;

};

class GPIOPort : public Hardware {
public:

    enum Port { A = 0, B, C, D, E, F, G, H, I, J, K };

    GPIOPort(Port port);
    GPIOPort(const GPIOPort& port) = delete;

    GPIOPin& get_pin(uint32_t pin);

    void init() override;
    void deinit() override;

private:

    friend class GPIOPin;

    Port port;
    GPIOPin pins[16];
    GPIO_TypeDef *regs;

};

extern HwOwner<GPIOPort> GPIO_A, GPIO_B, GPIO_C, GPIO_D, GPIO_E, GPIO_F, GPIO_G, GPIO_H, GPIO_I, GPIO_J, GPIO_K;