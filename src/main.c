/*
==============================
    includes / libs
==============================
*/
#include "constants.h"
#include "deck.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "utils.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
// #include <allegro5/allegro_font.h>
// #include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>

/*
==============================
    main function
==============================
*/
int main(int argc, char* argv[])
{
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    _Bool redraw = true, move = false, hand_locked = false;
    double inicio_turno_inimigo = 0;
    // Inicializa a semente aleatória com o tempo atual do sistema
    srand(time(NULL));

    // ===================== initialize routines =====================
    must_init(al_init(), "allegro", NULL);
    must_init(al_init_image_addon(), "image addon", NULL);
    must_init(al_init_primitives_addon(), "primitives addon", NULL);
    must_init(al_install_keyboard(), "keyboard", NULL);
    // al_init_font_addon();
    // must_init(al_init_ttf_addon(), "font ttf addon", NULL);
    Game_t* game = init_game();

    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer", game);

    event_queue = al_create_event_queue();
    must_init(event_queue, "queue", game);

    // ===================== event queue registers =====================

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(game->renderer->display));

    ALLEGRO_EVENT event;

    // inicia o temporizador
    al_start_timer(timer);

    while (true) {
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_Q) {
            break;
        }

        if (game->game_over) {
            /* TO-DO: tela de game over */

            continue;
        }

        if (game->change_level) {
            game->level += 1;
            game->change_level = false;
            free_battle(game->actual_battle);
            game->actual_battle = init_battle(2);

            /* TO-DO: Exibir mensagem de mudando o level*/
            /* TO-DO: Resetar o player e a batalha*/
        }

        if (game->actual_battle.isPlayerTurn && !hand_locked && game->player->hand->actual_length > 0) {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT: {
                    int index_atual = index_card_active(game->player->hand);
                    game->player->hand->cards[index_atual].active = false;
                    if (index_atual == 0) {
                        game->player->hand->cards[game->player->hand->actual_length - 1].active = true;
                    } else {
                        game->player->hand->cards[index_atual - 1].active = true;
                    }
                    break;
                }
                case ALLEGRO_KEY_RIGHT: {
                    int index_atual = index_card_active(game->player->hand);
                    game->player->hand->cards[index_atual].active = false;

                    if (index_atual == game->player->hand->actual_length - 1) {
                        game->player->hand->cards[0].active = true;
                    } else {
                        game->player->hand->cards[index_atual + 1].active = true;
                    }
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    move = true;
                    break;
                }
                }
            }
        }

        if (game->player->energy <= 0) {
            hand_locked = true;
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE
            && game->actual_battle.isPlayerTurn) {
            inicio_turno_inimigo = al_get_time();
            discard_all_hand(game->player);

            game->actual_battle.isPlayerTurn = false;
            hand_locked = true;
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {

            if (move && game->actual_battle.isPlayerTurn) {
                int energy = game->player->energy;
                battle(game);

                move = false;
            }

            else if (!game->actual_battle.isPlayerTurn) {
                double tempo_atual = al_get_time();

                if (tempo_atual - inicio_turno_inimigo >= 3.0) {
                    battle(game);

                    game->actual_battle.isPlayerTurn = true;
                    hand_locked = false;

                    player_init_new_turn(game->player);
                }
            }
            render_screen(game);

            // Para escrever "inimigo pensando..."
            if (!game->actual_battle.isPlayerTurn) {

                ALLEGRO_FONT* font = game->renderer->font;

                ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
                int cx = al_get_display_width(game->renderer->display) / 2;
                int cy = al_get_display_height(game->renderer->display) / 2;

                if ((int)(al_get_time() * 5) % 2 == 0) {
                    al_draw_text(font, color, cx, cy - 50, ALLEGRO_ALIGN_CENTER, "INIMIGO PENSANDO...");
                }
                al_flip_display();
            }

            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    free_battle(game->actual_battle);
    free_game(game);

    return SUCCESS;
}
