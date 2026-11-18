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

/* ## Window. */
/** Point d'entrée du TP9: canyon infernal. */
int main(void) {
  printf("# TP9: Canyon infernal.\n");
  printf("Repo: `https://github.com/Detroix23/DosInfernaleCanyone`\n\n");

	printf("## Keys. \n");
	printf("- Left : %c\n- Right : %c\n- Quit : %c\n\n", CUSTOM_LEFT_KEY, CUSTOM_RIGHT_KEY, KEY_QUIT);

  printf("## Settings. \n");
  printf("- RNG_SEED=%u \n", RNG_SEED);

  run();

  return EXIT_SUCCESS;
}
