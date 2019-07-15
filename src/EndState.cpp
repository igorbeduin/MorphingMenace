#include "../include/EndState.h"
#include "../include/GameData.h"
#include "../include/InputManager.h"
#include "../include/Game.h"

EndState::EndState()
{

    if (GameData::playerVictory) {

        GameObject *victory_object = new GameObject();

        std::weak_ptr<GameObject> weak_victory =  AddObject(victory_object);
        std::shared_ptr<GameObject> victory = weak_victory.lock();

        victory->box.x = 0;
        victory->box.y = 0;
        std::shared_ptr<Sprite> victory_sprite(new Sprite(*victory, VICTORY_PATH));
        std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*victory));
        victory->AddComponent(victory_sprite);
        // victory->AddComponent(CamFollow);

        // GameObject *win_text_object = new GameObject();

        // std::weak_ptr<GameObject> weak_win_text = AddObject(win_text_object);
        // std::shared_ptr<GameObject> win_text = weak_win_text.lock();

        // std::shared_ptr<Text> you_win(new Text(*win_text, FONT_PATH, END_FONT_SIZE, Text::BLENDED, VICTORY_MSG, TEXT_COLOR, END_SCREEN_TIME));
        // win_text->box.x = 512 - win_text->box.w/2;
        // win_text->box.y = 50 - win_text->box.h/2;
        // win_text->AddComponent(you_win);

        // backgroundMusic.Open(VICTORY_MUSIC);

    }
    else
    {

        GameObject *defeat_object = new GameObject();

        std::weak_ptr<GameObject> weak_defeat =  AddObject(defeat_object);
        std::shared_ptr<GameObject> defeat = weak_defeat.lock();

        defeat->box.x = 0;
        defeat->box.y = -200;
        std::shared_ptr<Sprite> defeat_sprite(new Sprite(*defeat, DEFEAT_PATH));
        std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*defeat));
        defeat->AddComponent(defeat_sprite);
        // defeat->AddComponent(CamFollow);

        // GameObject *lost_text_object = new GameObject();

        // std::weak_ptr<GameObject> weak_lost_text = AddObject(lost_text_object);
        // std::shared_ptr<GameObject> lost_text = weak_lost_text.lock();

        // std::shared_ptr<Text> you_lost(new Text(*lost_text, FONT_PATH, END_FONT_SIZE, Text::BLENDED, DEFEAT_MSG, TEXT_COLOR, END_SCREEN_TIME));
        // lost_text->box.x = 512 - lost_text->box.w/2;
        // lost_text->box.y = 50 - lost_text->box.h/2;
        // lost_text->AddComponent(you_lost);

        // backgroundMusic.Open(DEFEAT_MUSIC);
    }

    // GameObject *instruction_object = new GameObject();

    // std::weak_ptr<GameObject> weak_instruction = AddObject(instruction_object);
    // std::shared_ptr<GameObject> instruction = weak_instruction.lock();
    // std::shared_ptr<Text> instruction_text(new Text(*instruction, FONT_PATH, END_FONT_SIZE, Text::BLENDED, INSTRUCTION_MSG, TEXT_COLOR, END_SCREEN_TIME));
    // instruction->box.x = 512 - instruction->box.w/2;
    // instruction->box.y = 550 - instruction->box.h/2;
    // instruction->AddComponent(instruction_text);
}

EndState::~EndState()
{
}

void EndState::LoadAssets()
{
}

void EndState::Update(float dt)
{
    InputManager& input = InputManager::GetInstance();
    Game& game = Game::GetInstance();

    if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY))
    {
        quitRequested = true;
    }

    if (input.KeyPress(SPACE_KEY))
    {
        TitleState* titleState = new TitleState();
        game.Push(titleState);
        popRequested = true;
    }

    UpdateArray(dt);
}

void EndState::Render()
{
    RenderArray();
}

void EndState::Start()
{
    LoadAssets();
    StartArray();
}

void EndState::Pause()
{
}

void EndState::Resume()
{
}
