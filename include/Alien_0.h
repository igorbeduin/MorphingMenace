#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Transformation.h"
#include "Sprite.h"

class Alien_0 : public Component, public Transformation
{
public:
    Alien_0(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Attack();
    void Absorb();
};