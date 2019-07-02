#include "../include/GUI.h"

GUI::GUI(GameObject &associated) : Component::Component(associated),
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