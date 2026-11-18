/**
 * # The Infernal Canyon.
 * inputs.c
*/
#ifndef INFERNAL_CANYON_INPUTS
#define INFERNAL_CANYON_INPUTS

#include <stddef.h>
#include <stdlib.h>

#include "./constants.c"
#include "./state.c"

/**
 * Groups `KeyBinding`s with their `action` and `description`.
 */
struct KeyBinding {
  char key;
  void (*action)(struct State *state);
  char *description;
};

/**
 * Structured array of `KeyBinding`s.
 */
struct Bindings {
  struct KeyBinding *bindings;
  size_t length;
};

void cyclist_move_left(struct State *state) {
    cyclist_move(&state->cyclist, -1, 0);   
}
void cyclist_move_right(struct State *state) {
    cyclist_move(&state->cyclist, 1, 0);    
}
void cyclist_move_up(struct State *state) {
    cyclist_move(&state->cyclist, 0, 1);
}
void cyclist_move_down(struct State *state) {
    cyclist_move(&state->cyclist, 0, -1);    
}
void trigger_dash(struct State *state) {
    cyclist_trigger_dash(&state->cyclist);
}


struct Bindings bindings_create(void) {
  size_t l = 7;
  struct Bindings b = {
    .bindings = malloc(sizeof(struct KeyBinding) * l),
    .length = l,
  };
  b.bindings[0] = (struct KeyBinding) {KEY_QUIT, &set_quiting, "quits the game"};
  b.bindings[1] = (struct KeyBinding) {KEY_RANDOM_COLOR, &change_randomly_colors, "toggle epilleptic mode"};
  b.bindings[2] = (struct KeyBinding) {KEY_LEFT_CUSTOM, &cyclist_move_left, "move left"};
  b.bindings[3] = (struct KeyBinding) {KEY_RIGHT_CUSTOM, &cyclist_move_right, "move right"};
  b.bindings[4] = (struct KeyBinding) {KEY_UP_CUSTOM, &cyclist_move_up, "move up"};
  b.bindings[5] = (struct KeyBinding) {KEY_DOWN_CUSTOM, &cyclist_move_down, "move down"};
  b.bindings[6] = (struct KeyBinding) {KEY_DASH, &trigger_dash, "trigger dash"};

  return b;
}

void bindings_free(struct Bindings *bindings) {
  free(bindings->bindings);

  return;
}

void input_read(struct State *state, struct Bindings *bindings) {
  for (size_t i = 0; i < bindings->length; i++) {
    if (state->input == bindings->bindings[i].key) {
      bindings->bindings[i].action(state);
    }
  }  
	return;
}

/* Old conditions :
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
*/

#endif

