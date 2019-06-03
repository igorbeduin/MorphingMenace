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
#endif