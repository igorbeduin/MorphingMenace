#include "../include/Player.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include "../include/GameData.h"
#include "../include/Boss.h"

Player *Player::player = nullptr;
Player::Player(GameObject &associated) : Component::Component(associated),
                                         lvl(0),
                                         currentInfluence(INITIAL_INFLUENCE),
                                         maxInfluence(INITIAL_INFLUENCE),
                                         walkStep(PLAYER_LVL0_STEP),
                                         jumpVelocity(PLAYER_LVL0_JUMP),
                                         currentForm(BABY),
                                         applyWaterDamage(true)
{
    std::shared_ptr<Alien_0> alien_0(new Alien_0(associated));
    transformStack.push(alien_0);
    player = this;
    std::shared_ptr<WaterDamage> waterDmgComponent(new WaterDamage(associated));
    associated.AddComponent(waterDmgComponent);
}

void Player::Update(float dt)
{   
    // Character *enemyCharPtr = (Character *)associated.GetComponent("Character").get();
    FlipPlayer();
    // std::cout << "Transformação: " << currentForm << std::endl;
    // std::cout << "Gravidade: " << enemyCharPtr->applyGravity << " Water: " << enemyCharPtr->applyWaterThrust << std::endl;
    IsDamaged();
    UpdateVariables(dt);
    VerifiesInfluence();
    Transformation *currentTransf = (Transformation *)transformStack.top().get();
    currentTransf->Update(deltaTime);
    if (characterState != ABSORBING && hatching == false)
    {
        Joystick();
    }
    EnteringState();
    ExitingState();
    FollowingCamera();
    if (HatchTime.Get() < TRANSFORMATION_NUMB*TRANSFORMATION_TIME)
        HatchTime.Update(dt);
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
    if (HatchTime.Get() >= TRANSFORMATION_TIME*(TRANSFORMATION_NUMB-1) - 0.1)
    {
        Transformation *currentTransf = (Transformation *)transformStack.top().get();
        currentTransf->Render();
        hatching = false;
    }
    
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
    if (lvl != 0)
    {
        characterState = ATTACKING;
        currentTransf->Attack();
    }
}
void Player::IsDamaged()
{
    Character *CharPtr = (Character *)associated.GetComponent("Character").get();
    if (CharPtr->GetLastHP() > CharPtr->GetCurrentHP())
    {   
        CharPtr->SetLastHP(CharPtr->GetCurrentHP());
        // std::cout << "ai fdp isso dói" << std::endl;
        characterState = DAMAGED;
  
    }
    

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

void Player::LvlUp(Transformations next_form)
{
    currentForm = next_form;
    lvl += 1;
}

void Player::LvlDown()
{
    transformStack.pop();
    Alien_0 *currentTransf = (Alien_0 *)transformStack.top().get();
    currentTransf->UpdateAssocBox();
    lvl -= 1;

    currentForm = BABY;
    Character *enemyCharPtr = (Character *)associated.GetComponent("Character").get();
    enemyCharPtr->applyGravity = true;
    if (applyWaterDamage != true)
    {
        applyWaterDamage = true;
    }
}

void Player::NotifyCollision(GameObject &other)
{
    if (characterState == character_state::ABSORBING)
    {
        if ((other.GetComponent("CollisionBox").get() != nullptr) || (other.GetComponent("Character").get() != nullptr))
        {
            Character *characterPtr = (Character *)associated.GetComponent("Character").get();
            Idle();
        }
        Character *enemyCharPtr = (Character *)other.GetComponent("Character").get();
        if (enemyCharPtr != nullptr)
        {
            if (enemyCharPtr->IsAbsorbable())
            {
                Transform(enemyCharPtr->Type(), {other.box.x, other.box.y});
                if (enemyCharPtr->Type() != char_type::BOSS)
                {
                    associated.box.x = other.box.x;
                    associated.box.y = other.box.y;
                }
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

void Player::Transform(char_type type, Vec2 enemy_position)
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
        LvlUp(Transformations::ENTOKRATON_1);
        break;
    }
    case ENTOKRATON_2:
    {  
        std::shared_ptr<Alien_2> alien_2(new Alien_2(associated));
        alien_2->UpdateAssocBox();
        transformStack.push(alien_2);
        walkStep = PLAYER_LVL2_STEP;
        jumpVelocity = PLAYER_LVL2_JUMP;
        LvlUp(Transformations::ENTOKRATON_2);
        applyWaterDamage = false;

        break;
    }
    case BOSS:
    {
        if (Boss::defeated)
        {
            // std::cout << "pode fazer a tela de vitória" << std::endl;
            GameData::playerVictory = true;
        }
        
        break;
    }

    default:
        break;
    }

                    // std::cout << "absorveu" << std::endl;
                Character *playerCharPtr = (Character *)associated.GetComponent("Character").get();
                playerCharPtr->SetSpeed(0,0);

                GameObject *transf_object = new GameObject();
                std::weak_ptr<GameObject> weak_transf =  Game::GetInstance().GetCurrentState().AddObject(transf_object);//
                std::shared_ptr<GameObject> transf = weak_transf.lock();

                std::shared_ptr<Sprite> transf_sprite(new Sprite(*transf, TRANSFORMATION_PATH, TRANSFORMATION_NUMB, TRANSFORMATION_TIME, TRANSFORMATION_NUMB*TRANSFORMATION_TIME));
                // std::shared_ptr<Sound> transf_sound(new Sound(*transf, PENGUIN_DEATH_SOUND));

                transf->box.x  = enemy_position.x;
                transf->box.y  = enemy_position.y;
                transf_sprite->SetScale(TRANSFORMATION_SCALE, TRANSFORMATION_SCALE);

                if (playerCharPtr->IsFlipped())
                {
                    transf_sprite->SetFlipH();    
                }
                else
                {
                    transf_sprite->UnSetFlipH();
                }
                hatching = true;
                HatchTime.Restart();                
                transf->AddComponent(transf_sprite);
                // transf->AddComponent(transf_sound);
                // transf_sound->Play(1);

}

void Player::EnteringState()
{
    if (characterPtr->GetSpeed().y >= FALLING_SPEED /*&& !characterPtr->VerifyOcean() && characterState != JUMPING*/)
    {
        characterState = character_state::FALLING;
    }

    if (characterPtr->VerifyOcean())
    {
        if (characterPtr->GetSpeed().y > MAXIMUM_Y_SPEED_WATER)
        {
            characterPtr->SetSpeedY(MAXIMUM_Y_SPEED_WATER);
        }
        if (characterPtr->GetSpeed().y < -MAXIMUM_Y_SPEED_WATER)
        {
            characterPtr->SetSpeedY(-MAXIMUM_Y_SPEED_WATER);
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

void Player::Swim(int swimStep)
{
    if (swimStep != 0)
    {
        associated.box.y += swimStep * deltaTime;
        if (characterState == IDLE)
        {
            characterState = character_state::WALKING;
        }
    } else
    {
        characterPtr->SetSpeedY(SWIM_Y_SPEED);
    }    
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
        if (InputManager::GetInstance().KeyPress(SPACE_KEY) && (characterState == IDLE || characterState == WALKING) && currentForm != Transformations::ENTOKRATON_2)
        {
            if (characterPtr->VerifyOcean())
            {
                Swim(0);
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
        if (InputManager::GetInstance().IsKeyDown(W_KEY) && currentForm == Transformations::ENTOKRATON_2)
        {
            if (characterPtr->VerifyOcean())
            {
                Swim((-1)*walkStep);
            }            
        }
        if (InputManager::GetInstance().IsKeyDown(S_KEY) && currentForm == Transformations::ENTOKRATON_2)
        {
            if (characterPtr->VerifyOcean())
            {
                Swim(walkStep);
            }
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
void Player::FlipPlayer()
{
    Character *playerCharPtr = (Character *)associated.GetComponent("Character").get();

    // std::cout << playerCharPtr->IsFlipped() << std::endl;
    if (playerCharPtr->IsFlipped())
    {
        playerCharPtr->EnableFlip();
    }
    else
    {
        playerCharPtr->DisableFlip();
    }
    
    


}