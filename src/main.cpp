#include <stm32h7xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include "hardware_init.h"
#include "os.h"

StaticTask_t led_task;
StackType_t led_stack[configMINIMAL_STACK_SIZE];

void led_func(void*) {
    bool led = false;
    while (1) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (GPIO_PinState) led);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        led = !led;
    }
}

int main() {
    hardware_init();



    TaskHandle_t t;
    t = xTaskCreateStatic(&led_func, "LED", configMINIMAL_STACK_SIZE, nullptr, 1, led_stack, &led_task);
    vTaskResume(t);

    os_init();
}
