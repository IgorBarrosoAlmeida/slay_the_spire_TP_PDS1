#ifndef _GAME_H_
#define _GAME_H_

#include "battle.h"
#include "player.h"
#include "renderer.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Estrutura principal do jogo, responsável por unir as informações
 * mais necessárias para o jogo funcionar
 *
 * @param player estrutura do jogador
 * @param renderer estrutura que contém as informações de renderização
 * @param actual_battle estrutura da batalha atual
 * @param game_over true se o jogo acabou e false se não acabou
 * @param level nivel atual do jogo
 */
typedef struct game {
    Player_t* player;
    Renderer_t* renderer;
    Battle_t actual_battle;
    _Bool game_over;
    int level;
} Game_t;

/**
 * @brief Função responsável por inicializar a estrutura do jogo
 * com valores padrões
 *
 * @return retorna uma estrutura do jogo já inicializada
 */
Game_t* init_game();

/**
 * @brief Função que libera a memoria alocada na estrutura de jogo
 *
 * @param game ponteiro para o jogo a ser liberado
 */
void free_game(Game_t* game);

#endif