#include "../include/Alien_0.h"
#include "../include/Game.h"

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
    Collider* associatedCollider = (Collider *)associated.GetComponent("Collider").get();
    Character* associatedCharacter = (Character *)associated.GetComponent("Character").get();

    //Creating attack
    GameObject *attack = new GameObject();
    attack->box.w = PLAYER_LVL0_ATTACK_WIDTH;
    attack->box.h = PLAYER_LVL0_ATTACK_HEIGHT;
    if (associatedCharacter->IsFlipped())
    {
        attack->box.x = associatedCollider->box.x - attack->box.w;
    }
    else
    {
        attack->box.x = associatedCollider->box.x + associatedCollider->box.w;
    }
    attack->box.y = associatedCollider->box.GetCenter().y + (PLAYER_LVL0_ATTACK_HEIGHT/2);

    std::shared_ptr<Damage> attackBehaviour(new Damage(*attack, PLAYER_LVL0_ATTACK_DAMAGE, PLAYER_LVL0_ATTACK_TIME));
    attack->AddComponent(attackBehaviour);
    std::shared_ptr<Collider> attackCollider(new Collider(*attack));
    attack->AddComponent(attackCollider);
    Game::GetInstance().GetCurrentState().AddObject(attack);
    std::cout << "ATTACK" << std::endl;
}

void Alien_0::Absorb()
{
    std::cout << "ABSORB" << std::endl;
}