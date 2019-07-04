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
    BOSS,
    NONE_TYPE
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
    ATTACKING,
    NONE_STATE
};

#ifdef CHARACTER
    #include "Character.h"
    #include "Player.h"
    #include "Entokraton_1.h"
    #include "Boss.h"
    #include "Damage.h"
    
    #define ABSORB_X_SPEED 300
    #define ABSORB_Y_SPEED -700

    #define MAXIMUM_Y_SPEED 800
    #define PLAYER_INITIAL_HP 100
    #define INITIAL_INFLUENCE 10000
    //#define INITIAL_INFLUENCE 100
    #define ABSORBABLE_PERC 0.8


#define PLAYER_LVL1_SPRITE_PATH "assets/img/char/adulto.png"
#define PLAYER_LVL1_SPRITES_NUMB 18
#define PLAYER_LVL1_SPRITES_TIME 0.16
#define PLAYER_LVL1_SCALE 0.22
#define PLAYER_LVL1_STEP 200
#define PLAYER_LVL1_JUMP -800
#define PLAYER_LVL1_IDLE_START 0
#define PLAYER_LVL1_IDLE_END 1
#define PLAYER_LVL1_IDLE_TIME 0.3
#define PLAYER_LVL1_WALK_START 2
#define PLAYER_LVL1_WALK_END 5
#define PLAYER_LVL1_WALK_TIME 0.1
#define PLAYER_LVL1_JUMP_START 16
#define PLAYER_LVL1_JUMP_END 17
#define PLAYER_LVL1_JUMP_TIME 0.1
#define PLAYER_LVL1_ATTACK_WIDTH 100
#define PLAYER_LVL1_ATTACK_HEIGHT 20
#define PLAYER_LVL1_ATTACK_TIME 0.05
#define PLAYER_LVL1_ATTACK_DAMAGE 10
#define PLAYER_LVL1_ATTACK_START 6
#define PLAYER_LVL1_ATTACK_END 9

#endif

/************************************************
*					Stage					*
*************************************************/

#ifdef STATE
    #include "CameraFollower.h"
    #include "Sprite.h"
    #include "TileMap.h"

    #define SCENARIO_SCALE 1.4

    #define PLANET_BACKGROUND_PATH "assets/img/BG01.png"
    #define PLANET_BACKGROUND_SCALE SCENARIO_SCALE

    #define STARS_BACKGROUND_PATH "assets/img/StarsBackground.jpg"

    #define OCEAN_BACKGROUND_PATH "assets/img/agua.png"
    #define OCEAN_BACKGROUND_SCALE SCENARIO_SCALE
    #define OCEAN_INITIAL_POS {1732, 1650}

    #define TILESET_PATH "assets/img/tileset.png"
    #define TILEMAP_PATH "assets/map/tileMap.txt"
    #define TILE_SCALE SCENARIO_SCALE
    #define TILE_HEIGHT 32
    #define TILE_WIDTH 32
    #define STAGE_BG_MUSIC_PATH "assets/audio/background_demo1.ogg"
    #define SCENARIO_COLLISION_RADIUS 400
    

#endif

/************************************************
*					Environment					*
*************************************************/
#define GRAVITY_ACCELERATION {0, 20}
#define NORMAL_ACCELERATION {0, -20}
#define WATERTHRUST_ACCELERATION {0, -15}
#define SAFETY_COLLISION_RANGE 20
#define DEPTH_COLLISION_RANGE 20
#define COLLISION_COMPENSATION 5

#ifdef ENVIRONMENT
    #include "Force.h"
    #include "Gravity.h"
    #include "Normal.h"
    #include "Character.h"
    #include "WaterThrust.h"
#endif