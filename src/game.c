/**
 * # The Infernal Canyon.
 * game.c
*/
#ifndef INFERNAL_CANYON_GAME
#define INFERNAL_CANYON_GAME

#include <ncurses.h>

#include "./constants.c"
#include "./rng.c"
#include "./colors.c"
#include "./canyon.c"
#include "./cyclist.c"
#include "./state.c"

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

/** Démo couleurs random */
void change_randomly_colors(struct State *state) {
	COLOR_BACKGROUND = rand()%8;
	COLOR_TEXT = rand()%8;
	COLOR_PLAYER = rand()%8;
	COLOR_WALL = rand()%8;
	state->palette = palette_create();
	return;
	
}

/* # Window. */

NCURSES_BOOL is_running(struct State *state) {
  return (
    state->running
    && (
      state->cyclist.life > 0
      || state->distance < 23
    )
  );  
}

void set_quiting(struct State *state) { state->running = FALSE; }

void input_read(struct State *state) {
	if (state->input == KEY_QUIT) {
	  set_quiting(state);
	} if (state->input == KEY_RANDOM_COLOR) {
	  // Démo couleurs random.
		change_randomly_colors(state);
	} if (state->input == KEY_LEFT_CUSTOM) {
    cyclist_move(&state->cyclist, -1, 0);   
  } if (state->input == KEY_RIGHT_CUSTOM) {
    cyclist_move(&state->cyclist, 1, 0);    
  } if (state->input == KEY_UP_CUSTOM) {
    cyclist_move(&state->cyclist, 0, 1);    
  } if (state->input == KEY_DOWN_CUSTOM) {
    cyclist_move(&state->cyclist, 0, -1);    
  } if (state->input == KEY_DASH) {
    cyclist_trigger_dash(&state->cyclist);
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
void update(struct State *state) {
  clean(state);

  canyon_roll(&state->canyon);
  cyclist_update(&state->cyclist);
  check_collisions(state);
  state->distance += 1;
  
  input_read(state);

  draw(state);
  return;
}

/** Start the `ncurses` windows. */
void run(void) {
  // Crée l'object `rng`
  rng_create();

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

  struct State state = state_create();
  
  while (is_running(&state)) {  
    state.input = getch();

    update(&state);

    timeout(UPDATE_DELAY);
  }
  endwin();

  printf("\n## End. \n");
  printf("- Score: d=%d \n", state.distance);
  state_free(&state);
}

#endif
