#pragma once

#include <string>

#include "GameObject.h"
#include "Vec2.h"
#include "Character.h"


class Force 
{
public:
    Force(Vec2 acceleration);
    virtual ~Force();
    virtual bool Applicable(Character* character) = 0;
    void Apply(Character* character);
    void SetAcceleration(Vec2 Acceleration);
    Vec2 GetAcceleration();
    virtual bool Is(std::string type) = 0;
    virtual std::string Type() = 0;
    static void Update(float dt);

private:
    Vec2 acceleration;
    static float deltaTime;
};