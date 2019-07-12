#include "../include/Alien_1.h"
#include "../include/Game.h"
#include "../include/Character.h"
#include "../include/Player.h"

Alien_1::Alien_1(GameObject &associated) : Component::Component(associated),
                                           sprite(new Sprite(associated, PLAYER_LVL1_SPRITE_PATH, PLAYER_LVL1_SPRITES_NUMB, PLAYER_LVL1_SPRITES_TIME))
{

    sprite->SetScale(PLAYER_LVL1_SCALE, PLAYER_LVL1_SCALE);
    std::shared_ptr<Sound> sound(new Sound(associated));
    associated.AddComponent(sound);
    
}
void Alien_1::Update(float dt)
{   
    if (Player::player != nullptr)
    {
    /* code */

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

        if (sprite->GetCurrentFrame() == 3 && Player::player->GetCharacterState() == WALKING)
        {
            if(firstTime1 == false)
            {
                Play(LVL1_WALK1_SOUND);
                firstTime1 = true;
                firstTime2 = false;
            }
        }
        if (sprite->GetCurrentFrame() == 5 && Player::player->GetCharacterState() == WALKING)
        {
            if (firstTime2 == false)
            {
                Play(LVL1_WALK1_SOUND);
                firstTime2 = true;
                firstTime1 = false;
            }
        }
        if (sprite->GetCurrentFrame() == 6 && Player::player->GetCharacterState() == ATTACKING)
        {
            if(firstTime1 == false)
            {
                Play(LVL1_ATTACK1_SOUND);
                firstTime1 = true;
                firstTime2 = false;
            }
        }
        if (sprite->GetCurrentFrame() == 8 && Player::player->GetCharacterState() == ATTACKING)
        {
            if (firstTime2 == false)
            {
                Play(LVL1_ATTACK1_SOUND);
                firstTime2 = true;
                firstTime1 = false;
            }
        }
        if (sprite->GetCurrentFrame() == 11)
        {
            Play(LVL1_DAMAGE_SOUND);
        }

    }
}
void Alien_1::Render()
{
    sprite->Render();
    // std::cout << "sprite->GetCurrentFrame():" << sprite->GetCurrentFrame() << std::endl;
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
    case FALLING:
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

    case DAMAGED:
        {
            sprite->RunSpecificAnimation();
            sprite->SetStartFrame(PLAYER_LVL1_DAMAGED_START);
            sprite->SetEndFrame(PLAYER_LVL1_DAMAGED_END);
            sprite->SetAnimationTime(PLAYER_LVL1_DAMAGED_TIME);

            if (sprite->GetCurrentFrame() == PLAYER_LVL1_DAMAGED_END)
            {
                Player::player->SetCharacterState(character_state::IDLE);
            }

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
    colliderPtr->box.w = sprite->GetWidth()*0.7;
    colliderPtr->box.h = sprite->GetHeight();
}
void Alien_1::Play(std::string file)
{
    Sound* SoundEffect = (Sound *)associated.GetComponent("Sound").get();
    SoundEffect->Open(file);
    SoundEffect->Play();
}