#pragma once
/************************************************
*					General						*
*************************************************/
#define GAME_NAME "The Morphing Menace!"
#define ABSORB_X_SPEED 100
#define ABSORB_Y_SPEED -300
#define SWIM_Y_SPEED -800
#define MAXIMUM_Y_SPEED 600
#define MAXIMUM_Y_SPEED_WATER 100
#define FALLING_SPEED 5
#define PLAYER_INITIAL_HP 100
#define INITIAL_INFLUENCE 10000
#define ABSORBABLE_PERC 0.8
#define SCENARIO_SCALE 1.1
#define CHARACTER_GLOW_PATH "assets/img/efx/char_glow.png"

/************************************************
*					Character					*
*************************************************/
enum char_type
{
    // Different types of characters that the game might have
    PLAYER,
    ENTOKRATON_1,
    ENTOKRATON_2,
    BOSS,
    BOSS_CORE,
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
    #include "Entokraton_2.h"
    #include "Boss.h"
    #include "Boss_Core.h"
    #include "Damage.h"
    


#define PLAYER_LVL1_SPRITE_PATH "assets/img/char/adulto.png"
#define PLAYER_LVL1_SPRITES_NUMB 18
#define PLAYER_LVL1_SPRITES_TIME 0.16
#define PLAYER_LVL1_SCALE SCENARIO_SCALE / 6.3636
#define PLAYER_LVL1_STEP 200
#define PLAYER_LVL1_JUMP -850
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

    #define PLANET_BACKGROUND_PATH "assets/img/BG01.png"
    #define PLANET_BACKGROUND_SCALE SCENARIO_SCALE

    #define STARS_BACKGROUND_PATH "assets/img/StarsBackground.jpg"

    #define OCEAN1_BACKGROUND_PATH "assets/img/agua1.png"
    #define OCEAN1_BACKGROUND_SCALE SCENARIO_SCALE
    #define OCEAN1_INITIAL_POS {1370, 1300}
    #define OCEAN2_BACKGROUND_PATH "assets/img/agua2.png"
    #define OCEAN2_BACKGROUND_SCALE SCENARIO_SCALE * 2
    #define OCEAN2_INITIAL_POS {3900, 1332}

    #define TILESET_PATH "assets/img/tileset.png"
    #define TILEMAP_PATH "assets/map/tileMap.txt"
    #define TILE_SCALE SCENARIO_SCALE
    #define TILE_HEIGHT 32
    #define TILE_WIDTH 32
    #define STAGE_BG_MUSIC_PATH "assets/audio/background_demo1.ogg"
    #define SCENARIO_COLLISION_RADIUS 500
    

#endif

/************************************************
*					Environment					*
*************************************************/
#define GRAVITY_ACCELERATION_Y 15
#define GRAVITY_ACCELERATION_X 0
#define GRAVITY_ACCELERATION {GRAVITY_ACCELERATION_X, GRAVITY_ACCELERATION_Y}
#define NORMAL_ACCELERATION_Y -1 * GRAVITY_ACCELERATION_Y
#define NORMAL_ACCELERATION_X 0
#define NORMAL_ACCELERATION {NORMAL_ACCELERATION_X, GRAVITY_ACCELERATION_Y}
#define WATERTHRUST_ACCELERATION_Y  -1 * GRAVITY_ACCELERATION_Y / 1.33
#define WATERTHRUST_ACCELERATION_X 0
#define WATERTHRUST_ACCELERATION {WATERTHRUST_ACCELERATION_X, WATERTHRUST_ACCELERATION_Y}
#define SAFETY_COLLISION_RANGE 5
#define DEPTH_COLLISION_RANGE 10
#define COLLISION_COMPENSATION 10

#ifdef ENVIRONMENT
    #include "Force.h"
    #include "Gravity.h"
    #include "Normal.h"
    #include "Character.h"
    #include "WaterThrust.h"
#endif