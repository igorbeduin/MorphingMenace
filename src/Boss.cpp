#include "../include/Boss.h"
#include "../include/Player.h"
#include "../include/Character.h"

Boss::Boss(GameObject &associated) : Component::Component(associated),
                                     influenceReference((Character::playerChar->GetPosition() - associated.box.GetCenter()).Absolute())
{
    std::shared_ptr<Sprite> sprite(new Sprite(associated, BOSS_SPRITE_PATH));
    sprite->SetScale(BOSS_SCALE, BOSS_SCALE);
    associated.AddComponent(sprite);
}

void Boss::Update(float dt)
{
    if (Character::playerChar != nullptr)
    {
        float currentDistance = (Character::playerChar->GetPosition() - associated.box.GetCenter()).Absolute();
        float influenceFactor = influenceReference / currentDistance;
        std::cout << influenceFactor << std::endl;
        if (Player::player->GetLvl() != 0)
        {
            Player::player->SetInfluence(Player::player->GetCurrentInfluence() - influenceFactor);
        }
    }
}
void Boss::Render()
{}
bool Boss::Is(std::string type)
{
    return (type == "Boss");
}
