#include "hardware/gpio.h"

/**
 * @brief Construct a new GPIOPort object
 *
 * @param port The register block pointing to the GPIO port.
 */
GPIOPort::GPIOPort(Port port)
    : port(port), pin_states({{*this, 0},
                              {*this, 1},
                              {*this, 2},
                              {*this, 3},
                              {*this, 4},
                              {*this, 5},
                              {*this, 6},
                              {*this, 7},
                              {*this, 8},
                              {*this, 9},
                              {*this, 10},
                              {*this, 11},
                              {*this, 12},
                              {*this, 13},
                              {*this, 14},
                              {*this, 15}}),
      regs((GPIO_TypeDef *)((port * 0x400) + (uint32_t)GPIOA)) {}

/**
 * @brief Get a pin object from the GPIO port.
 *
 * @param pin The pin number to get access to.
 */
GPIOPin GPIOPort::get_pin(uint32_t pin) { return GPIOPin(pin_states[pin]); }

/**
 * @brief Power on the GPIO port hardware.
 */
void GPIOPort::init() { SET_BIT(RCC->AHB4ENR, 1 << port); }

/**
 * @brief Power off the GPIO port hardware.
 */
void GPIOPort::deinit() { CLEAR_BIT(RCC->AHB4ENR, 1 << port); }

/**
 * @brief Configure a GPIO pin.
 *
 * @param Pin mode.
 * @param Input/output/alternate as well as the push-pull/open drain mode.
 * @param res Pull-up/pull-down resistor configuration.
 * @param If `mode` is @ref GPIO::AlternatePP or @ref GPIO::AlternateOD,
 * this selects the alternate function.
 */
void GPIOPin::configure(Mode mode, Resistor res, uint32_t alt) {
    state.mode = mode;
    state.res = res;
    state.alt = alt;
    GPIO_InitTypeDef c{state.pin, mode, res, GPIO_SPEED_FREQ_LOW, alt};
    HAL_GPIO_Init(state.port.regs, &c);
}

/**
 * @brief Rest the pin configuration.
 */
void GPIOPin::reset() { HAL_GPIO_DeInit(state.port.regs, state.pin); }

/**
 * @brief Write to a GPIO pin.
 *
 * @param on true = HIGH, false = low
 */
void GPIOPin::write(bool on) {
    HAL_GPIO_WritePin(state.port.regs, state.pin, (GPIO_PinState)on);
}

/**
 * @brief Read from a GPIO pin.
 *
 * @return true = HIGH, false = LOW
 */
bool GPIOPin::read() { return HAL_GPIO_ReadPin(state.port.regs, state.pin); }

HwOwner<GPIOPort> GPIO_A(GPIOPort::Port::A), GPIO_B(GPIOPort::Port::B),
    GPIO_C(GPIOPort::Port::C), GPIO_D(GPIOPort::Port::D),
    GPIO_E(GPIOPort::Port::E), GPIO_F(GPIOPort::Port::F),
    GPIO_G(GPIOPort::Port::G), GPIO_H(GPIOPort::Port::H),
    GPIO_I(GPIOPort::Port::I), GPIO_J(GPIOPort::Port::J),
    GPIO_K(GPIOPort::Port::K);