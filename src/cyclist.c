/**
 * # The Infernal Canyon.
 * cyclist.c
*/
#ifndef INFERNAL_CANYON_CYCLIST
#define INFERNAL_CANYON_CYCLIST

#include <ncurses.h>

#include "./constants.c"
#include "./maths.c"
#include "./draw.c"

/** 
 * Player's character `Cyclist`.
 * 
 * **Fields** :
 * - `int` `x`;
 * - `int` `y`;
 * - `unsigned int` `life`;
 * - `unsigned int` `dash_cooldown`;
 * - `NCURSES_BOOL` `dash_triggered`;
 * - `struct Sprite` `sprite`;
 */
struct Cyclist {
  int x;
  int y;
  unsigned int life;
  unsigned int dash_cooldown;
  NCURSES_BOOL dash_triggered;
  struct Sprite sprite;
};

struct Cyclist cyclist_create(struct Sprite sprite) {
  return (struct Cyclist) {
    .x = COLS / 2,
    .y = 0,
    .life = 1,
    .dash_cooldown = 0,
    .dash_triggered = FALSE,
    .sprite = sprite,
  };
}

void cyclist_free(struct Cyclist *cyclist) {
  sprite_free(&cyclist->sprite);
  return;
}

void cyclist_trigger_dash(struct Cyclist *cyclist) {
  if (cyclist->dash_cooldown == 0) {
    cyclist->dash_triggered = TRUE;
  }
  return;
}

int cyclist_apply_dash(struct Cyclist *cyclist, int v) {
  if (v != 0 && cyclist->dash_triggered) {
    cyclist->dash_triggered = FALSE;
    cyclist->dash_cooldown = DASH_COOLDOWN;
    return v * DASH_FACTOR;
  } else {
    return v;
  };
}

/** Move the cyclist by a `x` and `y` offset. */
void cyclist_move(struct Cyclist *cyclist, int x, int y) {  
  cyclist->x = clamp(0, cyclist->x + cyclist_apply_dash(cyclist, x), COLS);
  cyclist->y = clamp(0, cyclist->y + cyclist_apply_dash(cyclist, y), LINES - 2);
  return;
}

void cyclist_update(struct Cyclist *cyclist) {
  cyclist->dash_cooldown = max(0, cyclist->dash_cooldown - 1);
  return;
}

#endif
