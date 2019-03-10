#pragma once

#include <optional>
#include <stdint.h>
#include <utility>

template <typename K, typename V, size_t S> class Lookup {
public:
    constexpr V operator[](K key) const {
        for (size_t i = 0; i < S; i++) {
            if (key == arr[i].first)
                return arr[i].second;
        }

        while (true)
            ;
    }

    const std::pair<K, V> arr[S];
};
