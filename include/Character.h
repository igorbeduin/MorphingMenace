#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"

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
    NONE_STATE
};

class Character : public Component
{
public:
    Character(GameObject& associated, float mass, char_type type);
    void SetSpeed(Vec2 speed);
    Vec2 GetSpeed();
    void Accelerate(Vec2 acceleration = Vec2(0, 0));

    void Update(float dt);
    bool Is(std::string);
    void Render();
    void NotifyCollision(GameObject &other);

    void Move(Vec2 speed);
    void Walk(int step, float dt);
    void Jump();
    void Idle();

    bool IsFlipped();
    void limitSpeeds();
    void collisionSide(Rect boxA, Rect boxB);

    bool applyNormal;
    
private:
    char_type charType;
    Vec2 speed;
    bool flip;
    collision_side verticalCollision;
    collision_side horizontalCollision;
    character_state characterState;
    Vec2 lastPosition;
};