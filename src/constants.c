/**
 * # The Infernal Canyon.
 * constants.c
*/
#ifndef INFERNAL_CANYON_CONSTANTS
#define INFERNAL_CANYON_CONSTANTS

#include <stdint.h>

const int RNG_SEED = 6769;
const int RNG_MOD = UINT32_MAX;

const int UPDATE_DELAY = 20;

const char KEY_QUIT = 'q';
// LEFT_KEY et RIGHT_KEY : déjà prises par `ncurses`.
const char KEY_LEFT_CUSTOM = 'h'; 
const char KEY_RIGHT_CUSTOM = 'l';
const char KEY_UP_CUSTOM = 'k'; 
const char KEY_DOWN_CUSTOM = 'j';
const char KEY_DASH = ' ';
// Pour démo couleur
const char KEY_RANDOM_COLOR = 'f';

const int DASH_COOLDOWN = 60;
const int DASH_FACTOR = 3;

#endif
