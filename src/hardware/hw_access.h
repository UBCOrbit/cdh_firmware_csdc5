#pragma once

#include "hardware.h"
#include "FreeRTOS.h"
#include "semphr.h"

template<typename T>
class HwAccess;

template<typename T>
class HwOwner {

public:

    HwOwner() { 
        refcount = 0;
        sam_schweigel = xSemaphoreCreateMutexStatic(&sams_buffer);
    }

    HwOwner(const HwOwner& o) = delete;
    HwOwner& operator=(const HwOwner& o) = delete;

    HwOwner(HwOwner&& o) = delete;
    HwOwner& operator=(HwOwner&& o) = delete;

    HwAccess<T> get_access() {
        if (refcount == 0) {
            hw.init();
        }
        ++refcount;
        return HwAccess(*this);
    }

private:

    friend class HwAccess<T>;

    void remove_access(const HwAccess<T>& a) {
        --refcount;
        if (refcount == 0) { hw.deinit(); }
    }

    T hw;
    uint32_t refcount;
    SemaphoreHandle_t sam_schweigel;
    StaticSemaphore_t sams_buffer;

};

template<typename T>
class HwAccess {
public:

    ~HwAccess() { owner.remove_access(*this); }

    void end() { owner.remove_access(*this); }

    void get_exclusive() {
        xSemaphoreTake(owner.sam_schweigel, portMAX_DELAY);
    }

    void release_exclusive() {
        xSemaphoreGive(owner.sam_schweigel);
    }

    T* operator->() { return &owner.hw; }

    T& operator*() { return owner.hw; }

private:

    friend class HwOwner<T>;

    HwAccess(HwOwner<T>& o): owner(o) {}

    HwAccess(const HwAccess& s) = delete;
    HwAccess& operator=(const HwAccess& s) = delete;

    HwAccess(HwAccess&& s) = delete;
    HwAccess& operator=(HwAccess&& s) = delete;

    HwOwner<T>& owner;

};
