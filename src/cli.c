/**
 * # The Infernal Canyon.
 * cli.c
*/
#ifndef INFERNAL_CANYON_CLI
#define INFERNAL_CANYON_CLI

#include <ncurses.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "./system.c"
#include "./state.c"

struct Flag {
  char *token;
  void (*action)(struct State *state);
  char *description;
  NCURSES_BOOL selected;
};

struct CliFlags {
  size_t length;
  struct Flag *flags;
};

struct Flag flag(
  char *token,
  void (*action)(struct State *state),
  char *description
) {
  return (struct Flag) {token, action, description, FALSE};
}


void cli_enable_god(struct State *state) {
  state->cyclist.life = 100000;
}

void cli_blocking_input(struct State *state) {
  state->delay_input = TRUE;
}

/** Dynamically allocated cli `Flags`. */
struct CliFlags cli_create(void) {
  size_t l = 2;
  struct CliFlags flags = {
      l,
      (struct Flag *) salloc(
      "cli_create.flags",
      sizeof(struct Flag),
      l
    )
  };

  // Debug.
  flags.flags[0] = flag("--god", &cli_enable_god, "make the player invicible");
  flags.flags[1] = flag("--blocking-input", &cli_blocking_input, "blocks the game on input.");
  
  return flags;
}

void cli_free(struct CliFlags *flags) {
  free(flags->flags);
  return;
}

/** Prints CLI arguments. */
void cli_print(struct CliFlags *flags) {
  if (flags->length <= 1) {
    printf("  - none. \n");
  } else { 
    for (size_t i = 0; i < flags->length; i++) {
      printf(
        "(%s) `%s` : %s \n",
        (flags->flags[i].selected) ? "x" : " ",
        flags->flags[i].token,
        flags->flags[i].description
      );
    }
  }
  return;
}

void cli_apply(
  size_t argc,
  char *argv[],
  struct CliFlags *flags,
  struct State *state
) {
  for (size_t i = 1; i < argc; i++) {
    for (size_t j = 0; j < flags->length; j++) {
      if (strcmp(flags->flags[j].token, argv[i]) == 0) {
        // printf("(?) Checked %s \n", flags->flags[j].token);
        flags->flags[j].action(state);
        flags->flags[j].selected = TRUE;
      }
    }
  }
}

#endif
