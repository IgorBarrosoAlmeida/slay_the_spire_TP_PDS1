#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "deck.h"

// FORWARD DECLARATION:
typedef struct game Game_t;

/**
 * @brief Estrutura responsável por guardar as informações
 * relativas a mão atual do jogador
 *
 * @param cards a lista de cartas na mão do jogador
 * @param max_length a quantidade maxima de cartas que podem estar na mão do jogador
 * @param actual_length a quantiade de cartas que está atualmente na mão do jogador
 */
typedef struct player_hand {
    Card_t* cards;
    int max_length;
    int actual_length;
} PlayerHand_t;

/**
 * @brief Estrutura responsável por guardar as informações
 * relativas ao jogador
 *
 * @param health vida atual do jogador
 * @param shield quanto escudo o jogador tem
 * @param energy quanta energia o jogador tem
 * @param deck a pilha de compras do jogador
 * @param discard_stack pilha de descartes do jogador
 * @param hand mão atual do jogador
 */
typedef struct player {
    int health;
    int shield;
    int energy;
    Deck_t* deck;
    Deck_t* discard_stack;
    PlayerHand_t* hand;
} Player_t;

/**
 * @brief Função que busca na mão do jogador qual é a carta que está ativa
 *
 * @param hand a mão atual do jogador
 *
 * @return Retorna o index da primeira carta ativa
 */
int index_card_active(PlayerHand_t* hand);

/**
 * @brief Função que tira 5 cartas do deck de compra e as inclui na mão
 * do jogador. Caso o `deck` não tenha cartas o suficiente, a função embaralha
 * a `discard_stack` e coloca as cartas dela na pilha de compras
 *
 * @param player_hand mão atual do jogador
 * @param deck baralho de compras
 * @param discard_stack baralho de descarte
 */
void buy_cards_from_deck(PlayerHand_t* player_hand, Deck_t* deck, Deck_t* discard_stack);

/**
 * @brief Função responsável por descartar a carta ativa da mão do player
 *
 * @param game ponteiro para a estrutura principal do jogo
 */
void discard_active_card(Game_t* game);

/**
 * @brief Função que descarta toda a mão do jogador e joga ela para a
 * pilha de descarte
 *
 * @param player ponteiro para a estrutura do jogador
 */
void discard_all_hand(Player_t* player);

/**
 * @brief Função responsável por zerar o shield, maximizar a energia e
 * comprar novas cartas chamando a função `buy_cards_from_deck`. Ela deve
 * ser utilizada no começo do turno do jogador
 */
void player_init_new_turn(Player_t* player);

/**
 * @brief Função responsável por inicializar a estrutura do jogador
 * com valores padrões
 *
 * @return retorna uma estrutura do jogador já inicializada
 */
Player_t* init_player();

/**
 * @brief Função que libera a memoria alocada na estrutura do jogador
 *
 * @param game ponteiro para o jogador a ser liberado
 */
void free_player(Player_t* player);

#endif