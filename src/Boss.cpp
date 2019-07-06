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
        // std::cout << influenceFactor << std::endl;
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
void Boss::Start()
{

    Vec2 InitialPos[2];
    InitialPos[0].x = associated.box.x + 120; 
    InitialPos[0].y = associated.box.y + 715;
    InitialPos[1].x = associated.box.x + 120;
    InitialPos[1].y = associated.box.y + 515;

    for (int i = 0; i < 2; i++)
    {    
        GameObject *boss_core = new GameObject();
        std::weak_ptr<GameObject> weak_core = Game::GetInstance().GetCurrentState().AddObject(boss_core);
        std::shared_ptr<GameObject> core = weak_core.lock();

        std::shared_ptr<Character> coreCharacter(new Character(*core, 100, char_type::BOSS_CORE));
        core->AddComponent(coreCharacter);
        std::shared_ptr<Collider> CORECollider(new Collider(*core));
        core->AddComponent(CORECollider);

        core->box.x = InitialPos[i].x;
        core->box.y = InitialPos[i].y;

        coreArray.emplace_back(weak_core);   
    }
}