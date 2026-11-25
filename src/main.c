/**
 * # TP9: Canyon infernal.
 * main.c 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

#include "./constants.c"
#include "./game.c"

/** Point d'entrée du TP9: canyon infernal. */
int main(int argc, char *argv[]) {  
  printf("# TP9: Canyon infernal.\n");
  printf("Repo: `https://github.com/Detroix23/DosInfernaleCanyone`\n\n");

  printf("## Settings. \n");
  printf("- Debug : %s. \n", (DEBUG_ENABLED) ? "enabled" : "disabled");

  printf("\n- RNG_SEED=%u \n", RNG_SEED);

  run(argc, argv);

  return EXIT_SUCCESS;
}
