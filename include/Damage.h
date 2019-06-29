#pragma once

#include "MorphingMenace_include.h"
#include "GameObject.h"
#include "Component.h"
#include "Engine_include.h"
#include "Timer.h"

class Damage : public Component
{
public:
    Damage(GameObject &associated, int damage, float destrTime, char_type shooter = char_type::NONE_TYPE);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject &other);
    char_type Shooter();

private:
    int damage;
    float destrTime;
    Timer autodestruction;
    char_type shooter;
};