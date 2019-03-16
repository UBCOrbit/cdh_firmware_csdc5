#pragma once

#include <utility>

#include <FreeRTOS.h>
#include <queue.h>

#define FWD(...) ::std::forward<decltype(__VA_ARGS__)>(__VA_ARGS__)

/**
 * @brief Helper class that is an @ref Async that has been mapped or
 * bound.
 *
 * This needs to be a separate class, because we can't just stored the
 * result type for the whole thing: we need to set aside enough space
 * to hold our closure's free variables, and there's no way to do that
 * without dynamic memory allocation (like std::function).
 */
template <typename F> class Mapped : F {
public:
    template <typename G> Mapped(G &&g) : F{FWD(g)} {}

    decltype(auto) block() { return (*this)(); }

    /**
     * @brief Apply a function to the Asnyc's result, when it is finished.
     *
     * @param f The function to map.
     *
     * @return A new Async, with the function's return value.
     */
    template <typename G> auto map(G &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block());
            }};
    }

    /**
     * @brief Apply a function returning another Async to the Async's
     * result, combining them into one Async.
     */
    template <typename G> auto bind(G &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block()).block();
            }};
    }
};

template <typename F> Mapped(F &&)->Mapped<std::decay_t<F>>;

/**
 * @brief Class representing computation or IO operation that has not
 * yet completed.
 *
 * The operation's result can be access through one of the scheduling
 * member functions, like @ref Async::block().
 *
 * Guaranteed to never spinlock, and instead hand control back to the
 * kernel while blocking on queues.
 */
template <typename T> class Async {
public:
    Async(QueueHandle_t handle) : handle(handle) {}

    T block() {
        T ret;
        xQueueReceive(handle, &ret, portMAX_DELAY);
        return ret;
    }

    /**
     * @brief Apply a function to the Asnyc's result, when it is finished.
     *
     * @param f The function to map.
     *
     * @return A new Async, with the function's return value.
     */
    template <typename F> auto map(F &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block());
            }};
    }

    /**
     * @brief Apply a function returning another Async to the Async's
     * result, combining them into one Async.
     */
    template <typename F> auto bind(F &&f) {
        return ::Mapped{
            [p = std::move(*this), f = FWD(f)]() mutable -> decltype(auto) {
                return f(p.block()).block();
            }};
    }

protected:
    QueueHandle_t handle;
};

/**
 * @brief Outgoing channel from making Async instances.
 *
 * This is the "in" channel of the RTOS queue.  Async instances are
 * just throway "out" channels representing the intent to block on a
 * result.
 */
template <typename T> class Producer {
public:
    Producer() : handle(xQueueCreateStatic(1, sizeof(T), storage, &queue)) {}

    /**
     * @brief Create an Async out of nothing, signaling that we will
     * fulfill our promise later.
     */
    Async<T> promise() { return Async<T>(handle); }

    /**
     * @brief Fulfill our promise.  *Do not* call from interrupts.
     */
    void fulfill(T x) { xQueueSend(handle, &x, portMAX_DELAY); }

    /**
     * Fulfill our promise, from an interrupt.
     */
    bool fulfill_isr(T x) {
        BaseType_t task_woken = 0;
        xQueueSendFromISR(handle, &x, &task_woken);
        return task_woken;
    }

    /**
     * This *must* be called if @ref fulfill_isr returns `true`.  It
     * should be called with the or'd results of all fulfills from
     * this ISR.
     */
    static void yield_isr(bool woke) { portYIELD_FROM_ISR(woke); }

protected:
    StaticQueue_t queue;
    QueueHandle_t handle;
    uint8_t storage[sizeof(T)];
};
