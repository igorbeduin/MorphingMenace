#pragma once

#include "MorphingMenace_include.h"
#include "Engine_include.h"

#include "GameObject.h"
#include "Collider.h"
#include <iostream>

class Transformation
{
public:
    virtual void Attack();
    virtual void Absorb();
    void Downgrade();
};