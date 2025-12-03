#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "deck.h"
#include <stdbool.h>

/* TO-DO Deixar alocação dinamica menos propensa a erros */
typedef enum enemy_enum {
    WEAK = 0,
    STRONG = 1,
} EnemyType_t;

typedef struct enemy {
    int health;
    int max_health;
    int shield;
    EnemyType_t type;
    int next_action;
    int n_actions;
    _Bool selected;
    Card_t* actions;
} Enemy_t;

Enemy_t init_enemy(EnemyType_t type);
void free_enemy(Enemy_t* enemy);

#endif