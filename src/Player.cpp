#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

Player::Player(GameObject &associated) : Component::Component(associated)
{
    std::shared_ptr<Alien_0> alien_0(new Alien_0(associated));
    transformStack.push(alien_0);
}

void Player::Update(float dt)
{
    Alien_0 *currentTransf = (Alien_0 *)transformStack.top().get();
    currentTransf->Update(dt);

    sharedChar = associated.GetComponent("Character");
    if (sharedChar != nullptr)
    {
        characterPtr = (Character *)sharedChar.get();
        // It's only possible to do stuff if player is not ABSORBING
        if (characterState != character_state::ABSORBING)
        {
            if ((associated.box.x == characterPtr->GetLastPosition().x) && (associated.box.y == characterPtr->GetLastPosition().y) && characterPtr->GetSpeed().y == 0)
            {
                if (characterState != character_state::IDLE)
                {
                    Idle();
                }
            }
            // Joystick
            if (InputManager::GetInstance().KeyPress(SPACE_KEY))
            {
                if ((characterState != character_state::JUMPING) && (characterPtr->GetSpeed().y == 0))
                {
                    Jump();
                }
            }
            if (InputManager::GetInstance().IsKeyDown(D_KEY))
            {
                Walk(PLAYER_LVL0_STEP, dt);
                if (characterPtr->IsFlipped())
                {
                    characterPtr->DisableFlip();
                }
            }
            if (InputManager::GetInstance().IsKeyDown(A_KEY))
            {
                Walk((-1) * PLAYER_LVL0_STEP, dt);
                if (!characterPtr->IsFlipped())
                {
                    characterPtr->EnableFlip();
                }
            }

            if (InputManager::GetInstance().KeyPress(O_KEY))
            {
                Attack();
            }
            if (InputManager::GetInstance().KeyPress(P_KEY))
            {
                Absorb();
            }

            if ((associated.box.x <= (-Camera::pos.x + LEFT_FOCUS_LIMIT) && characterPtr->GetLastPosition().x > associated.box.x) ||
                (associated.box.x + associated.box.w >= (-Camera::pos.x + RIGHT_FOCUS_LIMIT) && characterPtr->GetLastPosition().x < associated.box.x))
            {
                Camera::Follow(&associated);
            }
            else
            {
                Camera::Unfollow();
            }
        }
    }
}

void Player::SetCharacterState(character_state state)
{
    characterState = state;
}

character_state Player::GetCharacterState()
{
    return characterState;
}

void Player::Render()
{
    Alien_0 *currentTransf = (Alien_0 *)transformStack.top().get();
    currentTransf->Render();
}

bool Player::Is(std::string type)
{
    return (type == "Player");
}

void Player::Walk(int step, float dt)
{
    associated.box.x += step * dt;
    if (characterState == character_state::IDLE)
    {
        characterState = character_state::WALKING;
    }
}

void Player::Jump()
{
    characterPtr->SetSpeedY(PLAYER_LVL0_JUMP);
    characterState = character_state::JUMPING;
}

void Player::Idle()
{
    characterState = character_state::IDLE;
}

void Player::Attack()
{
    Transformation *currentTransf = (Transformation *)transformStack.top().get();
    currentTransf->Attack();
}

void Player::Absorb()
{
    Transformation *currentTransf = (Transformation *)transformStack.top().get();
    currentTransf->Absorb();
}

int Player::GetLvl()
{
    return lvl;
}

void Player::LvlUp()
{
    lvl += 1;
}

void Player::LvlDown()
{
    lvl -= 1;
}

void Player::NotifyCollision(GameObject &other)
{
    if (characterState == character_state::ABSORBING)
    {
        if ((other.GetComponent("CollisionBox").get() != nullptr) || (other.GetComponent("Character").get() != nullptr))
        {
            characterState = character_state::IDLE;
            Character *characterPtr = (Character *)associated.GetComponent("Character").get();
            characterPtr->SetSpeed(Vec2(0, 0));
        }
        Character *enemyCharPtr = (Character *)other.GetComponent("Character").get();
        if (enemyCharPtr != nullptr)
        {
            Transform(enemyCharPtr->Type());
        }
    }
}

void Player::Transform(char_type type)
{
    switch (type)
    {
        case ENTOKRATON_1:
        {
            std::shared_ptr<Alien_1> alien_1(new Alien_1(associated));
            transformStack.push(alien_1);
            break;

        }
        
        default:
            break;
        }
}