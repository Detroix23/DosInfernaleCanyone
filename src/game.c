/**
 * # The Infernal Canyon.
 * game.c
*/
#ifndef INFERNAL_CANYON_GAME
#define INFERNAL_CANYON_GAME

#include <ncurses.h>
#include <stdio.h>

#include "./constants.c"
#include "./cli.c"
#include "./arrays.c"
#include "./rng.c"
#include "./colors.c"
#include "./canyon.c"
#include "./cyclist.c"
#include "./state.c"
#include "./inputs.c"
#include "./draw.c"
#include "./maths.c"
#include "./fire.c"

void check_collisions(struct State *state) {
  if (
    state->cyclist.life > 0
    && !(is_in_canyon(&state->canyon, state->cyclist.x, state->cyclist.y))
  ) {
    state->cyclist.life -= 1;    
  }
  return;
}

/** 
 * Draw component for the `CANYON` menu state.
 * Actual gameplay.
 */
void draw_menu_canyon(struct State *state) {
  // Canyon.
  attron(COLOR_PAIR(state->palette.canyon));
  for (int y = 0; y < LINES - 1; y++) {
    canyone_line(&state->canyon, y);      
  }

	// Fire.
	for (int i = 0; i < LINES-1; i++){
		for (int j = 0; j < COLS; j++){
			if (!(is_in_canyon(&state->canyon, j, i))){
				mvprintw(
          i, 
          j, 
          "%c", 
          get_char_fire(state->fire.structure[i][j].heat, 
            state->palette
        ));
			}
		}
	}

  // Cyclist.
  attron(COLOR_PAIR(state->palette.player));
  sprite_x_centered(
    vector2d(
      state->cyclist.x,
      state->cyclist.y
    ),
    &state->cyclist.sprite
  );

  attron(COLOR_PAIR(state->palette.text));
  line_fill(LINES - 1, ' ');
  mvprintw(
    LINES - 1, 0,
    "(?) SCORE: d=%d blck=%s CYCLE: l=%u x=%d y=%d d=%d dt=%d CANY: w=%d x=%d",
    state->distance, state->delay_input ? "true" : "false",
    state->cyclist.life, state->cyclist.x, state->cyclist.y,
    state->cyclist.dash_triggered, state->cyclist.dash_cooldown,
    int_array_get(&state->canyon.widths, 0),
    int_array_get(&state->canyon.xs, 0)
  );

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
  input_read(state, bindings);
  canyon_roll(&state->canyon);  
  cyclist_update(&state->cyclist);
  check_collisions(state);
  state->distance += 1;
  fire_update(&state->fire);  
  return;
}

void window_initialize(void) {
  // Crée l'objet écran `stdscr`.
  initscr();
  noecho();
  // Initialise les couleurs
  start_color();
  // Positionne le curseur au tout début de l'écran.
  curs_set(0);
  refresh();
  return;
}

/** Start the `ncurses` windows. */
void run(size_t argc, char *argv[]) {
  rng_create();

  struct Bindings bindings = bindings_create(); // (struct Bindings) {NULL, 0};
  bindings_print(&bindings);

  window_initialize();
  
  struct State state = state_create();

  struct CliFlags flags = cli_create();
  cli_apply(argc, argv, &flags, &state);
  
  // Appels à `getch`.
  nodelay(stdscr, !state.delay_input);

  while (is_running(&state)) {  
    state.input = getch();
    update(&state, &bindings);
    draw(&state);

    timeout(UPDATE_DELAY);
  }
  endwin();
  printf("## CLI arguments. \n");
  cli_print(&flags);

  printf("\n## End. \n");
  printf("- Score: d=%d \n", state.distance);

  cli_free(&flags);
  state_free(&state);
  bindings_free(&bindings);
}

#endif
