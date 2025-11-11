/*
==============================
    includes / libs
==============================
*/

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
// #include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "constants.h"
#include "deck.h"
#include "player.h"
#include "renderer.h"
#include "utils.h"

/*
==============================
    functions
==============================
*/

/* initialize renderer struct */
void init_renderer(Renderer_t* renderer)
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    renderer->display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    must_init(renderer->display, "display");

    renderer->display_buffer = al_create_bitmap(DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT);
    must_init(renderer->display_buffer, "display buffer");

    // renderer->font = al_load_font("arial.ttf", 32, 1);
    renderer->font = al_create_builtin_font();
    must_init(renderer->font != NULL, "font");
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

void render_creature(const Renderer_t* renderer, int begin_x, int mid_y, int width)
{
    al_draw_filled_circle(begin_x + width / 2.0, mid_y, width,
        al_map_rgb(255, 255, 255));
    float x_end = begin_x + width;

    float health_bar_y = mid_y + width + 20;
    render_health_bar(begin_x, x_end, health_bar_y, renderer->font);
}

void render_card(const Renderer_t* renderer, int x_left, int y_top)
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

    al_set_target_bitmap(renderer->display_buffer);
    al_draw_scaled_bitmap(card_bitmap, 0, 0, CARD_WIDTH, CARD_HEIGHT, x_left,
        y_top, CARD_WIDTH, CARD_HEIGHT, 0);

    al_destroy_bitmap(card_bitmap);
}

void render_player_hand(Renderer_t* renderer)
{
    render_card(renderer, HAND_BEGIN_X, HAND_BEGIN_Y);
    render_card(renderer, HAND_BEGIN_X + CARD_WIDTH + 10, HAND_BEGIN_Y);
    render_card(renderer, HAND_BEGIN_X + (2 * (CARD_WIDTH + 10)), HAND_BEGIN_Y);
    render_card(renderer, HAND_BEGIN_X + (3 * (CARD_WIDTH + 10)), HAND_BEGIN_Y);
}

void render_enemies(Renderer_t* renderer)
{
    render_creature(renderer, ENEMIES_BEGIN_X, ENEMIES_BEGIN_Y + ENEMIES_RADIUS, ENEMIES_RADIUS);
    render_creature(renderer, ENEMIES_BEGIN_X + (2 * ENEMIES_RADIUS) + 30, ENEMIES_BEGIN_Y + ENEMIES_RADIUS, ENEMIES_RADIUS);
}

void render_player(Renderer_t* renderer, Player_t* player)
{

    render_creature(renderer, PLAYER_BEGIN_X, PLAYER_BEGIN_Y + PLAYER_RADIUS, PLAYER_RADIUS);
}

void render_energy(Renderer_t* renderer)
{
}

void render_screen(Renderer_t* renderer, Player_t* player)
{
    al_set_target_bitmap(renderer->display_buffer);
    render_background(renderer);
    render_deck(renderer, DECK_POSITION_X, DECK_POSITION_Y);
    render_player(renderer, player);
    render_energy(renderer);
    render_enemies(renderer);
    render_player_hand(renderer);
    al_set_target_backbuffer(renderer->display);

    al_draw_scaled_bitmap(renderer->display_buffer, 0, 0, DISPLAY_BUFFER_WIDTH,
        DISPLAY_BUFFER_HEIGHT, 0, 0, DISPLAY_WIDTH,
        DISPLAY_HEIGHT, 0);

    al_flip_display();
}

void clear_renderer(Renderer_t* renderer)
{
    al_destroy_display(renderer->display);
    al_destroy_bitmap(renderer->display_buffer);
    al_destroy_font(renderer->font);
}