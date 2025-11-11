/*
==============================
    includes / libs
==============================
*/
#include "constants.h"
#include "deck.h"
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
    _Bool playing = true, redraw = true;
    Player_t player;

    // ===================== initialize routines =====================
    must_init(al_init(), "allegro");
    must_init(al_init_image_addon(), "allegro addon");
    must_init(al_init_primitives_addon(), "primitives addon");
    must_init(al_install_keyboard(), "keyboard");
    init_player(&player);
    // al_init_font_addon();
    // must_init(al_init_ttf_addon(), "font ttf addon");

    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    event_queue = al_create_event_queue();
    must_init(event_queue, "queue");

    // ===================== event queue registers =====================
    Renderer_t renderer;
    init_renderer(&renderer);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(renderer.display));

    ALLEGRO_EVENT event;

    // inicia o temporizador
    al_start_timer(timer);

    while (playing) {
        al_wait_for_event(event_queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;

            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            playing = false;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Q:
                playing = false;

                printf("Apertou Q");
                break;
            }

            break;
        }

        if (playing && redraw) {
            render_screen(&renderer, &player);
            redraw = false;
        }
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    clear_renderer(&renderer);

    return SUCCESS;
}
