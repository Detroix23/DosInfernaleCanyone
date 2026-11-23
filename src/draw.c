/**
 * # The Infernal Canyon.
 * draw.c
*/
#ifndef INFERNAL_CANYON_DRAW
#define INFERNAL_CANYON_DRAW

#include <limits.h>
#include <ncurses.h>
#include <stddef.h>

#include "./arrays.c"
#include "./maths.c"

/**
 * # Graphic `Sprite`.
 * Size :
 * - `size.x` : line | string length or column count ;
 * - `size.y` : line count ;
 */
struct Sprite {
  struct Vector2D size;
  struct String string;
};

struct Sprite sprite(struct Vector2D size, struct String string) {
  return (struct Sprite) {
    .size = size,
    .string = string,
  };
}

void sprite_free(struct Sprite *sprite) {
  string_free(&sprite->string);
  return;
}

void sprite_draw(struct Vector2D position, struct Sprite *sprite) {
  for (int y = 0; y < sprite->size.y; y++) {
    for (int x = 0; x < sprite->size.x; x++) {
      mvaddch(
        position.y + y,
        position.x + x,
        string_get(&sprite->string, sprite->size.x * y + x)
      );
    }
  }
  return;
}

/** Draws `sprite` centered. */
void sprite_centered(struct Vector2D position, struct Sprite *sprite) {
  sprite_draw(
    vector2d(
      position.x - sprite->size.x / 2,
      position.y + sprite->size.y / 2
    ), 
    sprite
  );
  return;
}

void line_fill(int y, char character) {
  for (int x = 0; x <  COLS; x++) {
    mvaddch(y, x, character);
  }
}


#endif
