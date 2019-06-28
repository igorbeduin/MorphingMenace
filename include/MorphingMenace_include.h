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
    ENTOKRATON_1,
    BOSS
};

enum collision_side
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE_SIDE
};

enum character_state
{
    IDLE,
    WALKING,
    JUMPING,
    FALLING,
    ABSORBING,
    NONE_STATE
};

#ifdef CHARACTER
    #include "Character.h"
    #include "Player.h"
    #include "Entokraton_1.h"
    
    #define MAXIMUM_Y_SPEED 800
    #define PLAYER_LVL0_SPRITE_PATH "assets/img/char/player-baby-crawling.png"
    #define PLAYER_LVL0_SPRITES_NUMB 3
    #define PLAYER_LVL0_SPRITES_TIME 0.08
    #define PLAYER_LVL0_SCALE 0.15
    #define PLAYER_LVL0_MASS 1
    #define PLAYER_LVL0_STEP 200
    #define PLAYER_LVL0_JUMP -600
    #define PLAYER_INIT_POS {400, 300}

    #define ENEMY_1_SPRITE_PATH "assets/img/char/alien1_complete_movement.png"
    #define ENEMY_1_SPRITES_NUMB 7
    #define ENEMY_1_SPRITES_TIME 0.1
    #define ENEMY_1_SCALE 0.15
    #define ENEMY_1_INIT_POS {600, 300}
    #define ENEMY_1_IDLE_START 0
    #define ENEMY_1_IDLE_END 2
    #define ENEMY_1_IDLE_TIME 0.1    
    #define ENEMY_1_WALK_START 3
    #define ENEMY_1_WALK_END 6
    #define ENEMY_1_WALK_TIME 0.1
    #define ENEMY_1_COOLDOWN 1
    #define ENEMY_1_STEP 150
    #define WALK_RANGE 200
    #define STOP_RANGE 5

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
#define GRAVITY_ACCELERATION {0, 15}
#define NORMAL_ACCELERATION {0, -15}
#define SAFETY_COLLISION_RANGE 10
#define DEPTH_COLLISION_RANGE 10

#ifdef ENVIRONMENT
    #include "Force.h"
    #include "Gravity.h"
    #include "Normal.h"
    #include "Character.h"
#endif