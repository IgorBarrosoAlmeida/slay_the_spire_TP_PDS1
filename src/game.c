#include "game.h"
#include "utils.h"
#include <stdio.h>

Game_t* init_game()
{
    /* TO-DO atualizar logica de status */
    Game_t* game = (Game_t*)malloc(sizeof(Game_t));

    game->renderer = init_renderer();
    must_init(game->renderer, "Renderer", game);
    game->player = init_player();
    game->level = 1;
    game->game_over = false;
    game->actual_battle = init_battle(2, 1);

    return game;
}

void free_game(Game_t* game)
{
    if (!game)
        return;

    free_battle(game->actual_battle);
    free_player(game->player);
    clear_renderer(game->renderer);
    free(game);
}
