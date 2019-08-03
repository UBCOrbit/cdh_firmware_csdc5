#pragma once

#include "FreeRTOS.h"
#include "hardware.h"
#include "semphr.h"

template <typename T> class HwAccess;

template <typename T> class HwOwner {

public:
    HwOwner();
    template <class... Args> HwOwner(Args &&... args);

    HwOwner(const HwOwner &o) = delete;
    HwOwner &operator=(const HwOwner &o) = delete;

    HwOwner(HwOwner &&o) = delete;
    HwOwner &operator=(HwOwner &&o) = delete;

    HwAccess<T> get_access();

private:
    friend class HwAccess<T>;

    void remove_access(const HwAccess<T> &a);

    T hw;
    uint32_t refcount;
    SemaphoreHandle_t refcount_mutex;
    StaticSemaphore_t refcount_mutex_buffer;
    SemaphoreHandle_t access_mutex;
    StaticSemaphore_t access_mutex_buffer;
};

template <typename T> class HwAccess {
public:
    void end();

    ~HwAccess() { end(); }

    void get_exclusive();
    void release_exclusive();

    T *operator->() { return &owner.hw; }
    T &operator*() { return owner.hw; }

private:
    friend class HwOwner<T>;

    HwAccess(HwOwner<T> &o) : owner(o), exclusive(false) {}

    HwAccess(const HwAccess &s) = delete;
    HwAccess &operator=(const HwAccess &s) = delete;

    HwAccess(HwAccess &&s) = delete;
    HwAccess &operator=(HwAccess &&s) = delete;

    HwOwner<T> &owner;
    bool exclusive;
};

template <typename T> inline HwOwner<T>::HwOwner() {
    refcount = 0;
    refcount_mutex = xSemaphoreCreateMutexStatic(&refcount_mutex_buffer);
    access_mutex = xSemaphoreCreateRecursiveMutexStatic(&access_mutex_buffer);
}

template <typename T>
template <class... Args>
inline HwOwner<T>::HwOwner(Args &&... args) : hw(args...) {
    refcount = 0;
    refcount_mutex = xSemaphoreCreateMutexStatic(&refcount_mutex_buffer);
    access_mutex = xSemaphoreCreateRecursiveMutexStatic(&access_mutex_buffer);
}

template <typename T> inline HwAccess<T> HwOwner<T>::get_access() {
    xSemaphoreTake(refcount_mutex, portMAX_DELAY);
    if (refcount == 0) {
        hw.init();
    }
    ++refcount;
    xSemaphoreGive(refcount_mutex);
    return HwAccess(*this);
}

template <typename T>
inline void HwOwner<T>::remove_access(const HwAccess<T> &a) {
    xSemaphoreTake(refcount_mutex, portMAX_DELAY);
    --refcount;
    if (refcount == 0) {
        hw.deinit();
    }
    xSemaphoreGive(refcount_mutex);
}

template <typename T> inline void HwAccess<T>::end() {
    owner.remove_access(*this);
    if (exclusive) {
        release_exclusive();
    }
}

template <typename T> inline void HwAccess<T>::get_exclusive() {
    xSemaphoreTakeRecursive(owner.access_mutex, portMAX_DELAY);
    exclusive = true;
}

template <typename T> inline void HwAccess<T>::release_exclusive() {
    xSemaphoreGiveRecursive(owner.access_mutex);
    exclusive = false;
}
