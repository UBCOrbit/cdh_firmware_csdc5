#include <FreeRTOS.h>
#include <stdint.h>
#include <stm32h7xx_hal.h>
#include <task.h>

#include "os.h"

extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **, StackType_t **,
                                              uint32_t *);
StaticTask_t idle_task;
StackType_t idle_stack[configMINIMAL_STACK_SIZE];

/**
 * @brief FreeRTOS will call this to get some statically-allocated memory for
 * the idle task.
 */
extern "C" void
vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                              StackType_t **ppxIdleTaskStackBuffer,
                              uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &idle_task;
    *ppxIdleTaskStackBuffer = &*idle_stack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/**
 * @brief Configures the systick, and starts the kernel.
 *
 * This will not return, since the kernel takes over.
 */
void os_init() {
    HAL_SYSTICK_Config(SystemCoreClock / 1000);
    vTaskStartScheduler();
}

void Task::delay(uint32_t ms) { vTaskDelay(ms / portTICK_PERIOD_MS); }

/**
 * @brief Construct a new Wakeup Timer object.
 *
 * @param period How much time (in ms) a single period should occupy,
 * execution time *and* delay time.
 */
WakeupTimer::WakeupTimer(uint32_t period) : period(period), last_wake(0) {}

/**
 * @brief Call at the end of the task to delay the right amount of time.
 */
void WakeupTimer::sleep() {
    if (!last_wake)
        last_wake = xTaskGetTickCount();
    vTaskDelayUntil(&last_wake, period);
}
