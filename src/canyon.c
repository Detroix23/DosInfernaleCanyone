/**
 * # The Infernal Canyon.
 * canyon.c
*/
#ifndef INFERNAL_CANYON_CANYON
#define INFERNAL_CANYON_CANYON

#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

#include "./constants.c"
#include "./system.c"
#include "./maths.c"
#include "./arrays.c"
#include "./rng.c"

/**
 * # Main `Canyon` state.
 */
struct Canyon {
  struct IntArray widths;
  int *xs;
  char border;
};

struct Canyon canyon_create(void) {
  struct Canyon canyon = {
    .widths = int_array_empty(LINES),
    .xs = (int *) salloc("canyon.xs", sizeof(int), LINES),
    .border = '#',
  };
  for (int i = 0; i < LINES; i++) {
    canyon.xs[i] = COLS / 2;
    int_array_set(&canyon.widths, i, CANYON_DEFAULT_WIDTH);
  }
  return canyon;
}

void canyon_free(struct Canyon *canyon) {
  free(canyon->xs);
  int_array_free(&canyon->widths);
  return;
}

/** Create and print a line at `y` of the Canyon. */
void canyone_line(struct Canyon *canyon, int y) {
  char *line = (char *) salloc("line", sizeof(char), COLS + 1);

  for (int i = 0; i < COLS; i++) {
    line[i] = (
      canyon->xs[y] - int_array_get(&canyon->widths, y) / 2 == i
      || canyon->xs[y] + int_array_get(&canyon->widths, y) / 2 == i
    ) ? canyon->border
    : ' ';
  }
  line[COLS] = '\0';

  mvprintw(y, 0, "%s", line);
  free(line);
  return;
}

void canyon_generate(struct Canyon *canyon) {
  int x_next = canyon->xs[0];
  int w_next = int_array_get(&canyon->widths, 0);
  switch (rng_next() % 7) {
    case 1:
    case 2:
      x_next += 1;
      break;
    case 3:
    case 4:
      x_next -= 1;
      break;
    case 5:
      w_next -= 1;
      break;
    case 6:
      w_next += 1;
      break;
  };
  canyon->xs[0] = clamp(
    int_array_get(&canyon->widths, 0) / 2,
    x_next,
    COLS - 1 - int_array_get(&canyon->widths, 0) / 2
  );
  int_array_set(&canyon->widths, 0, w_next);

  return;
}  

/** Roll the canyon. `0` is top, `LINES - 2` is last visible. */
void canyon_roll(struct Canyon *canyon) {
  for (int y = LINES - 1; y > 0; y--) {
    canyon->xs[y] = canyon->xs[y - 1];
    int_array_set(
      &canyon->widths,
      y,
      int_array_get(&canyon->widths, y - 1)
    );
  }
  canyon_generate(canyon);
  return;
}

bool is_in_canyon(struct Canyon *canyon, int x, int y){
	return (
	  (x >= canyon->xs[y] - int_array_get(&canyon->widths, y) / 2)
	  && (x <= canyon->xs[y] + int_array_get(&canyon->widths, y) /2)
	);
}

#endif
