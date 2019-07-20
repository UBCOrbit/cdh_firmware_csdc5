#include "hardware/gpio.h"

GPIOPort::GPIOPort(Port port): port(port),
    pins({
        { *this, 0 }, { *this, 1 }, { *this, 2 }, { *this, 3 },
        { *this, 4 }, { *this, 5 }, { *this, 6 }, { *this, 7 },
        { *this, 8 }, { *this, 9 }, { *this, 10 }, { *this, 11 },
        { *this, 12 }, { *this, 13 }, { *this, 14 }, { *this, 15 }
    }),
    regs((GPIO_TypeDef *)((port * 0x400) + (uint32_t)GPIOA))
{}

GPIOPin& GPIOPort::get_pin(uint32_t pin) {
    return pins[pin];
}

void GPIOPort::init() {
    SET_BIT(RCC->AHB4ENR, 1 << port);
}

void GPIOPort::deinit() {
    CLEAR_BIT(RCC->AHB4ENR, 1 << port);
}

void GPIOPin::configure(Mode mode, Resistor res, uint32_t alt) {
    this->mode = mode;
    this->res = res;
    this->alt = alt;
    GPIO_InitTypeDef c{pin, mode, res, GPIO_SPEED_FREQ_LOW, alt};
    HAL_GPIO_Init(port.regs, &c);
}

void GPIOPin::reset() {
    HAL_GPIO_DeInit(port.regs, pin);
}

void GPIOPin::write(bool on) {
    HAL_GPIO_WritePin(port.regs, pin, (GPIO_PinState)on);
}

bool GPIOPin::read() {
    return HAL_GPIO_ReadPin(port.regs, pin);
}

HwOwner<GPIOPort>
GPIO_A(GPIOPort::Port::A),
GPIO_B(GPIOPort::Port::B),
GPIO_C(GPIOPort::Port::C),
GPIO_D(GPIOPort::Port::D),
GPIO_E(GPIOPort::Port::E),
GPIO_F(GPIOPort::Port::F),
GPIO_G(GPIOPort::Port::G),
GPIO_H(GPIOPort::Port::H),
GPIO_I(GPIOPort::Port::I),
GPIO_J(GPIOPort::Port::J),
GPIO_K(GPIOPort::Port::K);