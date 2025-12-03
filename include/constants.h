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
#define DISPLAY_WIDTH DISPLAY_SCALE* DISPLAY_BUFFER_WIDTH
#define DISPLAY_HEIGHT DISPLAY_SCALE* DISPLAY_BUFFER_HEIGHT
#define FPS 60.0

/*
===============================
    Visual consts
===============================
*/
#define DECK_POSITION_X 50
#define DECK_POSITION_Y 800

#define DECK_WIDTH 140
#define DECK_HEIGHT 200

#define PLAYER_BEGIN_X 300
#define PLAYER_BEGIN_Y 375
#define PLAYER_RADIUS 100

#define ENEMIES_BEGIN_X 1300
#define ENEMIES_BEGIN_Y 375
#define ENEMIES_RADIUS 100

#define HEALTH_BAR_HEIGHT 20
#define HEALTH_BAR_BACKGROUND_EXTRA 1

#define HEALTH_BAR_RX 0
#define HEALTH_BAR_RY 0

#define HAND_BEGIN_X 325
#define HAND_BEGIN_Y 780

#define CARD_WIDTH 280
#define CARD_HEIGHT 420

/*
===============================
    creatures informations
===============================
*/
#define PLAYER_MAX_HEALTH 100
#define PLAYER_MAX_ENERGY 3

#define DECK_LENGTH 20
#define HAND_LENGTH 5

#define WEAK_ENEMY_MIN_HEALTH 10
#define WEAK_ENEMY_MAX_HEALTH 30

#define STRONG_ENEMY_MIN_HEALTH 40
#define STRONG_ENEMY_MAX_HEALTH 100

/*
===============================
    Returns consts
===============================
*/
#define SUCCESS 0
#define INITIALIZE_ERROR -1

#endif