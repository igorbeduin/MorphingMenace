#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "macros/Entokraton_1_include.h"

class Entokraton_1 : public Component
{
private:

    enum EntoState{RESTING, MOVING, ATTACKING, CHASING, DYING};
    EntoState state;
    Timer restTimer;

    Vec2 distance;
    Vec2 destination;
    Vec2 lastPosition;
    int direction = 1;// -1 = left, 1 = right 

    std::vector< std::shared_ptr<Sound> > sounds;
    bool firstTime = false;

public:
    Entokraton_1(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Attack();
};