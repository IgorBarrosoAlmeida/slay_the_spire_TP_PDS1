#ifndef _GAME_H_
#define _GAME_H_

/* TO-DO Deixar alocação dinamica menos propensa a erros */
#include "battle.h"
#include "player.h"
#include "renderer.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct game {
    Player_t* player;
    Renderer_t* renderer;
    Battle_t actual_battle;
    _Bool game_over;
    int level;
} Game_t;

Game_t* init_game();
void free_game(Game_t* game);

#endif