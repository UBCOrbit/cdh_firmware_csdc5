#include <stm32h7xx_hal.h>

int main() {
    __GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef in;
    in.Mode = GPIO_MODE_OUTPUT_PP;
    in.Speed = GPIO_SPEED_FREQ_LOW;
    in.Pin = GPIO_PIN_7;
    in.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &in);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);

    while (1) {
	
    }
}
