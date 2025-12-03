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
} Renderer_t;

Renderer_t* init_renderer();

void render_screen(Game_t* game);

void clear_renderer(Renderer_t* renderer);

#endif