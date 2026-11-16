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


int max(int a, int b) {return (a > b) ? a : b;}
int min(int a, int b) {return (a < b) ? a : b;}

struct Canyon {
  int width;
  int *xs;
  char border;
};


/* ## States. */

struct Canyon canyon_create(void) {
  int *xs = malloc(sizeof(int) * LINES);
  for (int i = 0; i < LINES; i++) {
    xs[i] = COLS / 2;
  }
  return (struct Canyon) {
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
    line[i] = (canyon->xs[y] - canyon->width / 2 == i || canyon->xs[y] + canyon->width / 2 == i)
    ? canyon->border
    : ' ';
  }
  line[COLS] = '\0';

  mvprintw(y, 0, "%s", line);
  free(line);
  return;
}

struct Cyclist {
  int x;
  char *icon;
};

struct State {
  char input;
  struct Canyon canyon;
  struct Cyclist cyclist;
};

struct State state_create(void) {
  struct State state = {
    .input = ' ',
    .canyon = canyon_create(),
    .cyclist = (struct Cyclist) {
      .x = COLS / 2,
      .icon = "^",
    },
  };
  mvprintw(LINES - 1, 0, "(?) x=%d", state.cyclist.x);

  return state;
}

void state_free(struct State *state) {
  canyon_free(&state->canyon);
  return;
}

/* ## Window. */

NCURSES_BOOL is_running(struct State *state) {
  return (state->input != KEY_QUIT);  
}

/** Mise-à-jour toutes les frames. */
void update(struct State *state) {
  mvprintw(LINES - 2, state->cyclist.x, " "); 

  if (state->input == 'h') {
    state->cyclist.x = max(0, state->cyclist.x - 1);
  } else if (state->input == 'l') {
    state->cyclist.x = min(COLS - 1, state->cyclist.x + 1);
  }

  // Infos.
  mvprintw(LINES - 1, 0, "(?) x=%d", state->cyclist.x);

  // Canyon.
  for (int y = 0; y < LINES - 1; y++) {
    canyone_line(&state->canyon, y);      
  }

  // Cyclist.
  mvprintw(LINES - 2, state->cyclist.x, "%s", state->cyclist.icon); 


  return;
}

/** Start the `ncurses` windows. */
void run(void) {
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
  state_free(&state);
}

/** Point d'entrée du TP9: canyon infernal. */
int main(void) {
  printf("# TP9: Canyon infernal.\n");

  run();

  return EXIT_SUCCESS;
}
