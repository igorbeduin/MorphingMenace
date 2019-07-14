#pragma once

#define CHARACTER
#include "Timer.h"
#include "macros/WaterDamage_include.h"
#include "MorphingMenace_include.h"
#include "GameObject.h"
#include "Component.h"
#include <iostream>

class WaterDamage : public Component
{
public:
    WaterDamage(GameObject& associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
private:
    Timer clock;
    int cooldown;
};