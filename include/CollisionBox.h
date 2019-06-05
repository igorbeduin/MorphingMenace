#pragma once

#include <iostream>
#include "GameObject.h"

class CollisionBox : public Component
{
public:
    CollisionBox(GameObject& associated) : Component::Component(associated)
    {}

    void Update(float dt)
    {}
    void Render()
    {}
    bool Is(std::string type)
    {
        return (type == "CollisionBox");
    }
};