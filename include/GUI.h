#pragma once

#include "Component.h"
#include "GameObject.h"

class GUI : public Component
{
public:
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};