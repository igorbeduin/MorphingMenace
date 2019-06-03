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
    #include "TileMap.h"

    #define PLANET_BACKGROUND_PATH "assets/img/PlanetBackground.png"
    #define STARS_BACKGROUND_PATH "assets/img/StarsBackground.jpg"
    #define PLANET_BACKGROUND_SCALE 0.3
    #define TILESET_PATH "assets/img/Chao4x2.png"
    #define TILEMAP_PATH "assets/map/tileMap.txt"
    #define TILE_SCALE 0.0625
    #define TILE_HEIGHT 1024
    #define TILE_WIDTH 1024

#endif
