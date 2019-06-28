#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"

class Character : public Component
{
public:
    Character(GameObject& associated, float mass, char_type type);
    void Accelerate(Vec2 acceleration = Vec2(0, 0));

    void Update(float dt);
    bool Is(std::string);
    void Render();
    void NotifyCollision(GameObject &other);

    void limitSpeeds();
    void collisionSide(Rect boxA, Rect boxB);
    bool applyNormal;
    Vec2 GetLastPosition();
    Vec2 GetPosition();
    Vec2 GetSpeed();
    void SetSpeed(int speedX, int speedY);
    void SetSpeedX(int speedX);
    void SetSpeedY(int speedY);
    bool IsFlipped();
    void EnableFlip();
    void DisableFlip();

    static Character* player;
private:
    Vec2 speed;
    Vec2 lastPosition;
    collision_side verticalCollision;
    collision_side horizontalCollision;
    bool flip;
};