#include "deck.h"
#include "constants.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Deck_t* init_deck()
{
    Deck_t* deck = malloc(sizeof(Deck_t));
    deck->max_length = DECK_LENGTH;
    deck->actual_length = DECK_LENGTH;
    deck->cards = (Card_t*)malloc(sizeof(Card_t) * DECK_LENGTH);

    FILE* deck_file = fopen("./assets/deck.txt", "r");

    if (deck_file == NULL) {
        printf("Erro ao ler o arquivo, criando deck estatico");

        for (int i = 0; i < deck->max_length; i++) {
            deck->cards[i].cost = 1;
            deck->cards[i].effect = 3;
            deck->cards[i].type = ATACK;
            deck->cards[i].active = false;
        }
    } else {
        char line[30];
        int count = 0;

        // Limpa a legenda inicial
        fgets(line, 30, deck_file);
        while (fgets(line, 30, deck_file) != NULL) {
            if (count >= DECK_LENGTH) {
                break;
            }

            deck->cards[count].id = count;
            deck->cards[count].type = atoi(strtok(line, ";"));
            deck->cards[count].cost = atoi(strtok(NULL, ";"));
            deck->cards[count].effect = atoi(strtok(NULL, ";"));
            deck->cards[count].active = false;
            count++;
        }

        fclose(deck_file);
    }

    shuffle_array(deck->cards, deck->actual_length);

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