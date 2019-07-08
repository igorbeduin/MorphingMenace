#include "../include/Boss.h"
#include "../include/Player.h"
#include "../include/Character.h"

Boss::Boss(GameObject &associated) : Component::Component(associated),
                                     influenceReference((Character::playerChar->GetPosition() - associated.box.GetCenter()).Absolute()),
                                     state(RESTING)
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

        switch (state)
        {
            case RESTING:
            //espera o player chegar perto (limite na entrada da caverna)
            if (Character::playerChar->GetPosition().x > associated.box.x                    &&
                Character::playerChar->GetPosition().x < associated.box.x + associated.box.w &&
                Character::playerChar->GetPosition().y > associated.box.y                    &&
                Character::playerChar->GetPosition().y < associated.box.y + associated.box.h)
            {
                if ( WaveTimer.Get() >= WAVE_COOLDOWN )

                {
                    state = ATTACKING;

                }
                else
                {
                    WaveTimer.Update(dt);
                }
            }


                break;

            case ATTACKING:
                WaveTimer.Restart();
                //player chegou perto o suficiente, manda o ovo(?) atirar projeteis durante o tempo da wave (waveTimer)
                //passando o wave timer volta para o resting por um tempo de cooldown
                Attack();
                state = RESTING;
                break;

            default:
                break;
        }
        
    }

    for (int i = 0; i < (int)coreArray.size(); i++)
    {
        if (coreArray[i].expired())
        {
            coreArray.erase(coreArray.begin() + i);
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
void Boss::Attack()
{
    if (Character::playerChar != nullptr)
    {
        if (coreArray.size() > 1) 
        {
            BossCore *core = (BossCore *)coreArray[0].lock()->GetComponent("BossCore").get();           
            core->Shoot(Character::playerChar->GetPosition());
        }
    }
}