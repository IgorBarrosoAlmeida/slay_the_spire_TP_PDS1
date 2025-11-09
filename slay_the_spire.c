/*
==============================
    includes / libs
==============================
*/
#include "./libs/constants.h"
#include "constants.h"
#include "renderer.h"
#include "utils.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro5.h>
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

    // ===================== initialize routines =====================
    must_init(al_init(), "allegro");
    must_init(al_init_image_addon(), "allegro");
    must_init(al_init_primitives_addon(), "primitives");
    must_init(al_install_keyboard(), "keyboard");

    timer = al_create_timer(1.0 / FPS);
    must_init(timer, "timer");

    event_queue = al_create_event_queue();
    must_init(event_queue, "queue");

    // ===================== event queue registers =====================
    Renderer_t renderer;
    FillRenderer(&renderer);

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_display_event_source(renderer.display));

    ALLEGRO_EVENT event;

    // inicia o temporizador
    al_start_timer(timer);

    // initial screen
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    int playing = 1;
    while (playing) {
        al_wait_for_event(event_queue, &event);

        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            al_flip_display();

            if (al_get_timer_count(timer) % (int)FPS == 0)
                printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer) / FPS));
            break;
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            playing = 0;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            // imprime qual tecla foi
            printf("\ncodigo tecla: %d", event.keyboard.keycode);
            // Muda a cor da tela
            al_clear_to_color(al_map_rgb(rand() % 256, rand() % 256, rand() % 256));
        default:
            break;
        }
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    // ClearRenderer(&renderer);

    return SUCCESS;
}
