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
    _Bool redraw = true, card_selected = false, hand_locked = false, enemy_selected = false;
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
            al_draw_scaled_bitmap(game->renderer->img_game_over,
                0, 0, al_get_bitmap_width(game->renderer->img_game_over), al_get_bitmap_height(game->renderer->img_game_over),
                0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                0);
            al_flip_display();
            continue;
        }

        if (is_battle_over(game->actual_battle)) {
            game->level += 1;

            // Se passou do ultimo level acaba
            if (game->level == 12) {
                al_draw_scaled_bitmap(game->renderer->img_victory,
                    0, 0, al_get_bitmap_width(game->renderer->img_victory), al_get_bitmap_height(game->renderer->img_victory),
                    0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                    0);
                al_flip_display();
                continue;
            }

            // Boss battle
            if (game->level == 11) {
                al_draw_scaled_bitmap(game->renderer->img_boss_battle,
                    0, 0, al_get_bitmap_width(game->renderer->img_victory), al_get_bitmap_height(game->renderer->img_victory),
                    0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                    0);
                al_flip_display();
                al_rest(2.5);

                free_battle(game->actual_battle);
                game->actual_battle = init_battle(1, game->level + 1);
                hand_locked = false;
            } else {

                al_rest(1.5);

                free_battle(game->actual_battle);
                game->actual_battle = init_battle(2, game->level);

                // Reseta player
                int count = game->player->deck->actual_length;
                do {
                    discard_all_hand(game->player);
                    buy_cards_from_deck(game->player->hand, game->player->deck, game->player->discard_stack);
                    count--;
                } while (count >= 0);
                game->player->energy = 3;
                game->player->shield = 0;
                hand_locked = false;

                // Tela de mudança de fase
                al_clear_to_color(al_map_rgb(0, 0, 0));

                char buffer[10];
                ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
                float scale = 3.5;
                sprintf(buffer, "Fase %d", game->level);

                draw_scaled_text(game->renderer->font, text_color,
                    (DISPLAY_WIDTH) / (scale * 2.0), DISPLAY_HEIGHT / (scale * 2.0),
                    scale, scale, ALLEGRO_ALIGN_CENTRE, buffer);

                al_flip_display();
                al_rest(1.5);
            }
        }

        if (game->actual_battle.isPlayerTurn && !hand_locked && game->player->hand->actual_length > 0) {
            if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                int active_card = index_card_active(game->player->hand);

                switch (event.keyboard.keycode) {
                case ALLEGRO_KEY_LEFT: {
                    if (!card_selected) {
                        game->player->hand->cards[active_card].active = false;

                        if (active_card == 0) {
                            game->player->hand->cards[game->player->hand->actual_length - 1].active = true;
                        } else {
                            game->player->hand->cards[active_card - 1].active = true;
                        }
                    } else { // seleção de inimigos
                        int selected = index_selected_enemy(game->actual_battle.enemys, game->actual_battle.n_enemys);
                        game->actual_battle.enemys[selected].selected = false;

                        if (selected == 0) {
                            // Não seleciona se o inimigo estiver morto
                            if (!game->actual_battle.enemys[game->actual_battle.n_enemys - 1].died) {
                                game->actual_battle.enemys[game->actual_battle.n_enemys - 1].selected = true;
                            } else {
                                game->actual_battle.enemys[selected].selected = true;
                            }
                        } else {
                            // Não seleciona se o inimigo estiver morto
                            if (!game->actual_battle.enemys[selected - 1].died) {
                                game->actual_battle.enemys[selected - 1].selected = true;
                            } else {
                                game->actual_battle.enemys[selected].selected = true;
                            }
                        }
                    }

                    break;
                }
                case ALLEGRO_KEY_RIGHT: {
                    if (!card_selected) {
                        game->player->hand->cards[active_card].active = false;

                        if (active_card == game->player->hand->actual_length - 1) {
                            game->player->hand->cards[0].active = true;
                        } else {
                            game->player->hand->cards[active_card + 1].active = true;
                        }
                    } else { // seleção de inimigos
                        int selected = index_selected_enemy(game->actual_battle.enemys, game->actual_battle.n_enemys);

                        game->actual_battle.enemys[selected].selected = false;

                        if (selected == game->actual_battle.n_enemys - 1) {
                            // Não seleciona se o inimigo estiver morto
                            if (!game->actual_battle.enemys[0].died) {
                                game->actual_battle.enemys[0].selected = true;
                            } else {
                                game->actual_battle.enemys[selected].selected = true;
                            }
                        } else {
                            // Não seleciona se o inimigo estiver morto
                            if (!game->actual_battle.enemys[selected + 1].died) {
                                game->actual_battle.enemys[selected + 1].selected = true;
                            } else {
                                game->actual_battle.enemys[selected].selected = true;
                            }
                        }
                    }
                    break;
                }
                case ALLEGRO_KEY_ENTER: {
                    if (card_selected) {
                        enemy_selected = true;
                    } else if (game->player->hand->cards[active_card].cost <= game->player->energy) {
                        // Começa a seleção do inimigo
                        card_selected = true;

                        if (game->player->hand->cards[active_card].type == ATACK) {
                            // Seleciona o primeiro inimigo vivo
                            for (int i = 0; i < game->actual_battle.n_enemys; i++) {
                                if (!game->actual_battle.enemys[i].died) {
                                    game->actual_battle.enemys[i].selected = true;
                                    break;
                                }
                            }
                        } else {
                            enemy_selected = true;
                        }
                    }
                    break;
                }
                }
            }
        }

        if (event.type == ALLEGRO_EVENT_KEY_DOWN && game->actual_battle.isPlayerTurn) {
            // Só passa a vez se não estiver selecionando inimigo
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE && !card_selected) {
                inicio_turno_inimigo = al_get_time();
                discard_all_hand(game->player);

                game->actual_battle.isPlayerTurn = false;
                hand_locked = true;

                // Zera os escudos inimigos
                for (int i = 0; i < game->actual_battle.n_enemys; i++) {
                    game->actual_battle.enemys[i].shield = 0;
                }
            }

            // Teclas para teste
            if (event.keyboard.keycode == ALLEGRO_KEY_X) {
                game->player->health = 1;
            }
            if (event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                for (int i = 0; i < game->actual_battle.n_enemys; i++) {
                    game->actual_battle.enemys[i].health = 0;
                    game->actual_battle.enemys[i].died = true;
                }
                render_screen(game);
            }
        }

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {

            if (card_selected && enemy_selected && game->actual_battle.isPlayerTurn) {
                // Se não tem energia o suficiente não faz nada
                battle(game);

                card_selected = false;
                enemy_selected = false;
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

    free_game(game);

    return SUCCESS;
}
