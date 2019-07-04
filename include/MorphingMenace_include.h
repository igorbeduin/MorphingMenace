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

#define ENTOKRATON_1_SPRITE_PATH "assets/img/char/alien1_complete_movement.png"
#define ENTOKRATON_1_SPRITES_NUMB 7
#define ENTOKRATON_1_SPRITES_TIME 0.1
#define ENTOKRATON_1_SCALE 0.15
#define ENTOKRATON_1_INIT_POS \
    {                         \
        600, 300              \
    }
#define ENTOKRATON_1_IDLE_START 0
#define ENTOKRATON_1_IDLE_END 2
#define ENTOKRATON_1_IDLE_TIME 0.1
#define ENTOKRATON_1_WALK_START 3
#define ENTOKRATON_1_WALK_END 6
#define ENTOKRATON_1_WALK_TIME 0.1
#define ENTOKRATON_1_HP 100
#define ENTOKRATON_1_IDLE1_SOUND "assets/audio/alien1/alien 1 - idle 1.ogg"
#define ENTOKRATON_1_IDLE2_SOUND "assets/audio/alien1/alien 1 - idle 2.ogg"
#define ENTOKRATON_1_WALK1_SOUND "assets/audio/alien1/alien 1 - andar.ogg"
#define ENTOKRATON_1_STEP 150
#define ENTOKRATON_1_COOLDOWN 2
#define ENTOKRATON_1_PERCEPTION 300
#define ENTOKRATON_1_ATTACK_RANGE 30
#define ENTOKRATON_1_WALK_RANGE 200
#define ENTOKRATON_1_STOP_RANGE 5
#define ENTOKRATON_1_ATTACK_WIDTH 30
#define ENTOKRATON_1_ATTACK_HEIGHT 100
#define ENTOKRATON_1_ATTACK_TIME 0.05
#define ENTOKRATON_1_ATTACK_DAMAGE 5
#define ENEMY_1_IDLE_START 0
#define ENEMY_1_IDLE_END 2
#define ENEMY_1_IDLE_TIME 0.1
#define ENEMY_1_WALK_START 3
#define ENEMY_1_WALK_END 6
#define ENEMY_1_WALK_TIME 0.1
#define ENEMY_1_COOLDOWN 2
#define ENEMY_1_STEP 150
#define ENEMY_1_PERCEPTION 250
#define ENEMY_1_ATTACK_RANGE 30
#define WALK_RANGE 200
#define STOP_RANGE 5

#endif

/************************************************
*					Stage					*
*************************************************/

#ifdef STATE
    #include "CameraFollower.h"
    #include "Sprite.h"
    #include "TileMap.h"

    #define PLANET_BACKGROUND_PATH "assets/img/BG01.png"
    #define STARS_BACKGROUND_PATH "assets/img/StarsBackground.jpg"
    #define PLANET_BACKGROUND_SCALE 1.4
    #define TILESET_PATH "assets/img/tileset.png"
    #define TILEMAP_PATH "assets/map/tileMap.txt"
    #define TILE_SCALE 1.4
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
#define SAFETY_COLLISION_RANGE 20
#define DEPTH_COLLISION_RANGE 20
#define COLLISION_COMPENSATION 5

#ifdef ENVIRONMENT
    #include "Force.h"
    #include "Gravity.h"
    #include "Normal.h"
    #include "Character.h"
#endif