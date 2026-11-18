/**
 * # The Infernal Canyon.
 * colors.c
*/
#ifndef INFERNAL_CANYON_COLORS
#define INFERNAL_CANYON_COLORS

#include <ncurses.h>

int COLOR_PLAYER = COLOR_RED;
int COLOR_BACKGROUND = COLOR_BLACK;
int COLOR_WALL = COLOR_WHITE;
int COLOR_TEXT = COLOR_CYAN;

struct Palette {
	int player;
	int canyon;
	int text;
};

struct Palette palette_create(void) {
	init_pair(1, COLOR_PLAYER, COLOR_BACKGROUND);
	init_pair(2, COLOR_WALL, COLOR_BACKGROUND);
	init_pair(3, COLOR_TEXT, COLOR_BACKGROUND);
	return (struct Palette) {
	  .player = 1,
	  .canyon = 2,
	  .text = 3,
	};
}

#endif
