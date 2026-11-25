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
#include "./fire.c"

/** # `Menu` state. */ 
enum Menu {
  START,
  CANYON,
  DEATH,
  QUITTING,
};

/** Global shared game state. */
struct State {
  enum Menu menu;
  NCURSES_BOOL delay_input; 
  char input;
  int distance;
  struct Canyon canyon;
  struct Cyclist cyclist;
  struct Palette palette;
  struct Fire fire;
};

/** Create the initial state. */
struct State state_create(void) {
  struct Sprite cyclist_sprite = sprite(
    vector2d(3, 2),
    string(
      " ^ "
      "/8\\",
      6
    )
  );

  struct State state = {
    .menu = CANYON,
    .input = ' ',
    .delay_input = FALSE,
    .distance = 0,
    .canyon = canyon_create(),
    .cyclist = cyclist_create(cyclist_sprite),
    .palette = palette_create(),
    .fire = fire_create(),
  };

  return state;
}

/** Destroy appropriately the state. */
void state_free(struct State *state) {
  canyon_free(&state->canyon);
  cyclist_free(&state->cyclist);
  fire_free(&state->fire);
  return;
}

void set_quitting(struct State *state) { state->menu = QUITTING; }

NCURSES_BOOL is_running(struct State *state) { return (
  state->menu != QUITTING
  && (
    state->cyclist.life > 0
  )
); }

/** Démo couleurs random */
void change_randomly_colors(struct State *state) {
	COLOR_BACKGROUND = rng_next() % 8;
	COLOR_TEXT = rng_next() % 8;
	COLOR_PLAYER = rng_next() % 8;
	COLOR_WALL = rng_next() % 8;
	state->palette = palette_create();
	return;
	
}

#endif
