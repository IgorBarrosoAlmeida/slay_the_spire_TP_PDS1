#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

// FORWARD DECLARATION:
typedef struct game Game_t;

typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* display_buffer;
    ALLEGRO_FONT* font;

    // Imagens
    ALLEGRO_BITMAP* img_background;
    ALLEGRO_BITMAP* img_player;
    ALLEGRO_BITMAP* img_enemy_weak;
    ALLEGRO_BITMAP* img_enemy_strong;
    ALLEGRO_BITMAP* img_boss;
    ALLEGRO_BITMAP* img_dead_enemy;
    ALLEGRO_BITMAP* img_boss_battle;
    ALLEGRO_BITMAP* img_game_over;
    ALLEGRO_BITMAP* img_victory;
    // ALLEGRO_BITMAP* img_boss;
    ALLEGRO_BITMAP* img_shield;
    ALLEGRO_BITMAP* img_sword;

} Renderer_t;

Renderer_t* init_renderer();

void render_screen(Game_t* game);

void clear_renderer(Renderer_t* renderer);

void draw_scaled_text(ALLEGRO_FONT* font, ALLEGRO_COLOR color, float x, float y,
    float xscale, float yscale, int alignment,
    const char* text);

#endif