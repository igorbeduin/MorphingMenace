#include "../include/TitleState.h"
#include "../include/InputManager.h"
#include "../include/Game.h"
#include "../include/CameraFollower.h"
#include "../include/Resources.h"

TitleState::TitleState()
{
    started = false;

    GameObject *title_object = new GameObject();

    std::weak_ptr<GameObject> weak_title = AddObject(title_object);
    std::shared_ptr<GameObject> title = weak_title.lock();

    title->box.x = 0;
    title->box.y = 0;

    std::shared_ptr<Sprite> title_sprite(new Sprite(*title, TITLE_PATH));
    std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*title));

    title->AddComponent(title_sprite);
    title->AddComponent(CamFollow);

    // GameObject *text_object = new GameObject();

    // std::weak_ptr<GameObject> weak_text = AddObject(text_object);
    // std::shared_ptr<GameObject> text = weak_text.lock();

    // std::shared_ptr<Text> title_text(new Text(*text, FONT_PATH, FONT_SIZE, Text::BLENDED, TITLE_TEXT, TEXT_COLOR, SCREEN_TIME));
    // text->box.x = 512 - text->box.w/2;
    // text->box.y = 512 - text->box.h/2;
    // text->AddComponent(title_text);
}

TitleState::~TitleState()
{
    objectArray.clear();
}


void TitleState::LoadAssets()
{
    Resources::AddImage(TITLE_PATH);
    Resources::AddImage(LOADING_PATH);
}

void TitleState::Update(float dt)
{
    InputManager& input = InputManager::GetInstance();
    Game& game = Game::GetInstance();

    if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) 
    {
        quitRequested = true;
    }

    if (started)
    {
        StageState* stageState = new StageState();
        game.Push(stageState);
        started = false;
    }
    

    if (input.KeyPress(SPACE_KEY))
    {
        GameObject *loading_object = new GameObject();

        std::weak_ptr<GameObject> weak_loading = AddObject(loading_object);
        std::shared_ptr<GameObject> loading = weak_loading.lock();

        loading->box.x = 0;
        loading->box.y = 0;

        std::shared_ptr<Sprite> loading_sprite(new Sprite(*loading, LOADING_PATH));
        loading_sprite->SetScale(0.2, 0.2);
        loading->AddComponent(loading_sprite);
        started = true;
    }

    UpdateArray(dt);
}

void TitleState::Render()
{
    RenderArray();
}

void TitleState::Start()
{
    StartArray();
}

void TitleState::Pause()
{

}

void TitleState::Resume()
{
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}
