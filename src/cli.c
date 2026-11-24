/**
 * # The Infernal Canyon.
 * cli.c
*/
#ifndef INFERNAL_CANYON_CLI
#define INFERNAL_CANYON_CLI

#include <stddef.h>
#include <stdio.h>

/** Prints CLI arguments. */
void cli_print(size_t argc, char *argv[]) {
  if (argc <= 1) {
    printf("  - none. \n");
  } else { 
    for (size_t i = 1; i < argc; i++) {
      printf("  - `%s` \n", argv[i]);
    }
  }
  return;
}

#endif
