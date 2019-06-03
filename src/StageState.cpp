#include "../include/StageState.h"
#include "../include/InputManager.h"

StageState::StageState()
{
    //Creating Stars background
    GameObject *stars_object = new GameObject();
    std::weak_ptr<GameObject> weak_stars =  AddObject(stars_object);
    std::shared_ptr<GameObject> stars = weak_stars.lock();
    stars->box.y = 0;
    stars->box.x = 0;
    std::shared_ptr<Sprite> stars_sprite(new Sprite(*stars, STARS_BACKGROUND_PATH));
    std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*stars));
    stars->AddComponent(stars_sprite);
    stars->AddComponent(CamFollow);
    
    //Creating planet background
    GameObject *planet_object = new GameObject();
    std::weak_ptr<GameObject> weak_planet =  AddObject(planet_object);
    std::shared_ptr<GameObject> planet = weak_planet.lock();
    planet->box.y = 0;
    planet->box.x = 0;
    std::shared_ptr<Sprite> planet_sprite(new Sprite(*planet, PLANET_BACKGROUND_PATH));
    planet->AddComponent(planet_sprite);
    planet_sprite->SetScale(PLANET_BACKGROUND_SCALE, PLANET_BACKGROUND_SCALE);

    //Creating player
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
