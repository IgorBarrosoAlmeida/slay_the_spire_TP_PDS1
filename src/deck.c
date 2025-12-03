#include "deck.h"
#include "constants.h"
#include <stdlib.h>

Deck_t* init_deck()
{
    Deck_t* deck = malloc(sizeof(Deck_t));
    deck->max_length = DECK_LENGTH;
    deck->actual_length = DECK_LENGTH;
    deck->cards = (Card_t*)malloc(sizeof(Card_t) * DECK_LENGTH);

    // To-do: ler de um arquivo
    for (int i = 0; i < deck->max_length; i++) {
        deck->cards[i].cost = 1;
        deck->cards[i].effect = 3;
        deck->cards[i].type = ATACK;
    }

    return deck;
}

void free_deck(Deck_t* deck)
{
    if (deck == NULL) {
        return;
    }

    free(deck->cards);
    free(deck);
}