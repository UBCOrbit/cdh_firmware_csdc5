#pragma once

#include <utility>

#include <FreeRTOS.h>
#include <queue.h>

#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

template <typename F> class Mapped : F {
public:
    template <typename G> Mapped(G &&g) : F{FWD(g)} {}

    decltype(auto) block() { return (*this)(); }

    template <typename G> auto map(G &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block());
            }};
    }
};

template <typename F> Mapped(F &&)->Mapped<std::decay_t<F>>;

template <typename T> class Async {
public:
    Async(QueueHandle_t handle) : handle(handle) {}

    T block() {
        T ret;
        xQueueReceive(handle, &ret, portMAX_DELAY);
        return ret;
    }

    template <typename F> auto map(F &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block());
            }};
    }

    template <typename F> auto bind(F &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block()).block();
            }};
    }

protected:
    QueueHandle_t handle;
};

template <typename T> class Producer {
public:
    Producer() : handle(xQueueCreateStatic(1, sizeof(T), storage, &queue)) {}

    Async<T> promise() { return Async<T>(handle); }

    void fulfill(T x) { xQueueSend(handle, &x, portMAX_DELAY); }

    void fulfill_isr(T x) {
        BaseType_t task_woken = 0;
        xQueueSendFromISR(handle, &x, &task_woken);
        portYIELD_FROM_ISR(task_woken);
    }

protected:
    StaticQueue_t queue;
    QueueHandle_t handle;
    uint8_t storage[sizeof(T)];
};
