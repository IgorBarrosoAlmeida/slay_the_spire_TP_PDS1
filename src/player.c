#include "player.h"
#include "constants.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/*
===============================
    player hand functions
===============================
*/

PlayerHand_t* init_player_hand(Deck_t* deck, Deck_t* discard_stack)
{
    PlayerHand_t* hand = malloc(sizeof(PlayerHand_t));

    hand->max_length = 5;
    hand->cards = (Card_t*)malloc(sizeof(Card_t) * hand->max_length);
    buy_cards_from_deck(hand, deck, discard_stack);

    for (int i = 0; i < hand->max_length; i++) {
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

    // Se não tiver nenhuma ativa
    return -1;
}

void buy_cards_from_deck(PlayerHand_t* player_hand, Deck_t* deck, Deck_t* discard_stack)
{
    if (deck->actual_length == 0) {
        shuffle_array(discard_stack->cards, discard_stack->actual_length - 1);

        int count = 0;
        for (int i = discard_stack->actual_length - 1; i >= 0; i--) {
            deck->cards[count] = discard_stack->cards[i];
            deck->actual_length += 1;
            count++;
            discard_stack->actual_length -= 1;
        }
    }

    // Pega as cartas do final do baralho e colocam na mão do jogador
    for (int i = 1; i <= player_hand->max_length; i++) {
        player_hand->cards[i - 1] = deck->cards[deck->actual_length - i];
        player_hand->cards[i - 1].active = false;
    }
    player_hand->cards[0].active = true;
    player_hand->actual_length = player_hand->max_length;
    deck->actual_length -= player_hand->max_length;
}

Card_t discard(PlayerHand_t* hand, int card_index)
{
    Card_t card = hand->cards[card_index];

    // Move todas as cartas para uma posição antes da atual
    for (int i = 0; i < hand->actual_length; i++) {
        if (i > card_index) {
            hand->cards[i - 1] = hand->cards[i];
        }
    }
    // Remove a ultima carta
    hand->actual_length -= 1;

    return card;
}

void player_init_new_turn(Player_t* player)
{
    player->energy = 3;
    player->shield = 0;

    buy_cards_from_deck(player->hand, player->deck, player->discard_stack);
    player->hand->cards[0].active = true;
}

void discard_all_hand(Player_t* player)
{
    int count = player->discard_stack->actual_length;

    for (int i = player->hand->actual_length - 1; i >= 0; i--) {
        player->discard_stack->cards[count] = discard(player->hand, i);
        player->discard_stack->cards[count].active = false;
        player->discard_stack->actual_length += 1;
        count++;
    }
}

void discard_active_card(Game_t* game)
{
    int card_index = index_card_active(game->player->hand);

    Card_t card = discard(game->player->hand, card_index);
    card.active = false;

    if (game->player->discard_stack->actual_length == game->player->discard_stack->max_length) {
        /* TO-DO: Tratar - Está tentando adicionar sendo que já tem o numero maximo de cartas */
    } else {
        game->player->discard_stack->actual_length += 1;
        game->player->discard_stack->cards[game->player->discard_stack->actual_length - 1] = card;
        game->player->hand->cards[0].active = true;
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

    // init pilha de descart
    player->discard_stack = (Deck_t*)malloc(sizeof(Deck_t));
    player->discard_stack->cards = (Card_t*)malloc(sizeof(Card_t) * DECK_LENGTH);
    player->discard_stack->actual_length = 0;
    player->discard_stack->max_length = DECK_LENGTH;

    player->hand = init_player_hand(player->deck, player->discard_stack);
    return player;
}

void free_player(Player_t* player)
{
    if (!player)
        return;

    free_deck(player->deck);
    free_deck(player->discard_stack);

    if (player->hand) {
        free(player->hand->cards);
        free(player->hand);
    }

    free(player);
}
