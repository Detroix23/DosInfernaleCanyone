/**
 * # The Infernal Canyon.
 * arrays.c
*/
#include <stddef.h>
#include <ncurses.h>

#include "./system.c" 

/**
 * Wrapped `char` array to create a safe `String`.
 */
struct String {
    char *data;
    size_t length;
};

/** 
 * Creates a `String` by allocating heap memory for `data`. 
 *
 * **Warning** : resulting `struct` must be freed at the end. 
 */
struct String string(char data[], size_t length) {
  NCURSES_BOOL add_terminator = data[length - 1] != '\0';
  struct String s = {
    .data = (char *) salloc(
      "string.auto-data", 
      sizeof(char), 
      length + ((add_terminator) ? 1 : 0)
    ),
    .length = length + ((add_terminator) ? 1 : 0),
  };

  for (size_t i = 0; i < length; i++) {
    s.data[i] = data[i]; 
  }
  if (add_terminator) {
    s.data[length] = '\0';
  }

  // throw("String stop");
  return s;
}

void string_free(struct String *string) {
  free(string->data);
  return;
}

/** 
 * Gets the `char` at the `index` in `string`. 
 * 
 * On error : **throws** with output.
 */
char string_get(struct String *string, size_t index) {
  if (index >= string->length) {
    endwin();
    eprintf("\n| length=%ld\n", string->length);
    eprintf("| index=%ld", index);
    throw("`index` out of bounds");
  }
  return string->data[index];
}
