#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "macros/Boss_include.h"

class Boss : public Component
{
public:

    Boss(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
    std::vector< std::weak_ptr<GameObject> > coreArray;

private:
    int influenceReference;
};

