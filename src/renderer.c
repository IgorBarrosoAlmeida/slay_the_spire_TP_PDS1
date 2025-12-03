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

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
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

    return renderer;
}

/* render game background */
void render_background(Renderer_t* renderer)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
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

void render_deck(Renderer_t* renderer, int x_left, int y_top)
{
    ALLEGRO_BITMAP* prev_bitmap = al_get_target_bitmap();

    ALLEGRO_BITMAP* deck_bitmap = al_create_bitmap(DECK_WIDTH, DECK_HEIGHT);
    al_set_target_bitmap(deck_bitmap);

    al_draw_filled_rounded_rectangle(0, 0, DECK_WIDTH, DECK_HEIGHT, 10, 0, al_map_rgb(255, 255, 255));
    al_set_target_bitmap(prev_bitmap);

    al_draw_scaled_bitmap(deck_bitmap, 0, 0, DECK_WIDTH, DECK_HEIGHT, x_left, y_top, DECK_WIDTH, DECK_HEIGHT, 0);
    al_destroy_bitmap(deck_bitmap);
}

void draw_health_bar(float x, float y, float width, float height, int current_hp, int max_hp)
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

void render_health_bar(float x_begin, float x_end, float y_down_left, ALLEGRO_FONT* font)
{
    float mid_y = y_down_left - (HEALTH_BAR_HEIGHT * 0.78);

    al_draw_filled_rounded_rectangle(
        x_begin - HEALTH_BAR_BACKGROUND_EXTRA,
        y_down_left - HEALTH_BAR_BACKGROUND_EXTRA,
        x_end + HEALTH_BAR_BACKGROUND_EXTRA,
        y_down_left - HEALTH_BAR_HEIGHT + HEALTH_BAR_BACKGROUND_EXTRA,
        HEALTH_BAR_RX, HEALTH_BAR_RY, al_map_rgb(255, 255, 255));
    char text[100] = "";
    sprintf(text, "Vida?");
    float x_scale = 2.0, y_scale = 2.0;
    draw_scaled_text(font, al_map_rgb(0, 0, 0), (x_begin + x_end) / 2.0 / x_scale,
        mid_y / y_scale, x_scale, y_scale, ALLEGRO_ALIGN_CENTRE, text);
}

void render_creature(const Renderer_t* renderer, int begin_x, int mid_y, int width, int max_health, int health)
{
    al_draw_filled_circle(begin_x + width / 2.0, mid_y, width,
        al_map_rgb(255, 255, 255));
    float x_end = begin_x + width;

    float health_bar_y = mid_y + width + 20;
    draw_health_bar(begin_x, health_bar_y, 300, 50, health, max_health);
}

void render_card(const Renderer_t* renderer, int x_left, int y_top, _Bool active)
{
    ALLEGRO_BITMAP* card_bitmap = al_create_bitmap(CARD_WIDTH, CARD_HEIGHT);
    al_set_target_bitmap(card_bitmap);

    al_draw_filled_rounded_rectangle(0, 0, CARD_WIDTH, CARD_HEIGHT, 5, 5,
        al_map_rgb(255, 255, 255));
    al_draw_rounded_rectangle(0, 0, CARD_WIDTH, CARD_HEIGHT, 5, 5,
        al_map_rgb(255, 0, 0), 2);

    float xscale = 2, yscale = 2;

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);

    char text[10] = "";
    xscale = 3, yscale = 3;
    sprintf(text, "card");

    draw_scaled_text(renderer->font, color, (CARD_WIDTH * 0.5) / xscale,
        (CARD_HEIGHT * 0.3) / yscale, xscale, yscale,
        ALLEGRO_ALIGN_LEFT, text);

    if (active) {
        y_top -= 100;
    }
    al_set_target_bitmap(renderer->display_buffer);
    al_draw_scaled_bitmap(card_bitmap, 0, 0, CARD_WIDTH, CARD_HEIGHT, x_left,
        y_top, CARD_WIDTH, CARD_HEIGHT, 0);

    al_destroy_bitmap(card_bitmap);
}

void render_player_hand(Renderer_t* renderer, PlayerHand_t* hand)
{
    for (int i = 0; i < hand->actual_length; i++) {
        render_card(renderer, HAND_BEGIN_X + (i * (CARD_WIDTH + 10)), HAND_BEGIN_Y, hand->cards[i].active);
    }
}

void render_enemies(Renderer_t* renderer, int n_enemys, Enemy_t* enemys)
{
    for (int i = 0; i < n_enemys; i++) {
        render_creature(renderer, ENEMIES_BEGIN_X + (i * (ENEMIES_RADIUS + 30)), ENEMIES_BEGIN_Y + (i * ENEMIES_RADIUS), ENEMIES_RADIUS, enemys[i].max_health, enemys[i].health);
    }
}

void render_player(Renderer_t* renderer, Player_t* player)
{
    render_creature(renderer, PLAYER_BEGIN_X, PLAYER_BEGIN_Y + PLAYER_RADIUS, PLAYER_RADIUS, PLAYER_MAX_HEALTH, player->health);
}

void render_energy(Renderer_t* renderer)
{
}

void render_screen(Game_t* game)
{
    al_set_target_bitmap(game->renderer->display_buffer);
    render_background(game->renderer);
    render_deck(game->renderer, DECK_POSITION_X, DECK_POSITION_Y);
    render_player(game->renderer, game->player);
    render_energy(game->renderer);
    render_enemies(game->renderer, game->actual_battle.n_enemys, game->actual_battle.enemys);
    render_player_hand(game->renderer, game->player->hand);
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
    al_destroy_font(renderer->font);
    free(renderer);
}