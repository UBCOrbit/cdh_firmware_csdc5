#include "hardware/gpio_new.h"

GPIOPort::GPIOPort(Port port): port(port) {
    regs = (GPIO_TypeDef *)((port * 0x400) + (uint32_t)GPIOA);
}

GPIOPin& GPIOPOrt::get_pin(uint32_t pin) {
    return pins[pin];
}

void GPIOPort::init() override {
    SET_BIT(RCC->AHB4ENR, 1 << port);
}

void GPIOPORT::deinit() override {
    CLEAR_BIT(RCC->AHB4ENR, 1 << port);
}

void GPIOPin::configure(Mode mode, Resistor res, uint32_t alt) {
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
GPIO_A(GPIOPort(GPIOPort::Port::A)),
GPIO_B(GPIOPort(GPIOPort::Port::B)),
GPIO_C(GPIOPort(GPIOPort::Port::C)),
GPIO_D(GPIOPort(GPIOPort::Port::D)),
GPIO_E(GPIOPort(GPIOPort::Port::E)),
GPIO_F(GPIOPort(GPIOPort::Port::F)),
GPIO_G(GPIOPort(GPIOPort::Port::G)),
GPIO_H(GPIOPort(GPIOPort::Port::H)),
GPIO_I(GPIOPort(GPIOPort::Port::I)),
GPIO_J(GPIOPort(GPIOPort::Port::J)),
GPIO_K(GPIOPort(GPIOPort::Port::K));