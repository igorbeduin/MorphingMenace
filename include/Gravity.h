#pragma once

#include <iostream>
#include "Force.h"
#include "Vec2.h"
#include "Character.h"

class Gravity : public Force
{
public:
    Gravity() : Force::Force(Vec2(GRAVITY_ACCELERATION))
    {}
    bool Applicable(Character* character)
    {   
        if (character->applyGravity && !character->applyNormal)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    }

    bool Is(std::string type)
    {
        return (type == "Gravity");
    }

    std::string Type()
    {
        return "Gravity";
    }
};