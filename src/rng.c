/**
 * # The Infernal Canyon.
 * rng.c
*/
#ifndef INFERNAL_CANYON_RNG_C
#define INFERNAL_CANYON_RNG_C

#include <stdint.h>

#include "./constants.c"

/** Simple congruential random number generator. */
struct Rng {
  uint32_t current;
  uint32_t modulo;
  uint32_t a;
  uint32_t b;
};

/** Global singleton to reach out when generating RNG. */
struct Rng rng;

/** First initalization of the `rng` singleton. */
void rng_create(void) {
  rng = (struct Rng) {
    .current = RNG_SEED,
    .modulo = RNG_MOD,
    .a = 68987,
    .b = 1096838,
  };
}

/** Compute the next pesudo-random number, stores it and returns it. */
uint32_t rng_next() {
  return (rng.current = (rng.a * rng.current + rng.b) % rng.modulo);
}

#endif
