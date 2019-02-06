#include "hardware/gpio.h"

GPIO::GPIO(GPIO_TypeDef *port, uint32_t pin, GPIO::Mode mode,
           GPIO::Resistor res, uint32_t alt)
    : port(port), pin(1 << pin), mode(mode), res(res), alt(alt) {
    init();
}

void GPIO::set(bool on) { HAL_GPIO_WritePin(port, pin, (GPIO_PinState)on); }

void GPIO::init() {
    GPIO_InitTypeDef c{pin, mode, res, alt};
    HAL_GPIO_Init(port, &c);
}

void GPIO::deinit() { HAL_GPIO_DeInit(port, pin); }
