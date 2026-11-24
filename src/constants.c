/**
 * # The Infernal Canyon.
 * constants.c
*/
#ifndef INFERNAL_CANYON_CONSTANTS
#define INFERNAL_CANYON_CONSTANTS

#include <stdbool.h>
#include <stdint.h>
#include <ncurses.h>


/* Set the global DEBUG constant according to -DDEBUG compiler flag. */
#ifdef DEBUG
  /** `-DDEBUG` flag is on. */
  const bool DEBUG_ENABLED = true;
#else
  /** `-DDEBUG` flag is off. */ 
  const bool DEBUG_ENABLED = false;
#endif

const int RNG_SEED = 6769; // Highest score : 7409 :p
const int RNG_MOD = UINT32_MAX;

const int UPDATE_DELAY = 20;
const int CANYON_DEFAULT_WIDTH = 20;

const char KEY_QUIT = 'q';
// LEFT_KEY et RIGHT_KEY : déjà prises par `ncurses`.
const char KEY_LEFT_CUSTOM = 'h'; 
const char KEY_RIGHT_CUSTOM = 'l';
const char KEY_UP_CUSTOM = 'k'; 
const char KEY_DOWN_CUSTOM = 'j';
const char KEY_DASH = ' ';

// Pour dash
const int DASH_COOLDOWN = 60;
const int DASH_FACTOR = 3;

// Pour valeurs initiales du feu
const double INTENSITY = 0.5;
const double COOLING = 0.25;
const int MAX_FIRE = 100;

#endif
