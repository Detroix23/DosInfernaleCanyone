/**
 * # The Infernal Canyon.
 * system.c
*/
#ifndef INFERNAL_CANYON_SYSTEM
#define INFERNAL_CANYON_SYSTEM

#include <stdio.h>
#include <stdlib.h>
#include "ncurses.h"

/**
 * Exit the game with an error `message`.
 * Sort of stronger `assert`.
 * Prefer the macro `throw` to not have to pass `file, line, function`.
 */
void throwi(
  char *message,
  const char *file,
  const unsigned line,
  const char *function
) {
  endwin();
  fprintf(stderr, "\n(X) %s:%d %s() %s.\n", file, line, function, message);
  exit(1);
}

/** Shorter `throw` call with only `condition` and `message`. */
#define throw(message) \
  throwi(message, __FILE__, __LINE__, __func__)

/** Prints directly to `stderr` */
#define eprintf(format, ...) \
  fprintf(stderr, format, __VA_ARGS__)

/**
 * Safe `malloc` that throws on error.
 * Prefer the marco `salloc` for easier info handling.
 */
void *salloci(
  char *id,
  size_t type_size,
  size_t count,
  const char *file,
  const unsigned line,
  const char *function
) {
  size_t size = type_size * count;
  void *p = malloc(size);
  if (
    size < sizeof(char)
    || p == NULL
  ) {
    eprintf("%s", "\n");
    eprintf("│ id=%s \n", id);
    eprintf("├─ type_size=%ld \n", type_size);
    eprintf("├─ count=%ld", count);
    throwi("Memory allocation failed for `id`", file, line, function);
  }
  return p;
}

/** Shorter `salloci` call. */
#define salloc(id, type_size, count) \
  salloci(id, type_size, count, __FILE__, __LINE__, __func__)

#endif
