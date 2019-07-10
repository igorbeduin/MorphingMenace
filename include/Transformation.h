#pragma once

#include "MorphingMenace_include.h"
#include "Engine_include.h"

#include "GameObject.h"
#include "Collider.h"
#include <iostream>
#include "Sprite.h"

class Sprite;


class Transformation
{
public:
    virtual void Attack() = 0;
    virtual void Absorb();
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    void Downgrade();
    virtual float GetWidth();
    virtual float GetHeight();
protected:
    std::shared_ptr<Sprite> sprite;
};