#pragma once

#include "macros/Minimap_include.h"
#include "GameObject.h"
#include "Sprite.h"
#include <iostream>

class Minimap : public Component
{
public:
    Minimap(GameObject& associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
private:
    std::shared_ptr<Sprite> map;
    std::shared_ptr<Sprite> dot;
    std::shared_ptr<Sprite> border;
};