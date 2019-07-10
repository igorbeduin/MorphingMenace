#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"
#include "GameObject.h"
#include "Component.h"
#include "Transformation.h"
#include "Sprite.h"
#include "Timer.h"
#include "macros/Alien_2_include.h"

class Sprite;

class Alien_2 : public Component, public Transformation
{
public:
    Alien_2(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Attack();
    void VerifyState();
    void UpdateAssocBox();

private:
    std::shared_ptr<Sprite> sprite;
};