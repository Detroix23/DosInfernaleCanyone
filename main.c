/**
 * # TP9: Canyon infernal.
 * main.c 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

/* ## Base. */

const char KEY_QUIT = 'q';
const int UPDATE_DELAY = 20;
const int RNG_SEED = 6769;
const int RNG_MOD = UINT32_MAX;

int max(int a, int b) {return (a > b) ? a : b;}
int min(int a, int b) {return (a < b) ? a : b;}

/** Simple congruential random number generator. */
struct Rng {
  uint32_t current;
  uint32_t modulo;
  uint32_t a;
  uint32_t b;
};

struct Rng rng;

void rng_create(void) {
  rng = (struct Rng) {
    .current = RNG_SEED,
    .modulo = RNG_MOD,
    .a = 68987,
    .b = 1096838,
  };
}

/** Compute the next pseudo-random number, stores it and returns it. */
uint32_t rng_next() {
  return (rng.current = (rng.a * rng.current + rng.b) % rng.modulo);
}

/* ## States. */

struct Canyon {
  int width;
  int *xs;
  char border;
};

struct Canyon canyon_create(void) {
  int *xs = malloc(sizeof(int) * LINES);
  for (int i = 0; i < LINES; i++) {
    xs[i] = COLS / 2;
  }
  return (struct Canyon) {
    .width = 20,
    .xs = xs,
    .border = '#',
  };
}

void canyon_free(struct Canyon *canyon) {
  free(canyon->xs);
  return;
}

/** Create and print a line at `y` of the Canyon. */
void canyone_line(struct Canyon *canyon, int y) {
  char *line = malloc(sizeof(char) * (COLS + 1));
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

struct Cyclist {
  int x;
  int y;
  unsigned int life;
  char *icon;
};

struct Cyclist cyclist_create(void) {
  return (struct Cyclist) {
    .x = COLS / 2,
    .y = 0,
    .life = 1,
    .icon = "^",
  };
}

/** Global shared game state. */
struct State {
  char input;
  int distance;
  struct Canyon canyon;
  struct Cyclist cyclist;
};

struct State state_create(void) {
  struct State state = {
    .input = ' ',
    .distance = 0,
    .canyon = canyon_create(),
    .cyclist = cyclist_create(),
  };
  mvprintw(LINES - 1, 0, "(?) x=%d", state.cyclist.x);

  return state;
}

void state_free(struct State *state) {
  canyon_free(&state->canyon);
  return;
}

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

/* ## Window. */

NCURSES_BOOL is_running(struct State *state) {
  return (
    state->input != KEY_QUIT
    && (
      state->cyclist.life > 0
      || state->distance < 23
    )
  );  
}

void input_read(struct State *state) {
  if (state->input == 'h') {
    state->cyclist.x = max(0, state->cyclist.x - 1);
  } else if (state->input == 'l') {
    state->cyclist.x = min(COLS - 1, state->cyclist.x + 1);
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
  mvprintw(
    LINES - 1, 0,
    "(?) SCORE: d=%d  CYCLE: l=%u x=%d  CANY: w=%d x=%d",
    state->distance, state->cyclist.life, state->cyclist.x, state->canyon.width, state->canyon.xs[0]
  );

  // Canyon.
  for (int y = 0; y < LINES - 1; y++) {
    canyone_line(&state->canyon, y);      
  }

  // Cyclist.
  mvprintw(LINES - 2 - state->cyclist.y, state->cyclist.x, "%s", state->cyclist.icon); 

  return;
}

/** Mise-à-jour toutes les frames. */
void update(struct State *state) {
  clean(state);

  canyon_roll(&state->canyon);
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
  printf("Score: d=%d \n", state.distance);
  state_free(&state);
}

/** Point d'entrée du TP9: canyon infernal. */
int main(void) {
  printf("# TP9: Canyon infernal.\n");
  printf("Repo: `https://github.com/Detroix23/DosInfernaleCanyone`\n\n");

  printf("## Settings. \n");
  printf("- RNG_SEED=%u \n", RNG_SEED);

  run();

  return EXIT_SUCCESS;
}
