#include "battle.h"
#include "game.h"

Battle_t init_battle(int n_enemies, int level)
{
    Battle_t battle;
    battle.isPlayerTurn = true;
    battle.n_enemies = n_enemies;
    battle.enemies = (Enemy_t*)malloc(sizeof(Enemy_t) * n_enemies);

    if (n_enemies == 1) {
        battle.enemies[0] = init_enemy(BOSS);
    } else {
        for (int i = 0; i < n_enemies; i++) {
            // chance de aparecer um inimigo forte aumenta a cada fase
            int strong_enemy_percent = 1 + (rand() % 100);
            if (strong_enemy_percent <= 50) { // No enunciado está 5% mas achei mais condizente assim
                battle.enemies[i] = init_enemy(STRONG);
            } else {
                battle.enemies[i] = init_enemy(WEAK);
            }
        }
    }
    return battle;
}

void free_battle(Battle_t battle)
{
    if (!battle.enemies) // Batalha não foi inicializada
        return;

    for (int i = 0; i < battle.n_enemies; i++) {
        free_enemy(&(battle.enemies[i]));
    }
    free(battle.enemies);
}

void player_move(Player_t* player, Enemy_t* enemy)
{
    int card_index = index_card_active(player->hand);

    switch (player->hand->cards[card_index].type) {
    case SPECIAL:
        discard_all_hand(player);
        buy_cards_from_deck(player->hand, player->deck, player->discard_stack);

        return;
    case ATACK: {
        int damage = player->hand->cards[card_index].effect;

        if (enemy->shield != 0) {
            int aux = damage;
            damage -= enemy->shield;

            if (enemy->shield - aux <= 0) {
                enemy->shield = 0;
            } else {
                enemy->shield -= aux;
            }
        }

        if (damage > 0) {
            if (enemy->health - damage <= 0) {
                enemy->health = 0;
                enemy->died = true;
            } else {
                enemy->health -= damage;
            }
        }

        break;
    }
    case DEFENSE: {
        player->shield += player->hand->cards[card_index].effect;
        break;
    }
    }

    player->energy -= player->hand->cards[card_index].cost;
}

void enemy_move(Player_t* player, Enemy_t* enemy)
{
    switch (enemy->actions[enemy->next_action].type) {
    case ATACK: {
        int damage = enemy->actions[enemy->next_action].effect;
        if (player->shield != 0) {
            int aux = damage;
            damage -= player->shield;

            if (player->shield - aux <= 0) {
                player->shield = 0;
            } else {
                player->shield -= aux;
            }
        }

        if (damage > 0) {
            if (player->health - damage <= 0) {
                player->health = 0;
            } else {
                player->health -= damage;
            }
        }
        break;
    }
    case DEFENSE: {
        enemy->shield += enemy->actions[enemy->next_action].effect;
        break;
    }
    }

    if (enemy->next_action + 1 < enemy->n_actions) {
        enemy->next_action += 1;
    } else {
        enemy->next_action = 0;
    }
}

_Bool is_battle_over(Battle_t battle)
{
    _Bool result = true;

    for (int i = 0; i < battle.n_enemies; i++) {
        // Se um não morreu não acabou
        if (!battle.enemies[i].died) {
            result = false;
        }
    }

    return result;
}

int index_selected_enemy(Enemy_t* enemies, int n_enemies)
{
    for (int i = 0; i < n_enemies; i++) {
        if (enemies[i].selected) {
            return i;
        }
    }

    // Se não encontrar o inimigo
    return -1;
}

void battle(Game_t* game)
{
    if (game->actual_battle.isPlayerTurn) {
        int active_card = index_card_active(game->player->hand);

        if (game->player->hand->cards[active_card].type == ATACK) {
            for (int i = 0; i < game->actual_battle.n_enemies; i++) {
                if (game->actual_battle.enemies[i].selected) {
                    player_move(game->player, &(game->actual_battle.enemies[i]));

                    game->actual_battle.enemies[i].selected = false;
                    discard_active_card(game);
                    break;
                }
            }
        } else {
            Type_t type = game->player->hand->cards[active_card].type;
            player_move(game->player, NULL);

            if (type == DEFENSE) {
                discard_active_card(game);
            }
        }
        return;
    } else {
        for (int i = 0; i < game->actual_battle.n_enemies; i++) {
            if (!game->actual_battle.enemies[i].died) {
                enemy_move(game->player, &(game->actual_battle.enemies[i]));
            }
        }
    }

    if (game->player->health <= 0) {
        game->game_over = true;
    }
}