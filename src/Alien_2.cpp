#include "../include/Alien_2.h"
#include "../include/Game.h"
#include "../include/Character.h"
#include "../include/Player.h"

Alien_2::Alien_2(GameObject &associated) : Component::Component(associated),
                                           sprite(new Sprite(associated, PLAYER_LVL2_SPRITE_PATH, PLAYER_LVL2_SPRITES_NUMB, PLAYER_LVL2_SPRITES_TIME))
{

    sprite->SetScale(PLAYER_LVL2_SCALE, PLAYER_LVL2_SCALE);
}
void Alien_2::Update(float dt)
{   
    // Character* characterPtr = (Character*)associated.GetComponent("Character").get();

    // characterPtr->applyWaterThrust = false;
    // if (characterPtr->VerifyOcean())
    // {
    //     characterPtr->applyWaterThrust = true;
    // }
    // else
    // {
    //     characterPtr->applyGravity = true;
    // }
    
    VerifyState();
    sprite->Update(dt);
}
void Alien_2::Render()
{
    sprite->Render();
    // std::cout << "sprite->GetCurrentFrame():" << sprite->GetCurrentFrame() << std::endl;
}
bool Alien_2::Is(std::string type)
{
    return (type == "Alien_2");
}

void Alien_2::VerifyState()
{
    switch (Player::player->GetCharacterState())
    {
        case WALKING:
        {
            // std::cout << "WALKING" << std::endl;
            sprite->RunSpecificAnimation();
            sprite->SetStartFrame(PLAYER_LVL2_SWIM_START);
            sprite->SetEndFrame(PLAYER_LVL2_SWIM_END);
            sprite->SetAnimationTime(PLAYER_LVL2_SWIM_TIME);
            break;
        }

        case IDLE:
        {
            // std::cout << "DEFAULT" << std::endl;
            sprite->RunSpecificAnimation();
            sprite->SetStartFrame(PLAYER_LVL2_IDLE_START);
            sprite->SetEndFrame(PLAYER_LVL2_IDLE_END);
            sprite->SetAnimationTime(PLAYER_LVL2_IDLE_TIME);
            break;
        }
        default:
        {
            break;
        }
    }
}

void Alien_2::UpdateAssocBox()
{
    Collider* colliderPtr = (Collider*)associated.GetComponent("Collider").get();
    colliderPtr->box.w = sprite->GetWidth()*0.7;
    colliderPtr->box.h = sprite->GetHeight()*0.5;
}
void Alien_2::Attack()
{
    
}