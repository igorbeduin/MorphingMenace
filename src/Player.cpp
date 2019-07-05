#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"

Player *Player::player = nullptr;

Player::Player(GameObject &associated) : Component::Component(associated),
                                         lvl(0),
                                         currentInfluence(INITIAL_INFLUENCE),
                                         maxInfluence(INITIAL_INFLUENCE),
                                         walkStep(PLAYER_LVL0_STEP),
                                         jumpVelocity(PLAYER_LVL1_JUMP)
{
    std::shared_ptr<Alien_0> alien_0(new Alien_0(associated));
    transformStack.push(alien_0);
    player = this;
}

void Player::Update(float dt)
{   
    UpdateVariables(dt);
    VerifiesInfluence();
    Transformation *currentTransf = (Transformation *)transformStack.top().get();
    currentTransf->Update(deltaTime);
    Joystick();
    EnteringState();
    ExitingState();
    FollowingCamera();

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

void Player::Walk(int step)
{
    associated.box.x += step * deltaTime;
    if (characterState == IDLE)
    {
        characterState = character_state::WALKING;
    }
}

void Player::Jump()
{
    characterPtr->SetSpeedY(jumpVelocity);
    characterState = character_state::JUMPING;
}

void Player::Idle()
{
    characterState = character_state::IDLE;
}

void Player::Attack()
{
    Transformation *currentTransf = (Transformation *)transformStack.top().get();
    characterState = ATTACKING;
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
    transformStack.pop();
    Alien_0 *currentTransf = (Alien_0 *)transformStack.top().get();
    currentTransf->UpdateAssocBox();
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
            if (enemyCharPtr->IsAbsorbable())
            {
                Transform(enemyCharPtr->Type());
                associated.box.x = other.box.x;
                associated.box.y = other.box.y;
                enemyCharPtr->Die();
            }
        }
    }
    if (characterState == character_state::JUMPING || characterState == character_state::FALLING)
    {
        if ((other.GetComponent("CollisionBox").get() != nullptr))
        {
            if (((associated.box.y + associated.box.h > other.box.y - SAFETY_COLLISION_RANGE) &&
                 (associated.box.y + associated.box.h < other.box.y + DEPTH_COLLISION_RANGE) &&
                 (associated.box.x + associated.box.w > other.box.x + COLLISION_COMPENSATION) &&
                 (associated.box.x < other.box.x + other.box.w - COLLISION_COMPENSATION))
                ||
                ((associated.box.y > other.box.y + other.box.h - DEPTH_COLLISION_RANGE) &&
                 (associated.box.y < other.box.y + other.box.h + SAFETY_COLLISION_RANGE) &&
                 (associated.box.x + associated.box.w > other.box.x + COLLISION_COMPENSATION) &&
                 (associated.box.x < other.box.x + other.box.w - COLLISION_COMPENSATION)))

            {
                Idle();
            }
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
        alien_1->UpdateAssocBox();
        transformStack.push(alien_1);
        walkStep = PLAYER_LVL1_STEP;
        jumpVelocity = PLAYER_LVL1_JUMP;
        LvlUp();
        break;
    }

    default:
        break;
    }
}

void Player::EnteringState()
{
    if (characterPtr->GetSpeed().y >= FALLING_SPEED && characterState != JUMPING)
    {
        characterState = character_state::FALLING;
    }

    if (characterPtr->VerifyOcean())
    {
        if (characterPtr->GetSpeed().y > MAXIMUM_Y_SPEED_WATER)
        {
            characterPtr->SetSpeedY(MAXIMUM_Y_SPEED_WATER);
        }
    }
}

void Player::ExitingState()
{
    if (characterState == WALKING)
    {
        if (InputManager::GetInstance().KeyRelease(A_KEY) || InputManager::GetInstance().KeyRelease(D_KEY))
        {
            Idle();
        }
    }
}

int Player::GetCurrentInfluence()
{
    return currentInfluence;
}

void Player::SetInfluence(int influence)
{
    currentInfluence = influence;
}

int Player::GetMaxInfluence()
{
    return maxInfluence;
}

void Player::Swim()
{
    characterPtr->SetSpeedY(SWIM_Y_SPEED);
}

void Player::VerifiesInfluence()
{
    if (currentInfluence <= 0 && lvl != 0)
    {
        currentInfluence = 0;
        LvlDown();
    }
}

void Player::Joystick()
{
    sharedChar = associated.GetComponent("Character");
    if (sharedChar != nullptr)
    {
        characterPtr = (Character *)sharedChar.get();
        // It's only possible to do stuff if player is not ABSORBING
        // Joystick
        if (InputManager::GetInstance().KeyPress(SPACE_KEY) && characterState != JUMPING)
        {
            if (characterPtr->VerifyOcean())
            {
                Swim();
            }
            else
            {
                Jump();
            }
        }
        if (InputManager::GetInstance().IsKeyDown(D_KEY))
        {
            Walk(walkStep);
            if (characterPtr->IsFlipped())
            {
                characterPtr->DisableFlip();
            }
        }
        if (InputManager::GetInstance().IsKeyDown(A_KEY))
        {
            Walk((-1) * walkStep);
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
            if (currentInfluence > 0)
            {
                Absorb();
            }
        }
        if (InputManager::GetInstance().KeyPress(T_KEY))
        {
            #ifdef DEBUG
            characterPtr->ApplyDamage(50);
            #endif
        }
    }
}

void Player::FollowingCamera()
{
    if ((associated.box.x <= (-Camera::pos.x + LEFT_FOCUS_LIMIT) && characterPtr->GetLastPosition().x > associated.box.x) ||
        (associated.box.x + associated.box.w >= (-Camera::pos.x + RIGHT_FOCUS_LIMIT) && characterPtr->GetLastPosition().x < associated.box.x) ||
        (associated.box.y <= (-Camera::pos.y + UP_FOCUS_LIMIT) && characterPtr->GetLastPosition().y > associated.box.y) ||
        (associated.box.y + associated.box.h >= (-Camera::pos.y + DOWN_FOCUS_LIMIT) && characterPtr->GetLastPosition().y < associated.box.y))
    {
        Camera::Follow(&associated);
    }
    else
    {
        Camera::Unfollow();
    }
}

void Player::UpdateVariables(float dt)
{
    deltaTime = dt;
}