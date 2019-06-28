#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"

class Entokraton_1 : public Component
{
private:

    enum EntoState{RESTING, MOVING, ATTACKING, CHASING};
    EntoState state;
    Timer restTimer;

    Vec2 distance;
    Vec2 destination;
    Vec2 lastPosition;
    int direction = 1;// -1 = left, 1 = right 

public:
    Entokraton_1(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};