#pragma once

#include "macros/GUI_include.h"
#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"

class GUI : public Component
{
public:
    GUI(GameObject& associated, GameObject& other);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void VerifyLife();
    void VerifyInfuence();

private:
    GameObject& other;
    std::shared_ptr<Sprite> lifeSprite;
    std::shared_ptr<Sprite> influenceSprite;

};