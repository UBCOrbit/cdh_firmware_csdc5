#pragma once

#include <array>

#include <FreeRTOS.h>
#include <task.h>

class Task {
public:
    virtual void start() = 0;
    virtual void start_isr() = 0;
    virtual void stop() = 0;

    static void delay(const uint32_t ms);
};

template <unsigned stack_size> class StaticTask : public Task {
public:
    StaticTask(const char *name, uint32_t priority, void (*code)())
        : name(name), priority(priority), code(code) {
        static_assert(stack_size >= configMINIMAL_STACK_SIZE,
                      "Stack size is less than the minimum.");
        handle = xTaskCreateStatic(&callcode, name, stack_size, this, priority,
                                   stack.data(), &task);
        stop();
    }

    void start() override { vTaskResume(handle); }
    void start_isr() override {
        auto need_yield = xTaskResumeFromISR(handle);
        portYIELD_FROM_ISR(need_yield);
    }

    void stop() override { vTaskSuspend(handle); }

private:
    static void callcode(void *d) {
        auto t = static_cast<StaticTask<stack_size> *>(d);
        while (1)
            t->code();
    }

    TaskHandle_t handle;
    StaticTask_t task;
    const char *name;
    const uint32_t priority;
    void (*code)();
    std::array<StackType_t, stack_size> stack;
};

class WakeupTimer {
public:
    WakeupTimer(uint32_t period);

    void sleep();

private:
    uint32_t period;
    uint32_t last_wake;
};

void os_init();
