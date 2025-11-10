/*
==============================
    includes / libs
==============================
*/
#include "renderer.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
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

    renderer->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGTH);
    must_init(renderer->display, "display");

    renderer->display_buffer = al_create_bitmap(DISPLAY_BUFFER_WIDTH, DISPLAY_BUFFER_HEIGHT);
    must_init(renderer->display_buffer, "display buffer");

    renderer->font = al_create_builtin_font();
    must_init(renderer->font, "font");
}

void draw_scaled_text(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y,
    float xscale, float yscale, int alignment,
    const char* text)
{
    ALLEGRO_TRANSFORM transform;
    al_identity_transform(&transform); // Start with an identity transform
    al_scale_transform(
        &transform, xscale,
        yscale); // Apply scaling (e.g., sx=2.0, sy=2.0 for double size)
    al_use_transform(&transform); // Use the transform for subsequent drawing

    al_draw_text(font, color, x, y, alignment, text);
    // al_draw_text(font, color, x, y, alignment, text);
    al_identity_transform(&transform);
    al_use_transform(&transform); // Use the transform for subsequent drawing
}

void draw_centered_scaled_text(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x,
    float y, float xscale, float yscale, char* text)
{
    draw_scaled_text(font, color, x, y, xscale, yscale, ALLEGRO_ALIGN_CENTRE, text);
}

/* render game background */
void render_background(Renderer_t* renderer)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
}

void render_deck(Renderer_t* renderer, int x_left, int y_top) { }

void render_health_bar(float x_begin, float x_end, float y_down_left, ALLEGRO_FONT* font) { }

void render_creature(const Renderer_t* renderer, int begin_x, int mid_y,
    int width) { }

void render_card(const Renderer_t* renderer, int x_left, int y_top) { }

void render_player_hand(Renderer_t* renderer) { }

void render_enemies(Renderer_t* renderer) { }

void render_energy(Renderer_t* renderer) { }

void render_screen(Renderer_t* renderer)
{
    al_set_target_bitmap(renderer->display_buffer);
    render_background(renderer);

    al_flip_display();
}

void clear_renderer(Renderer_t* renderer)
{
    al_destroy_display(renderer->display);
    al_destroy_bitmap(renderer->display_buffer);
    al_destroy_font(renderer->font);
}