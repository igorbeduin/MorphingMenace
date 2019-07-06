#include "../include/Alien_0.h"
#include "../include/Game.h"
#include "../include/Character.h"
#include "../include/Player.h"

Alien_0::Alien_0(GameObject &associated) : Component::Component(associated),
                                           sprite(new Sprite(associated, PLAYER_LVL0_SPRITE_PATH, PLAYER_LVL0_SPRITES_NUMB, PLAYER_LVL0_SPRITES_TIME))
{   
    sprite->SetScale(PLAYER_LVL0_SCALE, PLAYER_LVL0_SCALE);
}
void Alien_0::Update(float dt)
{
    VerifyState();
    sprite->Update(dt);
    std::cout << (associated.GetComponent("Damage").get() == nullptr) << std::endl;
}
void Alien_0::Render()
{
    sprite->Render();
}
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

    std::shared_ptr<Damage> attackBehaviour(new Damage(*attack, PLAYER_LVL0_ATTACK_DAMAGE, PLAYER_LVL0_ATTACK_TIME, associatedCharacter->Type()));
    attack->AddComponent(attackBehaviour);
    std::shared_ptr<Collider> attackCollider(new Collider(*attack));
    attack->AddComponent(attackCollider);
    Game::GetInstance().GetCurrentState().AddObject(attack);
}

void Alien_0::Absorb()
{
    if (Player::player != nullptr)
    {
        int directABSORB_X_SPEED;
        Player::player->SetCharacterState(character_state::ABSORBING);
        Character::playerChar->IsFlipped() ? (directABSORB_X_SPEED = ABSORB_Y_SPEED) : (directABSORB_X_SPEED = -ABSORB_Y_SPEED);
        Character::playerChar->SetSpeedX(directABSORB_X_SPEED);
        Character::playerChar->SetSpeedY(ABSORB_Y_SPEED);
    }
}

void Alien_0::VerifyState()
{
    switch (Player::player->GetCharacterState())
    {
        case WALKING:
        {
            // std::cout << "WALKING" << std::endl;
            sprite->RunSpecificAnimation();
            sprite->SetStartFrame(PLAYER_LVL0_WALK_START);
            sprite->SetEndFrame(PLAYER_LVL0_WALK_END);
            sprite->SetAnimationTime(PLAYER_LVL0_WALK_TIME);
            break;
        }
        default:
        {
            // std::cout << "DEFAULT" << std::endl;
            sprite->RunSpecificAnimation();
            sprite->SetStartFrame(PLAYER_LVL0_IDLE_START);
            sprite->SetEndFrame(PLAYER_LVL0_IDLE_END);
            sprite->SetAnimationTime(PLAYER_LVL0_IDLE_TIME);
            break;
        }
    }
}

void Alien_0::UpdateAssocBox()
{
    Collider* colliderPtr = (Collider*)associated.GetComponent("Collider").get();
    colliderPtr->box.w = sprite->GetWidth();
    colliderPtr->box.h = sprite->GetHeight();
    
    associated.box.w = sprite->GetWidth();
    associated.box.h = sprite->GetHeight();
    
}
