/**
 * # The Infernal Canyon.
 * game.c
*/
#ifndef INFERNAL_CANYON_GAME
#define INFERNAL_CANYON_GAME

#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

#include "./constants.c"
#include "./rng.c"
#include "./colors.c"
#include "./canyon.c"
#include "./cyclist.c"
#include "./state.c"
#include "./inputs.c"
#include "./draw.c"
#include "./maths.c"
#include "./fire.c"

int x = 0;

void check_collisions(struct State *state) {
  if (
    state->cyclist.life > 0
    && 
    (!(is_in_canyon(&state->canyon, state->cyclist.x, LINES - 2 - state->cyclist.y)))){
    state->cyclist.life -= 1;    
  }
  return;
}

/** 
 * Draw component for the `CANYON` menu state.
 * Actual gameplay.
 */
void draw_menu_canyon(struct State *state) {
  attron(COLOR_PAIR(state->palette.text));
  mvprintw(
    LINES - 1, 0,
    "(?) SCORE: d=%d CYCLE: l=%u x=%d y=%d d=%d dt=%d CANY: w=%d x=%d",
    state->distance, state->cyclist.life, state->cyclist.x, state->cyclist.y,
    state->cyclist.dash_triggered, state->cyclist.dash_cooldown,
    state->canyon.width, state->canyon.xs[0]
  );

  // Canyon.
  attron(COLOR_PAIR(state->palette.canyon));
  for (int y = 0; y < LINES - 1; y++) {
    canyone_line(&state->canyon, y);      
  }

	// Fire
	for (int i = 0; i < LINES-1; i++){
		for (int j = 0; j < COLS; j++){
			if (!(is_in_canyon(&state->canyon, j, i))){
				mvprintw(i, j, "%c", get_char_fire(state->fire.structure[i][j].heat, state->palette));
			}
		}
	}

  // Cyclist.
  attron(COLOR_PAIR(state->palette.player));
  mvprintw(LINES - 2 - state->cyclist.y, state->cyclist.x, "%s", state->cyclist.icon); 
  
  return;
}

/**
 * Main junction to draw all menu states.
 */
void draw(struct State *state) {
  // Infos.
  switch (state->menu) {
    case START:
      mvprintw(0, 0, "(WIP) Start menu.");
      return;
    case CANYON:
      draw_menu_canyon(state);
      return;
    case DEATH:
      mvprintw(0, 0, "(WIP) Death menu.");
      return;
    case QUITTING:
      mvprintw(0, 0, "(WIP) Quitting menu.");
      return;
  }

  return;
}

/** Mise-à-jour toutes les frames. */
void update(struct State *state, struct Bindings *bindings) {
  //clean(state); /!\ Need to be refactored, useless for now
  canyon_roll(&state->canyon);
  cyclist_update(&state->cyclist);
  check_collisions(state);
  state->distance += 1;
  fire_update(&state->fire);
  
  input_read(state, bindings);

  return;
}

void window_initialize(void) {
  // Crée l'objet écran `stdscr`.
  initscr();
  noecho();
  // Initialise les couleurs
  start_color();
  // Positione le curseur au tout début de l'écran.
  curs_set(0);
  refresh();
  // Débloque les appels à `getch`.
  nodelay(stdscr, TRUE);

  return;
}

/** Start the `ncurses` windows. */
void run(void) {
  // Crée l'object `rng`
  rng_create();

  struct Bindings bindings = bindings_create(); // (struct Bindings) {NULL, 0};
  bindings_print(&bindings);

  window_initialize();
  
  struct State state = state_create();
  while (is_running(&state)) {  
    state.input = getch();
    update(&state, &bindings);
    draw(&state);

    timeout(UPDATE_DELAY);
  }
  endwin();

  printf("\n## End. \n");
  printf("- Score: d=%d \n", state.distance);
  state_free(&state);
  bindings_free(&bindings);
}

#endif
