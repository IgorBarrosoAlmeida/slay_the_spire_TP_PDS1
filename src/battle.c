#include "battle.h"
#include "game.h"

Battle_t init_battle(int n_enemys)
{
    Battle_t battle;
    battle.isPlayerTurn = true;
    battle.n_enemys = n_enemys;
    battle.enemys = (Enemy_t*)malloc(sizeof(Enemy_t) * n_enemys);
    for (int i = 0; i < n_enemys; i++) {
        // 5% de chance de ter um inimigo forte
        int strong_enemy_percent = 1 + (rand() % 100);
        if (strong_enemy_percent <= 5) {
            battle.enemys[i] = init_enemy(STRONG);
        } else {
            battle.enemys[i] = init_enemy(WEAK);
        }
    }

    return battle;
}

void free_battle(Battle_t battle)
{
    if (!battle.enemys) // Batalha não foi inicializada
        return;

    for (int i = 0; i < battle.n_enemys; i++) {
        free_enemy(&(battle.enemys[i]));
    }
    free(battle.enemys);
}

Type_t player_move(Player_t* player, Enemy_t* enemy)
{
    int card_index = index_card_active(player->hand);

    if (player->energy < player->hand->cards[card_index].cost) {
        return player->hand->cards[card_index].type;
    }

    switch (player->hand->cards[card_index].type) {
    case SPECIAL:
        discard_all_hand(player);
        buy_cards_from_deck(player->hand, player->deck, player->discard_stack);

        return SPECIAL;
        break;
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
    return player->hand->cards[card_index].type;
}

void enemy_move(Player_t* player, Enemy_t enemy)
{
    switch (enemy.actions[enemy.next_action].type) {
    case ATACK: {

        int damage = enemy.actions[enemy.next_action].effect;
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
        enemy.shield += enemy.actions[enemy.next_action].effect;
        break;
    }
    }

    if (enemy.next_action + 1 < enemy.n_actions) {
        enemy.next_action++;
    } else {
        enemy.next_action = 0;
    }
}

_Bool is_battle_over(Battle_t battle)
{
    _Bool result = true;

    for (int i = 0; i < battle.n_enemys; i++) {
        if (battle.enemys[i].health > 0) {
            result = false;
        }
    }

    return result;
}

void battle(Game_t* game)
{
    if (game->actual_battle.isPlayerTurn) {
        for (int i = 0; i < game->actual_battle.n_enemys; i++) {
            if (game->actual_battle.enemys[i].selected) {
                int energy = game->player->energy;
                Type_t type = player_move(game->player, &(game->actual_battle.enemys[i]));

                if (type != SPECIAL) {
                    discard_active_card(game, energy);
                }
                break;
            }
        }
    } else {
        for (int i = 0; i < game->actual_battle.n_enemys; i++) {
            (game->player, game->actual_battle.enemys[i]);
        }
        /* TO-DO: Fazer esperar um pouco pra ação dos inimigos */
    }

    if (game->player->health <= 0) {
        game->game_over = true;
    }
    if (is_battle_over(game->actual_battle)) {
        game->change_level = true;
    }
}