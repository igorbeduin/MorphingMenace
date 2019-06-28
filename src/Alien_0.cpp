#include "../include/Alien_0.h"

Alien_0::Alien_0(GameObject &associated) : Component::Component(associated)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, PLAYER_LVL0_SPRITE_PATH, PLAYER_LVL0_SPRITES_NUMB, PLAYER_LVL0_SPRITES_TIME));
    charSprite->SetScale(PLAYER_LVL0_SCALE, PLAYER_LVL0_SCALE);
    associated.AddComponent(charSprite);
}
void Alien_0::Update(float dt)
{}
void Alien_0::Render()
{}
bool Alien_0::Is(std::string type)
{
    return (type == "Alien_0");
}

void Alien_0::Attack()
{
    std::cout << "ATTACK" << std::endl;
}

void Alien_0::Absorb()
{
    std::cout << "ABSORB" << std::endl;
}