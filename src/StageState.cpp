#include "../include/StageState.h"
#include "../include/InputManager.h"

StageState::StageState()
{
    GameObject* player = new GameObject();
    std::shared_ptr<Character> playerBehaviour(new Character(*player, 1, char_type::PLAYER));
    player->AddComponent(playerBehaviour);
    AddObject(player);
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
