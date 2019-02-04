#pragma once

#include <random>

extern std::mt19937 rng;

/* Blocks until the RNG produces a seed value, so be careful. */
void rng_init();
