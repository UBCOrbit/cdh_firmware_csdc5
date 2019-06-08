#pragma once

#include "hardware.h"
#include "freertos/include/semphr.h"

template<typename T>
class HwOwner;

template<typename T>
class HwAccess;

template<typename T>
class HwOwner {

public:

    friend class HwAccess;

    HwOwner() { 
        refcount = 0;
        sam_schweigel = xSemaphoreCreateMutex();
    }

    HwOwner(const HwOwner& o) = delete;
    HwOwner& operator=(const HwOwner& o) = delete;

    HwOwner(HwOwner&& o) = delete;
    HwOwner& operator=(HwOwner&& o) = delete;

    HwAccess get_access() {
        if (refcount == 0) {
            hw.init();
        }
        ++refcount;
        return HwAccess(*this);
    }

private:

    friend class HwAccess;

    void remove_access(const HwAccess& a) {
        --refcount;
        if (owned.refcount == 0) { hw.deinit(); }
    }

    T hw;
    uint32_t refcount;
    SemaphoreHandle_t sam_schweigel;

};

template<typename T>
class HwAccess {
public:

    HwAccess() {
        owned.remove_access(*this);
    }

    void get_exclusive() {
        xSemaphoreTake(owned.sam_schweigel, portMAX_DELAY);
    }

    void release_exclusive() {
        xSemaphoreGive(owned.sam_schweigel);
    }

private:

    friend class HwOwner;

    HwAccess(const OwnedHw& o): owned(o) {}

    HwAccess(const HwAccess& s) = delete;
    HwAccess& operator=(const HwAccess& s) = delete;

    HwAccess(HwAccess&& s) = delete;
    HwAccess& operator=(HwAccess&& s) = delete;

    OwnedHw<T>& owned;

};
