#include "deck.h"
#include "constants.h"

Deck_t init_deck()
{
    Deck_t deck;
    deck.max_length = DECK_LENGTH;
    deck.actual_length = DECK_LENGTH;
    deck.cards[DECK_LENGTH];

    for (int i = 0; i < deck.max_length; i++) {
        deck.cards[i].cost = 1;
        deck.cards[i].effect = 3;
        deck.cards[i].type = ATACK;
    }

    return deck;
}
