#include "../include/Alien_1.h"
#include "../include/Game.h"
#include "../include/Character.h"
#include "../include/Player.h"

Alien_1::Alien_1(GameObject &associated) : Component::Component(associated),
                                           sprite(new Sprite(associated, PLAYER_LVL1_SPRITE_PATH, PLAYER_LVL1_SPRITES_NUMB, PLAYER_LVL1_SPRITES_TIME))
{

    sprite->SetScale(PLAYER_LVL1_SCALE, PLAYER_LVL1_SCALE);
}
void Alien_1::Update(float dt)
{   
    VerifyState();
    if (Player::player->GetCharacterState() == character_state::ATTACKING)
    {
        atkTimer.Update(dt);
        if (atkTimer.Get() >= (PLAYER_LVL1_ATTACK_END - PLAYER_LVL1_ATTACK_START + 1) * PLAYER_LVL1_ATTACK_TIME)
        {
            Player::player->SetCharacterState(character_state::IDLE);
            atkTimer.Restart();
        }
    }
    sprite->Update(dt);
}
void Alien_1::Render()
{
    sprite->Render();
    std::cout << "sprite->GetCurrentFrame():" << sprite->GetCurrentFrame() << std::endl;
}
bool Alien_1::Is(std::string type)
{
    return (type == "Alien_1");
}

void Alien_1::Attack()
{
    Collider *associatedCollider = (Collider *)associated.GetComponent("Collider").get();
    Character *associatedCharacter = (Character *)associated.GetComponent("Character").get();

    //Creating attack
    GameObject *attack = new GameObject();
    attack->box.w = (associatedCollider->box.w / 2);
    attack->box.h = associatedCollider->box.h;
    if (associatedCharacter->IsFlipped())
    {
        attack->box.x = associatedCollider->box.GetCenter().x - attack->box.w;
    }
    else
    {
        attack->box.x = associatedCollider->box.GetCenter().x;
    }
    attack->box.y = associatedCollider->box.y;

    std::shared_ptr<Damage> attackBehaviour(new Damage(*attack, PLAYER_LVL1_ATTACK_DAMAGE, PLAYER_LVL1_ATTACK_TIME, associatedCharacter->Type()));
    attack->AddComponent(attackBehaviour);
    std::shared_ptr<Collider> attackCollider(new Collider(*attack));
    attack->AddComponent(attackCollider);
    Game::GetInstance().GetCurrentState().AddObject(attack);
}

void Alien_1::VerifyState()
{
    switch (Player::player->GetCharacterState())
    {
    case WALKING:
    {
        // std::cout << "WALKING" << std::endl;
        sprite->RunSpecificAnimation();
        sprite->SetStartFrame(PLAYER_LVL1_WALK_START);
        sprite->SetEndFrame(PLAYER_LVL1_WALK_END);
        sprite->SetAnimationTime(PLAYER_LVL1_WALK_TIME);
        break;
    }
    case JUMPING:
    {
        // std::cout << "JUMPING" << std::endl;
        sprite->RunSpecificAnimation();
        sprite->SetStartFrame(PLAYER_LVL1_JUMP_START);
        sprite->SetEndFrame(PLAYER_LVL1_JUMP_END);
        sprite->SetAnimationTime(PLAYER_LVL1_JUMP_TIME);
        break;
    }
    case ATTACKING:
    {
        // std::cout << "ATTACKING" << std::endl;
        sprite->RunSpecificAnimation();
        sprite->SetStartFrame(PLAYER_LVL1_ATTACK_START);
        sprite->SetEndFrame(PLAYER_LVL1_ATTACK_END);
        sprite->SetAnimationTime(PLAYER_LVL1_ATTACK_TIME);
        break;
    }

    case IDLE:
    {
        // std::cout << "DEFAULT" << std::endl;
        sprite->RunSpecificAnimation();
        sprite->SetStartFrame(PLAYER_LVL1_IDLE_START);
        sprite->SetEndFrame(PLAYER_LVL1_IDLE_END);
        sprite->SetAnimationTime(PLAYER_LVL1_IDLE_TIME);
        break;
    }
    default:
    {
        break;
    }
    }
}

void Alien_1::UpdateAssocBox()
{
    Collider* colliderPtr = (Collider*)associated.GetComponent("Collider").get();
    colliderPtr->box.w = sprite->GetWidth();
    colliderPtr->box.h = sprite->GetHeight();
}
