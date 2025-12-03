#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "deck.h"

// FORWARD DECLARATION:
typedef struct game Game_t;

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
    Deck_t* discard_stack;
    PlayerHand_t* hand;
} Player_t;

int index_card_active(PlayerHand_t* hand);
void buy_cards_from_deck(PlayerHand_t* player_hand, Deck_t* deck, Deck_t* discard_stack);
void discard_active_card(Game_t* game, int energy);
void discard_all_hand(Player_t* player);
void player_init_new_turn(Player_t* player);

Player_t* init_player();
void free_player(Player_t* player);

#endif