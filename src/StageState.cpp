#include "../include/StageState.h"

StageState::StageState()
{
}

void StageState::LoadAssets()
{
}

void StageState::Update(float dt)
{
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }

    // std::cout << "(int)objectArray.size(): " << (int)objectArray.size() << std::endl;
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
}

void StageState::Render()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

StageState::~StageState()
{
}

void StageState::Start()
{
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}
