#pragma once

#include "GameObject.h"
#include "Vec2.h"


class Force 
{
public:
    Force(Vec2 direction, int acceleration);
    virtual bool Applicable(GameObject* go) = 0;
    void Apply(GameObject* go);
    void SetAcceleration(int acceleration);
    void SetDirection(Vec2 direction);
    int GetAcceleration();
    Vec2 GetDirection();

private:
    Vec2 direction;
    int acceleration;
};