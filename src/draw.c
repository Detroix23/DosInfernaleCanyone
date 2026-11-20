/**
 * # The Infernal Canyon.
 * draw.c
*/
#ifndef INFERNAL_CANYON_DRAW
#define INFERNAL_CANYON_DRAW

#include <limits.h>
#include <ncurses.h>
#include <stddef.h>
#include <stdlib.h>

#include "./maths.c"

/**
 * # Graphic `Sprite`.
 * Size :
 * - `size.x` : line | string length or column count ;
 * - `size.y` : line count ;
 */
struct Sprite {
  struct Vector2D size;
  char *data;
};

struct Sprite sprite_create(struct Vector2D size, char *data) {
  return (struct Sprite) {
    .size = size,
    .data = data,
  };
}

void sprite_free(struct Sprite *sprite) {
  free(sprite->data);
  return;
}

void sprite_draw(struct Vector2D position, struct Sprite *sprite) {
  for (int y = 0; y < sprite->size.y; y++) {
    for (int x = 0; x < sprite->size.x; x++) {
      mvaddch(
        position.y + y,
        position.x + x,
        sprite->data[sprite->size.y * y + x]
      );
    }
  }
}

#endif
