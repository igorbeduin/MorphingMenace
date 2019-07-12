#define SCENARIO_SCALE 1.0

#define PLAYER_LVL0_SPRITE_PATH "assets/img/char/baby.png"
#define PLAYER_LVL0_SPRITES_NUMB 22
#define PLAYER_LVL0_SPRITES_TIME 0.16
#define PLAYER_LVL0_SCALE SCENARIO_SCALE / 14
#define PLAYER_LVL0_STEP 200
#define PLAYER_LVL0_JUMP -800
#define PLAYER_INIT_POS \
    {                   \
        400, 300        \
    }
#define PLAYER_LVL0_ATTACK_WIDTH 100
#define PLAYER_LVL0_ATTACK_HEIGHT 20
#define PLAYER_LVL0_ATTACK_TIME 0.05
#define PLAYER_LVL0_ATTACK_DAMAGE 10

#define PLAYER_LVL0_IDLE_START 0
#define PLAYER_LVL0_IDLE_END 2
#define PLAYER_LVL0_IDLE_TIME 0.1

#define PLAYER_LVL0_WALK_START 3
#define PLAYER_LVL0_WALK_END 15
#define PLAYER_LVL0_WALK_TIME 0.05

#define PLAYER_LVL0_JUMP_START 7
#define PLAYER_LVL0_JUMP_END 9
#define PLAYER_LVL0_JUMP_TIME 0.1

#define PLAYER_LVL0_FALL_START 11
#define PLAYER_LVL0_FALL_END 12
#define PLAYER_LVL0_FALL_TIME 0.1

#define PLAYER_LVL0_ABSORB_START 3
#define PLAYER_LVL0_ABSORB_END 15
#define PLAYER_LVL0_ABSORB_TIME 0.03

#define PLAYER_LVL0_DAMAGED_START 16
#define PLAYER_LVL0_DAMAGED_MIDDLE 17
#define PLAYER_LVL0_DAMAGED_END 18
#define PLAYER_LVL0_DAMAGED_TIME 0.08
// #define SPACE_PUSHED 15

#define TRANSFORMATION_PATH "assets/img/char/transformation_animation.png"
#define TRANSFORMATION_NUMB 6
#define TRANSFORMATION_TIME 0.2
#define TRANSFORMATION_SCALE 0.18

#define BABY_DEATH_SOUND "assets/audio/baby/baby - death.ogg"
#define BABY_DAMAGE_SOUND "assets/audio/baby/baby - dano.ogg"
#define BABY_WALK1_SOUND "assets/audio/baby/baby - walk subindo.ogg"
#define BABY_WALK2_SOUND "assets/audio/baby/baby - walk descendo.ogg"