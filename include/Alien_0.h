#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"
#include "GameObject.h"
#include "Component.h"
#include "Transformation.h"
#include "Sprite.h"

class Sprite;

class Alien_0 : public Component, public Transformation
{
public:
    Alien_0(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Attack();
    void Absorb();
    void VerifyState();
private:
    std::shared_ptr<Sprite> sprite;
};