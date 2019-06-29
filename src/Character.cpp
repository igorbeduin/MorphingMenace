#include "../include/Character.h"
#include "../include/Environment.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"

Character* Character::player = nullptr;
Character::Character(GameObject &associated, int maxHP, char_type charType) : Component::Component(associated),
                                                                           maxHP(maxHP),
                                                                           applyNormal(false),
                                                                           flip(false),
                                                                           currentHP(maxHP)
{
    switch (charType)
    {
    case PLAYER:
    {
        std::shared_ptr<Player> playerBehav(new Player(associated));
        associated.AddComponent(playerBehav);
        player = this;
        this->box = associated.box;
        break;
    }
    case ENTOKRATON_1:
    {
        std::shared_ptr<Entokraton_1> enemyBehav(new Entokraton_1(associated));
        associated.AddComponent(enemyBehav);
        break;
    }
    case BOSS:
    {
        // PROVISORIO:
        std::shared_ptr<Sprite> charSprite(new Sprite(associated, BOSS_SPRITE_PATH, BOSS_SPRITES_NUMB, BOSS_SPRITES_TIME));
        charSprite->SetScale(BOSS_SCALE, BOSS_SCALE);
        associated.AddComponent(charSprite);
        // TODO:: Cria um personagem do tipo enemy
        break;
    }

    default:
        std::cout << "Character >> WARNING: Character type not specified. Make sure to specify it. " << std::endl;
        break;
    }
}

void Character::Update(float dt)
{
    if (currentHP <= 0)
    {
        associated.RequestDelete();
    }

    Environment::ApplyForces(this);
    
    lastPosition.x = associated.box.x;
    lastPosition.y = associated.box.y;

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
}

void Character::Accelerate(Vec2 acceleration)
{
    speed += acceleration;
    limitSpeeds();
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
    if (other.GetComponent("CollisionBox").get() != nullptr)
    {
        Collider *otherCollider = (Collider *)other.GetComponent("Collider").get();
        Collider *associatedCollider = (Collider *)associated.GetComponent("Collider").get();

        //TODO: colocar esse metodo em uma classe/arquivo de utilities
        collisionSide(associatedCollider->box, otherCollider->box);
        // Falling collision (Up-To-Down Collision)
        if (verticalCollision == collision_side::UP)
        {
            if (!applyNormal)
            {
                associated.box.y -= (associatedCollider->box.y + associatedCollider->box.h) - otherCollider->box.y;
                speed.y = 0;
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
        }

        // Right-To-Left Collision
        if (horizontalCollision == collision_side::RIGHT)
        {
            associated.box.x += (otherCollider->box.x + otherCollider->box.w) - associatedCollider->box.x;
        }
        
        verticalCollision = collision_side::NONE_SIDE;
        horizontalCollision = collision_side::NONE_SIDE;
    }

    if (other.GetComponent("Damage").get() != nullptr)
    {
        Damage *damagePtr = (Damage *)other.GetComponent("Damage").get();
        ApplyDamage(damagePtr->GetDamage());
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
    if ((boxA.x + boxA.w > boxB.x - SAFETY_COLLISION_RANGE) &&
        (boxA.x + boxA.w < boxB.x + DEPTH_COLLISION_RANGE) && 
        (boxA.y + boxA.h != boxB.y))
    {
        horizontalCollision = collision_side::LEFT;
    }
    else
    {
        if ((boxA.x > boxB.x + boxB.w - DEPTH_COLLISION_RANGE) &&
            (boxA.x < boxB.x + boxB.w + SAFETY_COLLISION_RANGE) &&
            (boxA.y + boxA.h != boxB.y))
        {
            horizontalCollision = collision_side::RIGHT;
        }
    }

    // Vertical verification
    if ((boxA.y + boxA.h > boxB.y - SAFETY_COLLISION_RANGE) &&
        (boxA.y + boxA.h < boxB.y + DEPTH_COLLISION_RANGE) &&
        (boxA.x + boxA.w > boxB.x + COLLISION_COMPENSATION) &&
        (boxA.x < boxB.x + boxB.w - COLLISION_COMPENSATION))
    {
        verticalCollision = collision_side::UP;
    }
    else
    {
        if ((boxA.y > boxB.y + boxB.h - DEPTH_COLLISION_RANGE) &&
            (boxA.y < boxB.y + boxB.h + SAFETY_COLLISION_RANGE) &&
            (boxA.x + boxA.w > boxB.x + COLLISION_COMPENSATION) &&
            (boxA.x < boxB.x + boxB.w - COLLISION_COMPENSATION))
        {
            verticalCollision = collision_side::DOWN;
        }   
    }
    
}

Vec2 Character::GetPosition()
{
    return associated.box.GetVec2();
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
}