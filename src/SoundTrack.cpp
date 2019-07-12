#include "../include/SoundTrack.h"
#include "../include/Player.h"

SoundTrack::SoundTrack(GameObject& associated):Component(associated)
{
    // for (int i = 0; i < 3; i++)
    // {
    //     Music temp;
    //     soundtrack.emplace_back(temp);
    // }    
}

SoundTrack::~SoundTrack()
{
    
}

void SoundTrack::Start()
{
    currentOpen = NONE;
    // soundtrack[Tracks::OPEN_AREA_LVL_0].Open(LVL0_OPEN_AREA_PATH);
    // soundtrack[Tracks::OPEN_AREA_LVL_1].Open(LVL1_OPEN_AREA_PATH);
    OpenArea.x = OPEN_AREA_X;
    OpenArea.y = OPEN_AREA_Y;
    OpenArea.h = OPEN_AREA_H;
    OpenArea.w = OPEN_AREA_W;

    // soundtrack[Tracks::WATER1_LVL_0].Open(LVL0_WATER1_PATH);
    Water1.x = WATER1_X;
    Water1.y = WATER1_Y;
    Water1.h = WATER1_H;
    Water1.w = WATER1_W;
}

void SoundTrack::Update(float dt)
{
    Player *playerPtr = (Player *)associated.GetComponent("Player").get() ;

    if (OpenArea.Contains(associated.box.GetCenter().x, associated.box.GetCenter().y) &&
        playerPtr->currentForm == Player::Transformations::BABY &&
        currentOpen != OPEN_AREA_LVL_0)
    {
        // Stop();
        currentOpen = OPEN_AREA_LVL_0;
        Play(LVL0_OPEN_AREA_PATH);
    }
    else if (OpenArea.Contains(associated.box.GetCenter().x, associated.box.GetCenter().y) &&
        playerPtr->currentForm == Player::Transformations::ENTOKRATON_1 &&
        currentOpen != OPEN_AREA_LVL_1)
    {
        // Stop();
        currentOpen = OPEN_AREA_LVL_1;
        Play(LVL1_OPEN_AREA_PATH);
    }
    else if (Water1.Contains(associated.box.GetCenter().x, associated.box.GetCenter().y) &&
        playerPtr->currentForm == Player::Transformations::BABY &&
        currentOpen != WATER1_LVL_0)
    {
        // Stop();
        currentOpen = WATER1_LVL_0;
        Play(LVL0_WATER1_PATH);
    }
    
}

void SoundTrack::Render()
{
    
}

bool SoundTrack::Is(std::string type)
{
    return(type == "SoundTrack");
}

void SoundTrack::Play(std::string file)
{
    if (currentOpen != NONE)
    {      
        soundtrack.Open(file);
        soundtrack.Play(-1);
        // soundtrack[currentOpen].Play(-1);
    }
}

void SoundTrack::Stop()
{
    // soundtrack[currentOpen].Stop(2000);
    soundtrack.Stop();
}