#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "macros/Entokraton_2_include.h"

class Entokraton_2 : public Component
{
private:

    enum EntoState{RESTING, MOVING, DAMAGED, DYING};
    EntoState state;
    Timer restTimer;

    Vec2 distance;
    Vec2 destination;
    Vec2 lastPosition;
    int direction = 1;// -1 = left, 1 = right 

    std::vector< std::shared_ptr<Sound> > sounds;
    bool firstTime = false;
    float EasingCounter;
    float DCEasing;
    void Easing();

public:
    Entokraton_2(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};