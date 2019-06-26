#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"

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

    bool IsFlipped();
    void limitSpeeds();

    bool applyNormal;
    
private:
    char_type charType;
    Vec2 speed;
    bool flip;
};