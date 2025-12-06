#ifndef _BATTLE_H_
#define _BATTLE_H_

#include "enemy.h"
#include "player.h"
#include <stdbool.h>
#include <stdlib.h>

// FORWARD DECLARATION:
typedef struct game Game_t;

/**
 * @brief Estrutura responsavel por guardar as informações relativas a batalha
 *
 * @param enemies lista com os inimigos dessa batalha
 * @param n_enemies numero de inimigos da lista
 * @param isPlayerTurn booleano que fala se está ou não no turno do jogador
 */
typedef struct battle {
    Enemy_t* enemies;
    int n_enemies;
    _Bool isPlayerTurn;
} Battle_t;

/**
 * @brief Função de batalha chamada pela main essa função realiza
 * a ação do jogador ou a ação dos inimigos. Essa função chama outras duas "player_move"
 * e "enemy_move" dependendo do turno atual do jogo. Essas funções já alteram
 * diretamente na memória os valores de vida, energia e outros atributos do jogo.
 *
 * @param game ponteiro para estrutura principal do jogo
 */
void battle(Game_t* game);

/**
 * @brief Função responsável por inicializar a estrutura de batalha
 * com valores padrões
 *
 * @param n_enemies
 * @param level
 *
 * @return retorna a estrutura de batalha já inicializada
 */
Battle_t init_battle(int n_enemies, int level);

/**
 * @brief Função que libera a memoria alocada na estrutura de batalha
 *
 * @param battle batalha a ser liberada
 */
void free_battle(Battle_t battle);

/**
 * @brief Função que busca na lista de inimigos qual inimigo
 * está selecionado
 *
 * @param enemies lista de inimigos a ser percorrida
 * @param n_enemies
 *
 * @return index do primeiro inimigo selecionado
 */
int index_selected_enemy(Enemy_t* enemies, int n_enemies);

/**
 * @brief Função que verifica se a batalha acabou percorrendo
 * por uma lista de inimigos e verificando se eles estão mortos
 *
 * @param battle batalha que é necessario verificar se acabou
 *
 * @return Retorna true se a batalha acabou e false se não acabou
 */
_Bool is_battle_over(Battle_t battle);

#endif