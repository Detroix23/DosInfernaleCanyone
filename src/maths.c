/**
 * # The Infernal Canyon.
 * maths.c
*/
#ifndef INFERNAL_CANYON_MATHS
#define INFERNAL_CANYON_MATHS

#include <ncurses.h>

/**
 * # `int` `Vector2D`.
 */
struct Vector2D {
  int x;
  int y;
};

/** Creates a `Vector2D`. */
struct Vector2D vector2d(int x, int y) {
  return (struct Vector2D) {x, y};
}

int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

/** Clamp `v` between `a` and `b` such that :
 * ```maths
 * a <= v' <= b
 * ```
 */
int clamp(int a, int v, int b) { return max(a, min(v, b)); }

#endif
