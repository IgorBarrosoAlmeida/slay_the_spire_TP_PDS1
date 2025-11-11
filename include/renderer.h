#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "player.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

typedef struct {
    ALLEGRO_DISPLAY* display;
    ALLEGRO_BITMAP* display_buffer;
    ALLEGRO_FONT* font;
} Renderer_t;

void init_renderer(Renderer_t* renderer);

void render_screen(Renderer_t* renderer, Player_t* player);

void clear_renderer(Renderer_t* renderer);

#endif