#pragma once

#define CHARACTER
#include "Engine_include.h"
#include "SDL_include.h"
#include "Alien_0.h"
#include "Alien_1.h"
#include "Transformation.h"

#include <iostream>
#include <stack>

class Character;

class Player : public Component
{
public:
    Player(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Walk(int step, float dt);
    void Jump();
    void Idle();
    void Attack();
    void Absorb();
    void SetCharacterState(character_state state);
    character_state GetCharacterState();
    int GetLvl();
    void LvlUp();
    void LvlDown();
    static Player* player;
    void NotifyCollision(GameObject &other);
    void Transform(char_type type);
    void EnteringState(float dt);
    void ExitingState(float dt);

private:
    character_state characterState;
    std::shared_ptr<Component> sharedChar;
    Character *characterPtr;
    std::stack<std::shared_ptr<Transformation>> transformStack;
    int lvl;
};