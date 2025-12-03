#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "deck.h"

/* TO-DO Deixar alocação dinamica menos propensa a erros */
typedef struct player_hand {
    Card_t* cards;
    int max_length;
    int actual_length;
} PlayerHand_t;

typedef struct player {
    int health;
    int shield;
    int energy;
    Deck_t* deck;
    PlayerHand_t* hand;
} Player_t;

int index_card_active(PlayerHand_t* hand);

Player_t* init_player();
void free_player(Player_t* player);

#endif