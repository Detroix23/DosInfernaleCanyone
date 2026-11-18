/**
 * # The Infernal Canyon.
 * game.c
*/
#ifndef INFERNAL_CANYON_GAME
#define INFERNAL_CANYON_GAME

#include <ncurses.h>
#include <stddef.h>
#include <stdio.h>

#include "./constants.c"
#include "./rng.c"
#include "./colors.c"
#include "./canyon.c"
#include "./cyclist.c"
#include "./state.c"
#include "./inputs.c"

void check_collisions(struct State *state) {
  int cx = state->canyon.xs[LINES - 2 - state->cyclist.y];
  int cw = state->canyon.width;
  if (
    state->cyclist.life > 0
    && (state->cyclist.x < cx - cw / 2
    || state->cyclist.x > cx + cw / 2)
  ) {
    state->cyclist.life -= 1;    
  }
  return;
}

/** Refreshes the screen to clear remaining drawings. */
void clean(struct State *state) {
  mvprintw(LINES - 2 - state->cyclist.y, state->cyclist.x, " "); 
  return;
}

void draw(struct State *state) {
  // Infos.
  attron(COLOR_PAIR(state->palette.text));
  mvprintw(
    LINES - 1, 0,
    "(?) SCORE: d=%d  CYCLE: l=%u x=%d y=%d d=%d dt=%d dCANY: w=%d x=%d",
    state->distance, state->cyclist.life, state->cyclist.x, state->cyclist.y,
    state->cyclist.dash_triggered, state->cyclist.dash_cooldown,
    state->canyon.width, state->canyon.xs[0]
  );

  // Canyon.
  attron(COLOR_PAIR(state->palette.canyon));
  for (int y = 0; y < LINES - 1; y++) {
    canyone_line(&state->canyon, y);      
  }

  // Cyclist.
  attron(COLOR_PAIR(state->palette.player));
  mvprintw(LINES - 2 - state->cyclist.y, state->cyclist.x, "%s", state->cyclist.icon); 

  return;
}

/** Mise-à-jour toutes les frames. */
void update(struct State *state, struct Bindings *bindings) {
  clean(state);

  canyon_roll(&state->canyon);
  cyclist_update(&state->cyclist);
  check_collisions(state);
  state->distance += 1;
  
  input_read(state, bindings);

  draw(state);
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

  printf("## Keys. \n");
  for (size_t i = 0; i < bindings.length; i++) {
    printf(
      "- `%c`: %s ;\n",
      bindings.bindings[i].key,
      bindings.bindings[i].description
    );
  }

  window_initialize();
  
  struct State state = state_create();

  while (is_running(&state)) {  
    state.input = getch();

    update(&state, &bindings);

    timeout(UPDATE_DELAY);
  }
  endwin();

  printf("\n## End. \n");
  printf("- Score: d=%d \n", state.distance);
  state_free(&state);
  bindings_free(&bindings);
}

#endif
