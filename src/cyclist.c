/**
 * # The Infernal Canyon.
 * cyclist.c
*/
#ifndef INFERNAL_CANYON_CYCLIST
#define INFERNAL_CANYON_CYCLIST

#include <ncurses.h>

#include "./constants.c"
#include "./maths.c"

/** Player's character */
struct Cyclist {
  int x;
  int y;
  unsigned int life;
  unsigned int dash_cooldown;
  NCURSES_BOOL dash_triggered;
  char *icon;
};

struct Cyclist cyclist_create(void) {
  return (struct Cyclist) {
    .x = COLS / 2,
    .y = 0,
    .life = 1,
    .dash_cooldown = 0,
    .dash_triggered = FALSE,
    .icon = "^",
  };
}

void cyclist_trigger_dash(struct Cyclist *cyclist) {
  if (cyclist->dash_cooldown == 0) {
    cyclist->dash_triggered = TRUE;
  }
  return;
}

int cyclist_apply_dash(struct Cyclist *cyclist, int v) {
  if (cyclist->dash_triggered) {
    cyclist->dash_triggered = FALSE;
    cyclist->dash_cooldown = DASH_COOLDOWN;
    return v * DASH_FACTOR;
  } else {
    return v;
  };
}

/** Move the cyclist by a `x` and `y` offset. */
void cyclist_move(struct Cyclist *cyclist, int x, int y) {  
  cyclist->x = max(
  0,
  min(cyclist->x + cyclist_apply_dash(cyclist, x),
  COLS));
  cyclist->y = max(
  0,
  min(cyclist->y + cyclist_apply_dash(cyclist, y),
  LINES - 2));

  return;
}

void cyclist_update(struct Cyclist *cyclist) {
  cyclist->dash_cooldown = max(0, cyclist->dash_cooldown - 1);
  
  return;
}

#endif
