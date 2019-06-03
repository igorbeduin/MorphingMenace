#pragma once
/************************************************
*					General						*
*************************************************/
#define GAME_NAME "The Morphing Menace!"

/************************************************
*					Character					*
*************************************************/
#ifdef CHARACTER
    enum char_type
    {
        // Different types of characters that the game might have
        PLAYER,
        ENEMY
    };
    #define PLAYER_LVL0_SPRITE_PATH "assets/img/char/player-baby-crawling.png"
    #include "R0350N.h"
    #include "Character.h"
#endif

/************************************************
*					Stage					*
*************************************************/
#ifdef STATE
    #include "CameraFollower.h"
    #include "Sprite.h"

    #define PLANET_BACKGROUND_PATH "assets/img/PlanetBackground.png"
    #define STARS_BACKGROUND_PATH "assets/img/StarsBackground.jpg"
    #define PLANET_BACKGROUND_SCALE 0.3
#endif
