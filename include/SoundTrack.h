#pragma once

#include "Engine_include.h"
#include "MorphingMenace_include.h"
#include "macros/SoundTrack_include.h"
#include "Component.h"
#include "Music.h"
#include "Rect.h"


#include <iostream>
#include <memory>

class SoundTrack: public Component{

private:

    // std::vector<Music> soundtrack;
    Music soundtrack;

    Rect OpenArea;
    Rect UnderDark;
    Rect Water1;
    Rect BossLair;

    enum Tracks {OPEN_AREA_LVL_0, OPEN_AREA_LVL_1, WATER1_LVL_0, NONE};
    Tracks currentOpen;
public:

    SoundTrack(GameObject& associated);
    ~SoundTrack();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Play(std::string file);
    void Stop();

};
