#pragma once
/************************************************
*					General						*
*************************************************/
#define GAME_NAME "The Morphing Menace!"

/************************************************
*					Character					*
*************************************************/
enum char_type
{
    // Different types of characters that the game might have
    PLAYER,
    ENEMY
};
#ifdef CHARACTER
    #define PLAYER_LVL0_SPRITE_PATH "assets/img/char/player-baby-crawling.png"
    #define PLAYER_LVL0_SPRITES_NUMB 3
    #define PLAYER_LVL0_SPRITES_TIME 0.08
    #define PLAYER_LVL0_SCALE 0.15
    #define PLAYER_LVL0_MASS 1
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
    #define STAGE_BG_MUSIC_PATH "assets/img/background_demo1.ogg"

#endif

/************************************************
*					Environment					*
*************************************************/
#define GRAVITY_ACCELERATION {0, 3}
#ifdef ENVIRONMENT
    #include "Force.h"
    #include "Gravity.h"
    #include "Character.h"
#endif