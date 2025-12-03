#include "player.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

/*
===============================
    player hand functions
===============================
*/
PlayerHand_t* init_player_hand()
{
    PlayerHand_t* hand = malloc(sizeof(PlayerHand_t));

    hand->actual_length = 5;
    hand->max_length = 5;
    hand->cards = (Card_t*)malloc(sizeof(Card_t) * hand->max_length);

    for (int i = 0; i < hand->max_length; i++) {
        hand->cards[i].cost = 1;
        hand->cards[i].effect = 3;
        hand->cards[i].type = ATACK;
        hand->cards[i].active = false;
    }
    hand->cards[0].active = true;

    return hand;
}

int index_card_active(PlayerHand_t* hand)
{
    for (int i = 0; i < hand->actual_length; i++) {
        if (hand->cards[i].active) {
            return i;
        }
    }
}

/*
===============================
    player functions
===============================
*/
Player_t* init_player()
{
    Player_t* player = (Player_t*)malloc(sizeof(Player_t));
    player->health = PLAYER_MAX_HEALTH;
    player->shield = 0;
    player->energy = PLAYER_MAX_ENERGY;

    player->deck = init_deck();
    player->hand = init_player_hand();
    return player;
}

void free_player(Player_t* player)
{
    if (!player)
        return;

    free_deck(player->deck);

    if (player->hand) {
        free(player->hand->cards);
        free(player->hand);
    }

    free(player);
}
