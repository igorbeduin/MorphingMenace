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
    ENEMY,
    BOSS
};
#ifdef CHARACTER
    #include "R0350N.h"
    #include "Character.h"

    #define PLAYER_LVL0_SPRITE_PATH "assets/img/char/player-baby-crawling.png"
    #define PLAYER_LVL0_SPRITES_NUMB 3
    #define PLAYER_LVL0_SPRITES_TIME 0.08
    #define PLAYER_LVL0_SCALE 0.15
    #define PLAYER_LVL0_MASS 1
    #define PLAYER_LVL0_STEP 200
    #define PLAYER_LVL0_JUMP -400
    #define PLAYER_INIT_POS {400, 300}

    #define ENEMY_1_SPRITE_PATH "assets/img/char/alien 1 - idle.png"
    #define ENEMY_1_SPRITES_NUMB 3
    #define ENEMY_1_SPRITES_TIME 1
    #define ENEMY_1_SCALE 0.15
    #define ENEMY_1_INIT_POS {600, 300}

    #define BOSS_SPRITE_PATH "assets/img/char/boss_temporario.png"
    #define BOSS_SPRITES_NUMB 1
    #define BOSS_SPRITES_TIME 1
    #define BOSS_SCALE 0.3
    #define BOSS_INIT_POS {2000, 0}
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
    #define STAGE_BG_MUSIC_PATH "assets/audio/background_demo1.ogg"

#endif

/************************************************
*					Environment					*
*************************************************/
#define GRAVITY_ACCELERATION {0, 60}
#define NORMAL_ACCELERATION {0, -60}
#define COLLISION_RANGE 0.05
#ifdef ENVIRONMENT
    #include "Force.h"
    #include "Gravity.h"
    #include "Normal.h"
    #include "Character.h"
#endif