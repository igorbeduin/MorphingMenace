#pragma once

#define CHARACTER
#include "Engine_include.h"
#include "SDL_include.h"
#include "Alien_0.h"
#include "Alien_1.h"
#include "Alien_2.h"
#include "Transformation.h"

#include <iostream>
#include <stack>

class Character;

class Player : public Component
{
public:
    enum Transformations {BABY, ENTOKRATON_1, ENTOKRATON_2};
    Transformations currentForm;
    
    Player(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Walk(int step);
    void Jump();
    void Idle();
    void Attack();
    void IsDamaged();
    void Absorb();
    void SetCharacterState(character_state state);
    character_state GetCharacterState();
    int GetLvl();
    void LvlUp(Transformations next_form);
    void LvlDown();
    static Player* player;
    void NotifyCollision(GameObject &other);
    void Transform(char_type type, Vec2 enemy_position);
    void EnteringState();
    void ExitingState();
    int GetCurrentInfluence();
    int GetMaxInfluence();
    void SetInfluence(int influence);
    void Swim(int swimStep);
    void VerifiesInfluence();
    void Joystick();
    void FollowingCamera();
    void UpdateVariables(float dt);
    Timer HatchTime;

private:
    character_state characterState;
    std::shared_ptr<Component> sharedChar;
    Character *characterPtr;
    std::stack<std::shared_ptr<Transformation>> transformStack;
    int lvl;
    int currentInfluence;
    int maxInfluence;
    float deltaTime;
    int walkStep;
    int jumpVelocity;
};