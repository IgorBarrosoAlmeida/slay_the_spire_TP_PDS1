#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

/*
===============================
    Display consts
===============================
*/
#define DISPLAY_BUFFER_WIDTH 1920.0
#define DISPLAY_BUFFER_HEIGHT 1080.0

#define DISPLAY_SCALE 0.7
#define SCREEN_WIDTH DISPLAY_SCALE* DISPLAY_BUFFER_WIDTH
#define SCREEN_HEIGTH DISPLAY_SCALE* DISPLAY_BUFFER_HEIGHT
#define FPS 100

/*
===============================
    Visual consts
===============================
*/
/*
#define DRAW_DECK_X 15
#define DRAW_DECK_Y 910

#define DECK_WIDTH 80
#define DECK_HEIGHT 80

#define PLAYER_BEGIN_X 300
#define PLAYER_BEGIN_Y 375
#define PLAYER_RADIUS 100

#define HEALTH_BAR_HEIGHT 20
#define HEALTH_BAR_BACKGROUND_EXTRA 1

#define HEALTH_BAR_RX 0
#define HEALTH_BAR_RY 0

#define HAND_BEGIN_X 325
#define HAND_BEGIN_Y 780

#define CARD_WIDTH 280
#define CARD_HEIGHT 420

*/

/*
===============================
    Returns consts
===============================
*/
#define SUCCESS 0
#define INITIALIZE_ERROR -1

typedef enum {
    MOVE_LEFT = 0,
    MOVE_RIGHT = 1,
} CursorMovementDirection_t;
#endif