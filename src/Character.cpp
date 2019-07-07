#include "../include/Character.h"
#include "../include/Environment.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/StageState.h"

Character* Character::playerChar = nullptr;
Character::Character(GameObject &associated, int maxHP, char_type charType) : Component::Component(associated),
                                                                              maxHP(maxHP),
                                                                              applyNormal(false),
                                                                              applyWaterThrust(false),
                                                                              flip(false),
                                                                              currentHP(maxHP),
                                                                              charType(charType)
{
    switch (charType)
    {
    case PLAYER:
    {
        std::shared_ptr<Player> playerBehav(new Player(associated));
        associated.AddComponent(playerBehav);
        playerChar = this;
        this->box = associated.box;
        ISEnemy = false;
        break;
    }
    case ENTOKRATON_1:
    {
        std::shared_ptr<Entokraton_1> enemyBehav(new Entokraton_1(associated));
        associated.AddComponent(enemyBehav);
        ISEnemy = true;
        break;
    }
    case BOSS:
    {
        std::shared_ptr<Boss> bossBehav(new Boss(associated));
        associated.AddComponent(bossBehav);
        ISEnemy = true;
        break;
    }
    case BOSS_CORE:
    {
        std::shared_ptr<BossCore> coreBehav(new BossCore(associated));
        associated.AddComponent(coreBehav);
        ISEnemy = true;
        break;
    }

    default:
        std::cout << "Character >> WARNING: Character type not specified. Make sure to specify it. " << std::endl;
        break;
    }
}

void Character::Update(float dt)
{
    VerifyOcean();
    if (charType != char_type::BOSS && charType != char_type::BOSS_CORE)
    {
        Environment::ApplyForces(this);
    }
    
    lastPosition.x = associated.box.x;
    lastPosition.y = associated.box.y;

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    if (currentHP <= 0)
    {
        if (associated.GetComponent("Player").get()) //verificar se player ainda existe
        {
            Camera::Unfollow();
        }
        Die();
    }
    limitSpeeds();
}

void Character::Accelerate(Vec2 acceleration)
{
    speed += acceleration;
}


bool Character::Is(std::string type)
{
    return (type == "Character");
}

void Character::Render()
{
}


void Character::NotifyCollision(GameObject &other)
{   
    // Collision with environment
    if (other.GetComponent("CollisionBox").get() != nullptr)
    {   
        Collider *otherCollider = (Collider *)other.GetComponent("Collider").get();
        Collider *associatedCollider = (Collider *)associated.GetComponent("Collider").get();

        collisionSide(associatedCollider->box, otherCollider->box);
        // Falling collision (Up-To-Down Collision)
        if (verticalCollision == collision_side::UP)
        {
            if (!applyNormal)
            {
                associated.box.y -= (associatedCollider->box.y + associatedCollider->box.h) - otherCollider->box.y;
                speed.y = 0;
                speed.x = 0;
                applyNormal = true;
            }
        }

        // Down-To-Up Collision
        if (verticalCollision == collision_side::DOWN)
        {
            associated.box.y += (otherCollider->box.y + otherCollider->box.h) - associatedCollider->box.y;
            speed.y = 0;
        }

        // Left-To-Right Collision
        if (horizontalCollision == collision_side::LEFT)
        {
            associated.box.x -= (associatedCollider->box.x + associatedCollider->box.w) - otherCollider->box.x;
            speed.x = 0;
        }

        // Right-To-Left Collision
        if (horizontalCollision == collision_side::RIGHT)
        {
            associated.box.x += (otherCollider->box.x + otherCollider->box.w) - associatedCollider->box.x;
            speed.x = 0;
        }
        
        verticalCollision = collision_side::NONE_SIDE;
        horizontalCollision = collision_side::NONE_SIDE;
    }

    // Collision with damages
    if (other.GetComponent("Damage").get() != nullptr)
    {
        if (other.GetComponent("Player").get() != nullptr)
        {
            std::cout << "É player" << std::endl;
        }
        else
        {
            std::cout << "Nao eh player" << std::endl;
            
        }
        
        Damage *damagePtr = (Damage *)other.GetComponent("Damage").get();   
        std::cout << "Character tipo: " << charType << std::endl;
        std::cout << "tipo do damage: " << damagePtr->shooter << std::endl; 
        std::cout << "dano do damage: " << damagePtr->damage << std::endl;
        if (damagePtr->shooter != charType)
        {
           // ApplyDamage(damagePtr->GetDamage());
            // other.RequestDelete();
        }
    }
}

void Character::limitSpeeds()
{
    if (speed.y > MAXIMUM_Y_SPEED)
    {
        speed.y = MAXIMUM_Y_SPEED;
    }
}

void Character::collisionSide(Rect boxA, Rect boxB)
{
    // This function returns the side colliding of B in relation of A, e.g, A->B returns "Left"

    // Horizontal verification
    if ((boxA.x + boxA.w > boxB.x /*- SAFETY_COLLISION_RANGE*/) &&
        (boxA.x + boxA.w <= boxB.x + DEPTH_COLLISION_RANGE) &&
        (boxA.y + boxA.h > boxB.y + DEPTH_COLLISION_RANGE))
    {
        horizontalCollision = collision_side::LEFT;
    }
    else
    {
        if ((boxA.x >= boxB.x + boxB.w - DEPTH_COLLISION_RANGE) &&
            (boxA.x < boxB.x + boxB.w /*+ SAFETY_COLLISION_RANGE*/) &&
            (boxA.y + boxA.h > boxB.y + DEPTH_COLLISION_RANGE))
        {
            horizontalCollision = collision_side::RIGHT;
        }
    }

    // Vertical verification
    if ((boxA.y + boxA.h > boxB.y /*- SAFETY_COLLISION_RANGE*/) &&
        (boxA.y + boxA.h <= boxB.y + DEPTH_COLLISION_RANGE) &&
        (boxA.x + boxA.w > boxB.x + DEPTH_COLLISION_RANGE) &&
        (boxA.x < boxB.x + boxB.w - DEPTH_COLLISION_RANGE))
    {
        verticalCollision = collision_side::UP;
    }
    else
    {
        if ((boxA.y < boxB.y + boxB.h /*- DEPTH_COLLISION_RANGE*/) &&
            (boxA.y >= boxB.y + boxB.h - DEPTH_COLLISION_RANGE) &&
            (boxA.x + boxA.w > boxB.x + DEPTH_COLLISION_RANGE) &&
            (boxA.x < boxB.x + boxB.w - DEPTH_COLLISION_RANGE))
        {
            verticalCollision = collision_side::DOWN;
        }   
    }
    
}

Vec2 Character::GetPosition()
{
    return associated.box.GetCenter();
}

Vec2 Character::GetLastPosition()
{
    return lastPosition;
}

Vec2 Character::GetSpeed()
{
    return speed;
}

void Character::SetSpeedX(int speedX)
{
    speed.x = speedX;
}
void Character::SetSpeedY(int speedY)
{
    speed.y = speedY;
}

void Character::SetSpeed(Vec2 speed)
{
    SetSpeed(speed.x, speed.y);
}

void Character::SetSpeed(int speedX, int speedY)
{
    SetSpeedX(speedX);
    SetSpeedY(speedY);
}

bool Character::IsFlipped()
{
    return flip;
}

void Character::EnableFlip()
{
    flip = true;
}

void Character::DisableFlip()
{
    flip = false;
}

void Character::ApplyDamage(int damage)
{
    currentHP -= damage;
    std::cout << "currentHP:" << currentHP << std::endl;
}

char_type Character::Type()
{
    return charType;
}

int Character::GetCurrentHP()
{
    return currentHP;
}

int Character::GetMaxHP()
{
    return maxHP;
}

bool Character::IsAbsorbable()
{
    if (currentHP <= ABSORBABLE_PERC * maxHP)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Character::Die()
{
    associated.RequestDelete();
    if (charType == char_type::PLAYER)
    {
        playerChar = nullptr;
    }
    // if (charType == char_type::BOSS_CORE)
    // {
    //     // (BossCore *)associated.GetComponent("BossCore").get()->

    // }
}

bool Character::VerifyOcean()
{
    for (int i = 0; i < (int)StageState::oceanArray.size(); i++)
    {
        if (StageState::oceanArray[i].get() != nullptr)
        {
            if (StageState::oceanArray[i]->box.Contains(associated.box.GetCenter().x, associated.box.GetCenter().y))
            {
                applyWaterThrust = true;
                return applyWaterThrust;
            }
        }
    }
    applyWaterThrust = false;
    return false;
}