/*
==============================
    includes / libs
==============================
*/

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#include "constants.h"
#include "deck.h"
#include "game.h"
#include "player.h"
#include "renderer.h"
#include "utils.h"

/*
==============================
    functions
==============================
*/

/* initialize renderer struct */
Renderer_t* init_renderer()
{

    Renderer_t* renderer = malloc(sizeof(Renderer_t));

    if (!renderer) {
        return NULL;
    }

    // al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    // al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    renderer->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (!renderer->display) {
        return NULL;
    }

    renderer->display_buffer = al_create_bitmap(DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT);
    if (!renderer->display_buffer) {
        return NULL;
    }

    renderer->font = al_create_builtin_font();
    if (!renderer->font) {
        return NULL;
    }

    // Carrega imagens
    renderer->img_player = al_load_bitmap("./assets/images/player.png");
    if (!renderer->img_player) {
        return NULL;
    }

    renderer->img_background = al_load_bitmap("./assets/images/bg.jpg");
    if (!renderer->img_background) {
        return NULL;
    }

    // monstros
    renderer->img_enemy_weak = al_load_bitmap("./assets/images/slime.png");
    if (!renderer->img_enemy_weak) {
        return NULL;
    }

    renderer->img_enemy_strong = al_load_bitmap("./assets/images/ogre.png");
    if (!renderer->img_enemy_strong) {
        return NULL;
    }
    renderer->img_dead_enemy = al_load_bitmap("./assets/images/dead_enemy.png");
    if (!renderer->img_dead_enemy) {
        return NULL;
    }
    renderer->img_game_over = al_load_bitmap("./assets/images/game_over.png");
    if (!renderer->img_game_over) {
        return NULL;
    }
    renderer->img_victory = al_load_bitmap("./assets/images/victory.png");
    if (!renderer->img_victory) {
        return NULL;
    }
    renderer->img_boss_battle = al_load_bitmap("./assets/images/boss_battle.png");
    if (!renderer->img_boss_battle) {
        return NULL;
    }

    renderer->img_boss = al_load_bitmap("./assets/images/dragon.png");
    if (!renderer->img_boss_battle) {
        return NULL;
    }

    // icones
    renderer->img_shield = al_load_bitmap("./assets/images/shield_icon.png");
    if (!renderer->img_shield) {
        return NULL;
    }
    renderer->img_sword = al_load_bitmap("./assets/images/sword_icon.png");
    if (!renderer->img_sword) {
        return NULL;
    }

    return renderer;
}

/* render game background */
void render_background(Renderer_t* renderer)
{

    if (renderer->img_background) {
        int bg_w = al_get_bitmap_width(renderer->img_background);
        int bg_h = al_get_bitmap_height(renderer->img_background);

        al_draw_scaled_bitmap(renderer->img_background,
            0, 0, bg_w, bg_h,
            0, 0, DISPLAY_WIDTH / DISPLAY_SCALE, DISPLAY_HEIGHT / DISPLAY_SCALE,
            0);
    } else {
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
}

void draw_scaled_text(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y,
    float xscale, float yscale, int alignment,
    const char* text)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform); // Start with an identity transform
    al_scale_transform(&transform, xscale, yscale); // Apply scaling (e.g., sx=2.0, sy=2.0 for double size)
    al_use_transform(&transform); // Use the transform for subsequent drawing

    al_draw_text(font, color, x, y, alignment, text);
    al_identity_transform(&transform);
    al_use_transform(&transform); // Use the transform for subsequent drawing
}

void draw_centered_scaled_text(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x,
    float y, float xscale, float yscale, char* text)
{
    draw_scaled_text(font, color, x, y, xscale, yscale, ALLEGRO_ALIGN_CENTRE, text);
}

void render_deck(Renderer_t* renderer, int x_left, int y_top, char* type, int count, int max)
{
    ALLEGRO_BITMAP* prev_bitmap = al_get_target_bitmap();

    ALLEGRO_BITMAP* deck_bitmap = al_create_bitmap(DECK_WIDTH, DECK_HEIGHT);
    al_set_target_bitmap(deck_bitmap);

    al_draw_filled_rounded_rectangle(0, 0, DECK_WIDTH, DECK_HEIGHT, 10, 0, al_map_rgb(255, 255, 255));
    al_set_target_bitmap(prev_bitmap);

    al_draw_scaled_bitmap(deck_bitmap, 0, 0, DECK_WIDTH, DECK_HEIGHT, x_left, y_top, DECK_WIDTH, DECK_HEIGHT, 0);
    al_destroy_bitmap(deck_bitmap);

    float scale = 2.0;
    ALLEGRO_COLOR text_color = al_map_rgb(0, 0, 0);

    float txt_x = (x_left + 10) / scale;
    float txt_y = (y_top + 10) / scale;

    float line_height = 20;

    char buffer[64];

    sprintf(buffer, "%s", type);
    draw_scaled_text(renderer->font, text_color, txt_x, txt_y,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

    sprintf(buffer, "%d/%d", count, max);
    draw_scaled_text(renderer->font, text_color, txt_x, txt_y + line_height,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);
}

void render_health_bar(float x, float y, float width, float height, int current_hp, int max_hp)
{
    if (max_hp <= 0)
        max_hp = 1;
    if (current_hp < 0)
        current_hp = 0;
    if (current_hp > max_hp)
        current_hp = max_hp;

    float percentage = (float)current_hp / (float)max_hp;

    ALLEGRO_COLOR bar_color;
    if (percentage > 0.5) {
        bar_color = al_map_rgb(50, 205, 50);
    } else if (percentage > 0.25) {
        bar_color = al_map_rgb(255, 215, 0);
    } else {
        bar_color = al_map_rgb(220, 20, 60);
    }

    al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(50, 50, 50));

    al_draw_filled_rectangle(x, y, x + (width * percentage), y + height, bar_color);

    al_draw_rectangle(x, y, x + width, y + height, al_map_rgb(255, 255, 255), 2.0);
}

void render_creature(const Renderer_t* renderer, int begin_x, int begin_y, int width, int max_health, int health, int shield, int img_id, _Bool is_selected)
{
    switch (img_id) {
    case 0:
        al_draw_scaled_bitmap(
            renderer->img_player,
            0, 0,
            al_get_bitmap_width(renderer->img_player),
            al_get_bitmap_height(renderer->img_player),
            begin_x, begin_y,
            width,
            200,
            0);
        break;
    case 1:
        al_draw_scaled_bitmap(
            renderer->img_enemy_weak,
            0, 0,
            al_get_bitmap_width(renderer->img_enemy_weak),
            al_get_bitmap_height(renderer->img_enemy_weak),
            begin_x, begin_y,
            width,
            200,
            0);
        break;
    case 2:
        al_draw_scaled_bitmap(
            renderer->img_enemy_strong,
            0, 0,
            al_get_bitmap_width(renderer->img_enemy_strong),
            al_get_bitmap_height(renderer->img_enemy_strong),
            begin_x, begin_y,
            width,
            200,
            0);
        break;
    case 3:
        al_draw_scaled_bitmap(
            renderer->img_boss,
            0, 0,
            al_get_bitmap_width(renderer->img_boss),
            al_get_bitmap_height(renderer->img_boss),
            begin_x, begin_y,
            BOSS_WIDTH,
            BOSS_HEIGHT,
            0);
        break;
    case -1:
        al_draw_scaled_bitmap(
            renderer->img_dead_enemy,
            0, 0,
            al_get_bitmap_width(renderer->img_dead_enemy),
            al_get_bitmap_height(renderer->img_dead_enemy),
            begin_x, begin_y,
            width,
            200,
            0);
        break;
    }
    float health_bar_y;
    if (img_id == 3) {
        health_bar_y = begin_y + (width / 2.5);
        begin_x += 300;
    } else {
        health_bar_y = begin_y + 200;
    }

    render_health_bar(begin_x, health_bar_y, 300, 50, health, max_health);

    float scale = 2.0;
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);

    char buffer[64];

    sprintf(buffer, "Escudo: %d", shield);
    draw_scaled_text(renderer->font, text_color, (begin_x + 10) / scale, (health_bar_y + 100) / scale,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

    // Escreve atual/max
    text_color = al_map_rgb(255, 255, 255);
    sprintf(buffer, "%d/%d", health, max_health);
    draw_scaled_text(renderer->font, text_color, (begin_x + 100) / scale, (health_bar_y + 20) / scale,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

    // select box
    if (is_selected) {
        al_draw_rectangle(begin_x, begin_y, begin_x + width, begin_y + (width / 2), al_map_rgb(255, 255, 255), 2.0);
    }
}

void render_card(const Renderer_t* renderer, int x_left, int y_top, Card_t card)
{
    if (card.active) {
        y_top -= 50;
    }

    al_draw_filled_rounded_rectangle(x_left, y_top,
        x_left + CARD_WIDTH, y_top + CARD_HEIGHT,
        5, 5, al_map_rgb(255, 255, 255));

    al_draw_rounded_rectangle(x_left, y_top,
        x_left + CARD_WIDTH, y_top + CARD_HEIGHT,
        5, 5, al_map_rgb(255, 0, 0), 2);

    float scale = 2.0;
    ALLEGRO_COLOR text_color = al_map_rgb(0, 0, 0);

    float txt_x = (x_left + 10) / scale;
    float txt_y = (y_top + 10) / scale;

    float line_height = 20;

    char buffer[64];

    if (card.type == ATACK)
        sprintf(buffer, "Tipo: ATAQUE");
    else if (card.type == DEFENSE)
        sprintf(buffer, "Tipo: ESCUDO");
    else
        sprintf(buffer, "Tipo: ESPECIAL");

    draw_scaled_text(renderer->font, text_color, txt_x, txt_y,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

    sprintf(buffer, "Efeito: %d", card.effect);
    draw_scaled_text(renderer->font, text_color, txt_x, txt_y + line_height,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

    sprintf(buffer, "Custo: %d", card.cost);
    draw_scaled_text(renderer->font, text_color, txt_x, txt_y + (line_height * 2),
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);
}

void render_player_hand(Renderer_t* renderer, PlayerHand_t* hand)
{
    for (int i = 0; i < hand->actual_length; i++) {
        render_card(renderer, HAND_BEGIN_X + (i * (CARD_WIDTH + 10)), HAND_BEGIN_Y, hand->cards[i]);
    }
}

void render_enemies(Renderer_t* renderer, int n_enemys, Enemy_t* enemys)
{
    for (int i = 0; i < n_enemys; i++) {
        float x_icon, y_icon;
        if (enemys[i].type == BOSS) {
            x_icon = ENEMIES_BEGIN_X + 300;
            y_icon = ENEMIES_BEGIN_Y - 300;
        } else {
            x_icon = ENEMIES_BEGIN_X + (i * (ENEMIES_WIDTH + 30)) + 75;
            y_icon = ENEMIES_BEGIN_Y - 75;
        }

        if (enemys[i].actions[enemys[i].next_action].type == ATACK) {
            al_draw_scaled_bitmap(
                renderer->img_sword,
                0, 0,
                al_get_bitmap_width(renderer->img_sword),
                al_get_bitmap_height(renderer->img_sword),
                x_icon, y_icon,
                200,
                100,
                0);
        } else {
            al_draw_scaled_bitmap(
                renderer->img_shield,
                0, 0,
                al_get_bitmap_width(renderer->img_shield),
                al_get_bitmap_height(renderer->img_shield),
                x_icon, y_icon,
                200,
                100,
                0);
        }

        // Escreve o efeito da proxima ação
        char buffer[10];
        ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
        float scale = 2.0;
        sprintf(buffer, "%d", enemys[i].actions[enemys[i].next_action].effect);

        draw_scaled_text(renderer->font, text_color,
            (x_icon + 150) / scale, (y_icon + 30) / scale,
            scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

        if (enemys[i].type == WEAK) {
            render_creature(renderer, ENEMIES_BEGIN_X + (i * (ENEMIES_WIDTH + 30)), ENEMIES_BEGIN_Y,
                ENEMIES_WIDTH, enemys[i].max_health, enemys[i].health, enemys[i].shield, enemys[i].died ? -1 : 1, enemys[i].selected);
        } else if (enemys[i].type == STRONG) {
            render_creature(renderer, ENEMIES_BEGIN_X + (i * (ENEMIES_WIDTH + 30)), ENEMIES_BEGIN_Y,
                ENEMIES_WIDTH, enemys[i].max_health, enemys[i].health, enemys[i].shield, enemys[i].died ? -1 : 2, enemys[i].selected);
        } else {
            render_creature(renderer, ENEMIES_BEGIN_X, ENEMIES_BEGIN_Y - 200,
                BOSS_WIDTH + 200, enemys[i].max_health, enemys[i].health, enemys[i].shield, enemys[i].died ? -1 : 3, enemys[i].selected);
        }
    }
}

void render_player(Renderer_t* renderer, Player_t* player)
{
    render_creature(renderer, PLAYER_BEGIN_X, PLAYER_BEGIN_Y, PLAYER_WIDTH, PLAYER_MAX_HEALTH, player->health, player->shield, 0, false);
}

void render_energy(Renderer_t* renderer, int qnt, int max, float pos_x, float pos_y)
{
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);
    char text[30];

    sprintf(text, "Energia: %d/%d", qnt, max);

    draw_scaled_text(renderer->font, text_color, pos_x, pos_y, 2.0, 2.0, ALLEGRO_ALIGN_LEFT, text);

    if (qnt == 0) {
        sprintf(text, "Energia acabou!!", qnt, max);

        draw_scaled_text(renderer->font, text_color, pos_x, pos_y + 20, 2.0, 2.0, ALLEGRO_ALIGN_LEFT, text);
    }
}

void render_instruction(Renderer_t* renderer)
{
    float scale = 2.0;
    ALLEGRO_COLOR text_color = al_map_rgb(255, 255, 255);

    float txt_x = DISPLAY_WIDTH - 100 / scale;
    float txt_y = 30 / scale;

    float line_height = 20;

    char buffer[64];

    sprintf(buffer, "Enter: Confirmar seleção");
    draw_scaled_text(renderer->font, text_color, txt_x, txt_y + line_height,
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);

    sprintf(buffer, "Espaço: Passar para proxima fase");
    draw_scaled_text(renderer->font, text_color, txt_x, txt_y + (line_height * 2),
        scale, scale, ALLEGRO_ALIGN_LEFT, buffer);
}

void render_screen(Game_t* game)
{
    al_set_target_bitmap(game->renderer->display_buffer);
    render_background(game->renderer);
    render_deck(game->renderer, DECK_POSITION_X, DECK_POSITION_Y, "Compra", game->player->deck->actual_length,
        game->player->deck->max_length); // deck
    render_deck(game->renderer, DECK_POSITION_X + 5 * CARD_WIDTH + 280, DECK_POSITION_Y, "Descarte",
        game->player->discard_stack->actual_length, game->player->discard_stack->max_length); // pilha discarte
    render_player(game->renderer, game->player);
    render_energy(game->renderer, game->player->energy, 3, 10.0, 10.0);
    render_enemies(game->renderer, game->actual_battle.n_enemys, game->actual_battle.enemys);
    render_player_hand(game->renderer, game->player->hand);
    render_instruction(game->renderer);

    al_set_target_backbuffer(game->renderer->display);

    al_draw_scaled_bitmap(game->renderer->display_buffer, 0, 0, DISPLAY_BUFFER_WIDTH,
        DISPLAY_BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH,
        DISPLAY_HEIGHT, 0);

    al_flip_display();
}

void clear_renderer(Renderer_t* renderer)
{
    if (!renderer)
        return;

    al_destroy_display(renderer->display);
    al_destroy_bitmap(renderer->display_buffer);
    al_destroy_bitmap(renderer->img_shield);
    al_destroy_bitmap(renderer->img_sword);
    al_destroy_font(renderer->font);
    free(renderer);
}