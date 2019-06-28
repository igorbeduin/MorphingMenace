#include "../include/Entokraton_1.h"

Entokraton_1::Entokraton_1(GameObject &associated) : Component::Component(associated)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENEMY_1_SPRITE_PATH, ENEMY_1_SPRITES_NUMB, ENEMY_1_SPRITES_TIME));
    charSprite->SetScale(ENEMY_1_SCALE, ENEMY_1_SCALE);
    associated.AddComponent(charSprite);
}
void Entokraton_1::Update(float dt)
{}
void Entokraton_1::Render()
{}
bool Entokraton_1::Is(std::string type)
{
    return (type == "Entokraton_1");
}