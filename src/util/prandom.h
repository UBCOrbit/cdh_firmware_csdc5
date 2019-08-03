#pragma once

#include <random>
#include "hardware/random.h"

class PRandom {
public:

    PRandom(Random &random);
    PRandom(PRandom &prandom);

    uint32_t fast();
    uint32_t secure();

protected:
    std::mt19937 twister; // Pseudorandom number generate state for fast rng.
};
