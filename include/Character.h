#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"

class Character : public Component
{
public:
    Character(GameObject& associated, float mass, char_type type);
    void SetMass(float mass);
    float GetMass();
    void Move(Vec2 dst);

    void Update(float dt);
    bool Is(std::string);
    void Render();
    
private:
    char_type charType;
    float mass;
    Vec2 speed;
};