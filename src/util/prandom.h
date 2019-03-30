#pragma once

#include <random>

class PRandom {
public:
    bool init(uint32_t seed);

    uint32_t fast();
    uint32_t secure();

protected:
    std::mt19937 twister; // Pseudorandom number generate state for fast rng.
};
