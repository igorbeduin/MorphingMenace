#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"

class Entokraton_1 : public Component
{
public:
    Entokraton_1(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};