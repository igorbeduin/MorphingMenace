#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Engine_include.h"
#include "Timer.h"

class Damage : public Component
{
public:
    Damage(GameObject &associated, int damage, float destrTime);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject &other);

private:
    int damage;
    float destrTime;
    Timer autodestruction;
};