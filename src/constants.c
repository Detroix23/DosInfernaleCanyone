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
const char CUSTOM_LEFT_KEY = 'h'; 
const char CUSTOM_RIGHT_KEY = 'l';
// Pour démo couleur
const char KEY_RANDOM_COLOR = 'f';

#endif
