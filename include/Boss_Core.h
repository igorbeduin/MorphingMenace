#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "macros/Boss_Core_include.h"

class BossCore : public Component
{
public:

    BossCore(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);

private:
};

