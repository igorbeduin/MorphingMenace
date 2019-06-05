#pragma once

#define ENVIRONMENT
#include "MorphingMenace_include.h"

#include "Force.h"
#include "Character.h"

#include <vector>
#include <memory>

class Environment
{
public:
    Environment();
    ~Environment();
    static void AddForce(std::shared_ptr<Force> force);
    static void ApplyForces(Character* character);

private:
    static std::vector<std::shared_ptr<Force>> forcesArray;
    Character* character;
};