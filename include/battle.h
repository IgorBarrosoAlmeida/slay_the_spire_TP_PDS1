#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "enemy.h"
#include "player.h"
#include <stdbool.h>
#include <stdlib.h>

// FORWARD DECLARATION:
typedef struct game Game_t;

typedef struct battle {
    Enemy_t* enemys;
    int n_enemys;
    _Bool isPlayerTurn;
} Battle_t;

void battle(Game_t* game);

Battle_t init_battle(int n_enemys);

void free_battle(Battle_t battle);
int index_selected_enemy(Enemy_t* enemys, int n_enemys);

#endif