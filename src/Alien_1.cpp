#include "../include/Alien_1.h"
#include "../include/Game.h"
#include "../include/Character.h"
#include "../include/Player.h"

Alien_1::Alien_1(GameObject &associated) : Component::Component(associated),
                                           sprite(new Sprite(associated, PLAYER_LVL1_SPRITE_PATH, PLAYER_LVL1_SPRITES_NUMB, PLAYER_LVL1_SPRITES_TIME))
{
    //std::shared_ptr<Sprite> charSprite(new Sprite(associated, PLAYER_LVL1_SPRITE_PATH, PLAYER_LVL1_SPRITES_NUMB, PLAYER_LVL1_SPRITES_TIME));
    //sprite = charSprite;

    sprite->SetScale(PLAYER_LVL1_SCALE, PLAYER_LVL1_SCALE);
}
void Alien_1::Update(float dt)
{
    VerifyState();
    sprite->Update(dt);
}
void Alien_1::Render()
{
    sprite->Render();
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
    attack->box.w = PLAYER_LVL1_ATTACK_WIDTH;
    attack->box.h = PLAYER_LVL1_ATTACK_HEIGHT;
    if (associatedCharacter->IsFlipped())
    {
        attack->box.x = associatedCollider->box.x - attack->box.w;
    }
    else
    {
        attack->box.x = associatedCollider->box.x + associatedCollider->box.w;
    }
    attack->box.y = associatedCollider->box.GetCenter().y + (PLAYER_LVL1_ATTACK_HEIGHT / 2);

    std::shared_ptr<Damage> attackBehaviour(new Damage(*attack, PLAYER_LVL1_ATTACK_DAMAGE, PLAYER_LVL1_ATTACK_TIME, associatedCharacter->Type()));
    attack->AddComponent(attackBehaviour);
    std::shared_ptr<Collider> attackCollider(new Collider(*attack));
    attack->AddComponent(attackCollider);
    Game::GetInstance().GetCurrentState().AddObject(attack);
}

void Alien_1::Absorb()
{
   /*
    if (Player::player != nullptr)
    {
        int directABSORB_X_SPEED;
        if (Player::player->GetLvl() != 1)
        {
            Downgrade();
        }
        Player::player->SetCharacterState(character_state::ABSORBING);
        Character::playerChar->IsFlipped() ? (directABSORB_X_SPEED = ABSORB_Y_SPEED) : (directABSORB_X_SPEED = -ABSORB_Y_SPEED);
        Character::playerChar->SetSpeedX(directABSORB_X_SPEED);
        Character::playerChar->SetSpeedY(ABSORB_Y_SPEED);
    }
    */
}

void Alien_1::VerifyState()
{
    switch (Player::player->GetCharacterState())
    {
    case WALKING:
    {
        std::cout << "WALKING" << std::endl;
        sprite->RunSpecificAnimation();
        sprite->SetStartFrame(PLAYER_LVL1_WALK_START);
        sprite->SetEndFrame(PLAYER_LVL1_WALK_END);
        sprite->SetAnimationTime(PLAYER_LVL1_WALK_TIME);
        break;
    }
    default:
    {
        // std::cout << "DEFAULT" << std::endl;
        sprite->RunSpecificAnimation();
        sprite->SetStartFrame(PLAYER_LVL1_IDLE_START);
        sprite->SetEndFrame(PLAYER_LVL1_IDLE_END);
        sprite->SetAnimationTime(PLAYER_LVL1_IDLE_TIME);
        break;
    }
    }
}