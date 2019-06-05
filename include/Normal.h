#pragma once

#include <iostream>
#include "Force.h"
#include "Vec2.h"
#include "Character.h"

class Normal : public Force
{
public:
    Normal() : Force::Force(Vec2(NORMAL_ACCELERATION))
    {
    }
    bool Applicable(Character *character)
    {
        if (character->applyNormal)
        {
            character->applyNormal = false;
            return true;
        }
        else
        {
            return false;
        }
        
    }

    bool Is(std::string type)
    {
        return (type == "Normal");
    }

    std::string Type()
    {
        return "Normal";
    }
};