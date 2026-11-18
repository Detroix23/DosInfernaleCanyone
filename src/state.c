/**
 * # The Infernal Canyon.
 * state.c
*/
#ifndef INFERNAL_CANYON_STATE
#define INFERNAL_CANYON_STATE

#include <ncurses.h>

#include "./colors.c"
#include "./canyon.c"
#include "./cyclist.c"

/** Global shared game state. */
struct State {
  NCURSES_BOOL running;
  char input;
  int distance;
  struct Canyon canyon;
  struct Cyclist cyclist;
  struct Palette palette;
};

/** Create the initial state. */
struct State state_create(void) {
  struct State state = {
    .running = TRUE,
    .input = ' ',
    .distance = 0,
    .canyon = canyon_create(),
    .cyclist = cyclist_create(),
    .palette = palette_create(),
  };
  mvprintw(LINES - 1, 0, "(?) x=%d", state.cyclist.x);

  return state;
}

/** Destroy appropriately the state. */
void state_free(struct State *state) {
  canyon_free(&state->canyon);
  return;
}

void set_quiting(struct State *state) { state->running = FALSE; }

NCURSES_BOOL is_running(struct State *state) { return (
  state->running
  && (
    state->cyclist.life > 0
    || state->distance < 23
  )
); }

/** Démo couleurs random */
void change_randomly_colors(struct State *state) {
	COLOR_BACKGROUND = rand()%8;
	COLOR_TEXT = rand()%8;
	COLOR_PLAYER = rand()%8;
	COLOR_WALL = rand()%8;
	state->palette = palette_create();
	return;
	
}

#endif
