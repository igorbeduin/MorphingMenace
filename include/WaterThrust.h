#pragma once

#include <iostream>
#include "Force.h"
#include "Vec2.h"
#include "Character.h"

class WaterThrust : public Force
{
public:
    WaterThrust() : Force::Force(Vec2(WATERTHRUST_ACCELERATION))
    {
    }
    bool Applicable(Character *character)
    {
        if (character->applyWaterThrust)
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
        return (type == "WaterThrust");
    }

    std::string Type()
    {
        return "WaterThrust";
    }
};