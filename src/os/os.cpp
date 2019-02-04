#include <FreeRTOS.h>
#include <stdint.h>
#include <task.h>

#include "os.h"

extern "C" void vApplicationGetIdleTaskMemory(StaticTask_t **, StackType_t **,
                                              uint32_t *);
StaticTask_t idle_task;
StackType_t idle_stack[configMINIMAL_STACK_SIZE];

extern "C" void
vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer,
                              StackType_t **ppxIdleTaskStackBuffer,
                              uint32_t *pulIdleTaskStackSize) {
    *ppxIdleTaskTCBBuffer = &idle_task;
    *ppxIdleTaskStackBuffer = &*idle_stack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void os_init() { vTaskStartScheduler(); }
