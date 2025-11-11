#ifndef _DECK_H_
#define _DECK_H_

typedef enum {
    SPECIAL = 0,
    DEFENSE = 1,
    ATACK = 2,
} Type_t;

typedef struct card {
    Type_t type;
    int cost;
    int effect;
    // char* description;
} Card_t;

typedef struct deck {
    Card_t* cards;
    int max_length;
    int actual_length;
} Deck_t;

Deck_t init_deck();

#endif