#ifndef _UTILS_H_
#define _UTILS_H_

#include "game.h"
#include <stdlib.h>

void must_init(_Bool test, const char* description, Game_t* game);

void shuffle_array(Card_t* array, int size);

#endif