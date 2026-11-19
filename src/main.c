/**
 * # TP9: Canyon infernal.
 * main.c 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <ncurses.h>

#include "./constants.c"
#include "./game.c"

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

/* ## Window. */
/** Point d'entrée du TP9: canyon infernal. */
int main(int argc, char *argv[]) {
  printf("# TP9: Canyon infernal.\n");
  printf("Repo: `https://github.com/Detroix23/DosInfernaleCanyone`\n\n");

  printf("## Settings. \n");
  printf("- CLI arguments : \n");
  cli_print(argc, argv);
  
  printf("\n- RNG_SEED=%u \n", RNG_SEED);

  run();

  return EXIT_SUCCESS;
}
