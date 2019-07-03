#include "../include/GUI.h"
#include "../include/Game.h"

GUI::GUI(GameObject &associated, GameObject& other) : Component::Component(associated),
                                   other(other),
                                   lifeSprite(new Sprite(associated, GUI_LIFE_PATH, GUI_LIFE_FRAMES_NUMBER, GUI_LIFE_FRAME_TIME)),
                                   influenceSprite(new Sprite(associated, GUI_INFLUENCE_PATH, GUI_INFLUENCE_FRAMES_NUMBER, GUI_INFLUENCE_FRAME_TIME))
{
    lifeSprite->SetScale(GUI_SCALE, GUI_SCALE);
    influenceSprite->SetScale(GUI_SCALE, GUI_SCALE);
}

void GUI::Update(float dt)
{
    lifeSprite->Update(dt);
    influenceSprite->Update(dt);
    associated.box.x += 15;
    associated.box.y += -30;
    VerifyLife();
    VerifyInfuence();
}

void GUI::Render()
{
    lifeSprite->Render();
    influenceSprite->Render();
}

bool GUI::Is(std::string type)
{
    return (type == "GUI");
}

void GUI::VerifyLife()
{
    if (!Game::GetInstance().GetCurrentState().GetObjectPtr(&other).expired())
    {
        Character* otherCharPtr = (Character*)other.GetComponent("Character").get();
        if (otherCharPtr != nullptr)
        {
            if (otherCharPtr->GetCurrentHP() > 0.66 * otherCharPtr->GetMaxHP() && otherCharPtr->GetCurrentHP() <= otherCharPtr->GetMaxHP())
            {
                lifeSprite->SetFrame(0);
            }
            if (otherCharPtr->GetCurrentHP() > 0.33 * otherCharPtr->GetMaxHP() && otherCharPtr->GetCurrentHP() <= 0.66 * otherCharPtr->GetMaxHP())
            {
                lifeSprite->SetFrame(1);
            }
            if (otherCharPtr->GetCurrentHP() > 0 && otherCharPtr->GetCurrentHP() <= 0.33 * otherCharPtr->GetMaxHP())
            {
                lifeSprite->SetFrame(2);
            }
            if (otherCharPtr->GetCurrentHP() <= 0)
            {
                associated.RequestDelete();
            }
        }
        else
        {
            associated.RequestDelete();
        }
    }
}

void GUI::VerifyInfuence()
{
    influenceSprite->SetFrame(0);
}