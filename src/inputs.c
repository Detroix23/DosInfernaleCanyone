/**
 * # The Infernal Canyon.
 * inputs.c
*/
#ifndef INFERNAL_CANYON_INPUTS
#define INFERNAL_CANYON_INPUTS

#include <stddef.h>
#include <stdlib.h>

#include "./constants.c"
#include "./system.c"
#include "./state.c"

/**
 * Groups `KeyBinding`s with their `action` and `description`.
 */
struct KeyBinding {
  char key;
  void (*action)(struct State *state);
  char *description;
};

struct KeyBinding key_binding(  
  char key,
  void (*action)(struct State *state),
  char *description
) {
  return (struct KeyBinding) {key, action, description};
} 

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
    .bindings = salloc("b.bindings", sizeof(struct KeyBinding), l),
    .length = l,
  };
  b.bindings[0] = key_binding(KEY_QUIT, &set_quitting, "quits the game");
  b.bindings[1] = key_binding(KEY_RANDOM_COLOR, &change_randomly_colors, "toggle epileptic mode");
  b.bindings[2] = key_binding(KEY_LEFT_CUSTOM, &cyclist_move_left, "move left");
  b.bindings[3] = key_binding(KEY_RIGHT_CUSTOM, &cyclist_move_right, "move right");
  b.bindings[4] = key_binding(KEY_UP_CUSTOM, &cyclist_move_up, "move up");
  b.bindings[5] = key_binding(KEY_DOWN_CUSTOM, &cyclist_move_down, "move down");
  b.bindings[6] = key_binding(KEY_DASH, &trigger_dash, "trigger dash");

  return b;
}

void bindings_free(struct Bindings *bindings) {
  free(bindings->bindings);

  return;
}

void bindings_print(struct Bindings *bindings) {
  printf("## Keys. \n");
  for (size_t i = 0; i < bindings->length; i++) {
    printf(
      "- `%c`: %s ;\n",
      bindings->bindings[i].key,
      bindings->bindings[i].description
    );
  }
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


#endif

