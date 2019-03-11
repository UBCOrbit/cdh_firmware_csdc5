#pragma once

#include <array>

#include <FreeRTOS.h>
#include <task.h>

/**
 * @brief Pure base class for all kernel tasks.
 *
 *  This should not be used directly.  All statically-allocated tasks like @ref
 *  StaticTask inherit from this so that common functions can be used across all
 * of them.
 */
class Task {
public:
    /**
     * @brief Start this task.
     *
     * This won't immediately yield execution to the task, but might transfer
     * control on the next SysTick.  Do not use this from an interrupt, use @ref
     * start_isr instead.
     */
    virtual void start() = 0;

    /**
     * @brief Start this task, and transfer control immediately out of the
     * interrupt if it has higher priority.
     */
    virtual void start_isr() = 0;

    /**
     * @brief Stop the task.
     */
    virtual void stop() = 0;

    /**
     * @brief Can be called from any task, and will pass control back to the
     * kernel.
     *
     * @param ms The number of milliseconds to wait.
     */
    static void delay(const uint32_t ms);
};

/**
 * @brief A task with a statically-allocated stack and control block.
 *
 * @tparam stack_size Number of *words* of stack to set aside for this task.
 */
template <unsigned stack_size> class StaticTask : public Task {
public:
    /**
     * @brief Construct a new Static Task object
     *
     * The code that's passed to this will be called repeatedly, so it should
     * delay (or stop itself) at the end up every call.
     *
     * @param name Only used for debugging and monitoring of tasks.
     * @param priority This task's priority. Higher priorities will not be
     * interupted by lower ones.
     * @param code Function pointer to this task's code.  (Can be a lambda, but
     * can't capture anything.)
     */
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

protected:
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

/**
 * @brief A timer for ensuring a precise timing cycle, taking into account the
 * execution time of the task.
 */
class WakeupTimer {
public:
    WakeupTimer(uint32_t period);

    void sleep();

private:
    uint32_t period;
    uint32_t last_wake;
};

void os_init();
