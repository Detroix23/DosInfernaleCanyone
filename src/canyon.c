/**
 * # The Infernal Canyon.
 * canyon.c
*/
#ifndef INFERNAL_CANYON_CANYON
#define INFERNAL_CANYON_CANYON

#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

#include "./system.c"
#include "./maths.c"
#include "./rng.c"

/**
 * # Main `Canyon` state.
 */
struct Canyon {
  int width;
  int *xs;
  char border;
};

struct Canyon canyon_create(void) {
  struct Canyon canyon = {
    .width = 20,
    .xs = (int *) salloc("canyon.xs", sizeof(int), LINES),
    .border = '#',
  };
  for (int i = 0; i < LINES; i++) {
    canyon.xs[i] = COLS / 2;
  }
  return canyon;
}

void canyon_free(struct Canyon *canyon) {
  free(canyon->xs);
  return;
}

/** Create and print a line at `y` of the Canyon. */
void canyone_line(struct Canyon *canyon, int y) {
  char *line = (char *) salloc("line", sizeof(char), COLS + 1);

  for (int i = 0; i < COLS; i++) {
    line[i] = (
      canyon->xs[y] - canyon->width / 2 == i
      || canyon->xs[y] + canyon->width / 2 == i
    ) ? canyon->border
    : ' ';
  }
  line[COLS] = '\0';

  mvprintw(y, 0, "%s", line);
  free(line);
  return;
}

int canyon_generate(struct Canyon *canyon) {
  int x_next = canyon->xs[0];
  switch (rng_next() % 3) {
    case 1:
      x_next += 1;
      break;
    case 2:
      x_next -= 1;
      break;
  }; 
  return max(canyon->width / 2, min(x_next, COLS - canyon->width / 2));
}  

/** Roll the canyon. `0` is top, `LINES - 2` is last visible. */
void canyon_roll(struct Canyon *canyon) {
  for (int y = LINES - 1; y > 0; y--) {
    canyon->xs[y] = canyon->xs[y - 1];
  }
  canyon->xs[0] = canyon_generate(canyon);
  return;
}

#endif
