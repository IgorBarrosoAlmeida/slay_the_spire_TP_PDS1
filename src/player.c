#include "player.h"
#include "constants.h"

PlayerHand_t init_player_hand()
{
    PlayerHand_t hand;

    hand.actual_length = 5;
    hand.max_length = 5;
    hand.cards[hand.max_length];

    for (int i = 0; i < hand.max_length; i++) {
        hand.cards[i].cost = 1;
        hand.cards[i].effect = 3;
        hand.cards[i].type = ATACK;
    }
}

void init_player(Player_t* player)
{
    player->heath = PLAYER_MAX_HEALTH;
    player->shield = 0;
    player->energy = PLAYER_MAX_ENERGY;

    player->deck = init_deck();
    player->hand = init_player_hand();
}
