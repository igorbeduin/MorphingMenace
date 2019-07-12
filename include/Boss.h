#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "macros/Boss_include.h"
#include "Game.h"

class Boss : public Component
{
public:

    Boss(GameObject &associated);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
    void Attack();
    std::vector< std::weak_ptr<GameObject> > coreArray;
    static bool defeated;

    enum BossState{RESTING, ATTACKING};
    BossState state;
    Timer WaveTimer;

private:
    int influenceReference;
};

