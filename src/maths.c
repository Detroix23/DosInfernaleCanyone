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

int max(int a, int b) { return (a > b) ? a : b; }

int min(int a, int b) { return (a < b) ? a : b; }

#endif
