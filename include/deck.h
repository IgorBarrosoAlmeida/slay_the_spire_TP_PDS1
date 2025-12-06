#ifndef _DECK_H_
#define _DECK_H_
#include <stdbool.h>

/**
 * @brief enum que define os tipos de cartas existentes, sendo
 * eles: SPECIAL, DEFENSE e ATACK
 */
typedef enum {
    SPECIAL = 0,
    DEFENSE = 1,
    ATACK = 2,
} Type_t;

/**
 * @brief Estrutura responsável por guardar as informações
 * relativas às cartas do jogo
 *
 * @param id identificador sequecial para testes
 * @param type o tipo da carta (SPECIAL, DEFENSE ou ATACK)
 * @param cost o custo em energia dessa carta
 * @param effect o efeito da carta, seja ele dano ou quantidade de
 * escudo adicionado
 * @param active true se a carta estiver selecionda e false caso contrário
 */
typedef struct card {
    int id;
    Type_t type;
    int cost;
    int effect;
    _Bool active;
} Card_t;

/** @brief Estrutura responsável por guardar as informações relativas
 * a um conjunto de cartas do jogo
 *
 * @example pilha de compras e pilha de descarte
 *
 * @param cards lista de cartas
 * @param max_length o tamanho maximo da lista de cartas
 * @param actual_legth o tamanho atual da lista de cartas
 */
typedef struct deck {
    Card_t* cards;
    int max_length;
    int actual_length;
} Deck_t;

/**
 * @brief Função responsável por inicializar a estrutura de deck
 * com valores padrões
 *
 * @return retorna o ponteiro para uma estrutura de deck já inicializada
 */
Deck_t* init_deck();

/**
 * @brief Função que libera a memoria alocada na estrutura de deck
 *
 * @param deck ponteiro para o deck a ser liberado
 */
void free_deck(Deck_t* deck);

#endif