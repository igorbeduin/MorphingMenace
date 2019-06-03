#pragma once

#include <vector>

#include "Force.h"
#include "GameObject.h"

class Environment
{
public:
    Environment();
    ~Environment();
    static void ApplyForces(GameObject *go);

private:
    static std::vector<Force> forcesArray;
    GameObject* go;
};