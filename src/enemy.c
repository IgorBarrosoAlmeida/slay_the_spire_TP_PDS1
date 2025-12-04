#include "enemy.h"
#include "constants.h"
#include <stdlib.h>

Enemy_t init_enemy(EnemyType_t type)
{
    Enemy_t enemy;
    enemy.type = type;
    enemy.next_action = 0;
    enemy.shield = 0;
    enemy.selected = false;
    enemy.died = false;

    if (enemy.type == BOSS) {
        enemy.health = BOSS_MIN_HEALTH + (rand() % (BOSS_MAX_HEALTH - BOSS_MIN_HEALTH + 1));
        enemy.n_actions = 4;

        enemy.actions = (Card_t*)malloc(sizeof(Card_t) * enemy.n_actions);

        enemy.actions[0].effect = 10 + (rand() % (35 - 10 + 1));
        enemy.actions[0].type = ATACK;

        enemy.actions[1].effect = 10 + (rand() % (35 - 10 + 1));
        enemy.actions[1].type = DEFENSE;

        enemy.actions[2].effect = 10 + (rand() % (35 - 10 + 1));
        enemy.actions[2].type = ATACK;

        enemy.actions[3].effect = 10 + (rand() % (35 - 10 + 1));
        enemy.actions[3].type = DEFENSE;

    } else if (enemy.type == WEAK) {
        enemy.health = WEAK_ENEMY_MIN_HEALTH + (rand() % (WEAK_ENEMY_MAX_HEALTH - WEAK_ENEMY_MIN_HEALTH + 1));

        int n_actions = 1 + (rand() % 2);
        enemy.n_actions = n_actions;
        enemy.actions = (Card_t*)malloc(sizeof(Card_t) * n_actions);

        enemy.actions[0].effect = 1 + (rand() % 10);
        enemy.actions[0].type = ATACK;
        if (n_actions == 2) {
            // randomize second action type
            enemy.actions[1].effect = 1 + (rand() % 10);
            enemy.actions[1].type = (rand() % 2) ? DEFENSE : ATACK;
        }
    } else {
        enemy.health = STRONG_ENEMY_MIN_HEALTH + (rand() % (STRONG_ENEMY_MAX_HEALTH - STRONG_ENEMY_MIN_HEALTH + 1));

        int n_actions = 2 + (rand() % 2);
        enemy.n_actions = n_actions;
        enemy.actions = (Card_t*)malloc(sizeof(Card_t) * n_actions);

        enemy.actions[0].effect = 5 + (rand() % (30 - 5 + 1));
        enemy.actions[0].type = ATACK;
        // randomize second action type
        enemy.actions[1].effect = 5 + (rand() % (30 - 5 + 1));
        enemy.actions[1].type = (rand() % 2) ? DEFENSE : ATACK;

        if (n_actions == 3) {
            // randomize third action type
            enemy.actions[2].effect = 5 + (rand() % (30 - 5 + 1));
            enemy.actions[2].type = (rand() % 2) ? DEFENSE : ATACK;
        }
    }

    enemy.max_health = enemy.health;

    return enemy;
}

void free_enemy(Enemy_t* enemy)
{
    if (!enemy->actions)
        return;
    free(enemy->actions);
}
