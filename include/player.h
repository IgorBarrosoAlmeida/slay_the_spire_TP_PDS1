#include "deck.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct player_hand {
    Card_t* cards;
    int max_length;
    int actual_length;
} PlayerHand_t;

typedef struct player {
    int heath;
    int shield;
    int energy;
    Deck_t deck;
    PlayerHand_t hand;
} Player_t;

void init_player(Player_t* player);

#endif