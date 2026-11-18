/**
 * # The Infernal Canyon.
 * canyon.c
*/
#ifndef INFERNAL_CANYON_CYCLIST
#define INFERNAL_CANYON_CYCLIST

#include <ncurses.h>

struct Cyclist {
  int x;
  int y;
  unsigned int life;
  char *icon;
};

struct Cyclist cyclist_create(void) {
  return (struct Cyclist) {
    .x = COLS / 2,
    .y = 0,
    .life = 1,
    .icon = "^",
  };
}

#endif
