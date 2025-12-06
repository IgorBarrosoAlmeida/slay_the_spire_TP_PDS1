#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "deck.h"
#include <stdbool.h>

/**
 * @brief Enum que define os tipos de inimigos existentes, sendo
 * eles: WEAK, STRONG e BOSS
 */
typedef enum enemy_enum {
    WEAK = 0,
    STRONG = 1,
    BOSS = 2,
} EnemyType_t;

/**
 * @brief Estrutura responsável por guardar as informações relativas a um inimigo
 * do jogo
 *
 * @param health a quantidade atual de vida do inimigo
 * @param max_health a quantidade máxima de vida do inimigo
 * @param shield a quantidade atual de escudo do inimigo
 * @param type tipo do inimigo (WEAK, STRONG ou BOSS)
 * @param next_action o index na lista de ações da proxima ação
 * @param n_actions a quantidade de ações que o inimigo tem
 * @param selected true se o inimigo está selecionado e false caso contrário
 * @param died true se o inimigo está morto e false caso contrário
 * @param actions lista de ações do inimigo
 */
typedef struct enemy {
    int health;
    int max_health;
    int shield;
    EnemyType_t type;
    int next_action;
    int n_actions;
    _Bool selected;
    _Bool died;
    Card_t* actions;
} Enemy_t;

/**
 * @brief Função responsável por inicializar a estrutura de inimigo
 * com valores padrões
 *
 * @return retorna uma estrutura de inimigo já inicializada
 */
Enemy_t init_enemy(EnemyType_t type);

/**
 * @brief Função que libera a memoria alocada na estrutura de inimigo
 *
 * @param deck ponteiro para o inimigo a ser liberado
 */
void free_enemy(Enemy_t* enemy);

#endif