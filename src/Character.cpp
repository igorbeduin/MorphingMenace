#include "../include/Character.h"
#include "../include/Environment.h"
#include "../include/InputManager.h"
#include "../include/Collider.h"

Character::Character(GameObject &associated, float mass, char_type charType) : Component::Component(associated),
                                                                               charType(charType),
                                                                               speed(Vec2(0, 0)),
                                                                               flip(false),
                                                                               applyNormal(false),
                                                                               verticalCollision(collision_side::NONE_SIDE),
                                                                               horizontalCollision(collision_side::NONE_SIDE),
                                                                               characterState(character_state::NONE_STATE),
                                                                               lastPosition(Vec2(0, 0))
{
    switch (charType)
    {
    case PLAYER:
    {
        // PROVISORIO:
        std::shared_ptr<Sprite> charSprite(new Sprite(associated, PLAYER_LVL0_SPRITE_PATH, PLAYER_LVL0_SPRITES_NUMB, PLAYER_LVL0_SPRITES_TIME));
        charSprite->SetScale(PLAYER_LVL0_SCALE, PLAYER_LVL0_SCALE);
        associated.AddComponent(charSprite);
        // TODO:: Cria um personagem do tipo enemy
        break;
    }
    case ENEMY:
    {
        // PROVISORIO:
        std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENEMY_1_SPRITE_PATH, ENEMY_1_SPRITES_NUMB, ENEMY_1_SPRITES_TIME));
        charSprite->SetScale(ENEMY_1_SCALE, ENEMY_1_SCALE);
        associated.AddComponent(charSprite);

        // TODO:: Cria um personagem do tipo enemy
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

void Character::SetSpeed(Vec2 speed)
{
    this->speed = speed;
}

Vec2 Character::GetSpeed()
{
    return speed;
}

void Character::Accelerate(Vec2 acceleration)
{
    speed += acceleration;
    limitSpeeds();
}

void Character::Update(float dt)
{
    Environment::ApplyForces(this);


    // Joystick
    if (charType == PLAYER)
    {
        if ((associated.box.x == lastPosition.x) && (associated.box.y == lastPosition.y))
        {
            if (characterState != character_state::IDLE)
            {
                Idle();
            }
        }

        if (InputManager::GetInstance().KeyPress(SPACE_KEY))
        {
            Jump();
        }
        if (InputManager::GetInstance().IsKeyDown(D_KEY))
        {
            Walk(PLAYER_LVL0_STEP, dt);
            if (flip)
            {
                flip = false;
            }
        }
        if (InputManager::GetInstance().IsKeyDown(A_KEY))
        {
            Walk((-1) * PLAYER_LVL0_STEP, dt);
            if (!flip)
            {
                flip = true;
            }
        }
    }

    lastPosition.x = associated.box.x;
    lastPosition.y = associated.box.y;

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
    if (charType == char_type::PLAYER)
    {
        switch (characterState)
        {
            case character_state::WALKING:
                std::cout << "Walking" << std::endl;
                break;
            case character_state::JUMPING:
                std::cout << "Jumping" << std::endl;
                break;
            case character_state::FALLING:
                std::cout << "Falling" << std::endl;
                break;
            case character_state::IDLE:
                std::cout << "Idle" << std::endl;
                break;    
            case character_state::NONE_STATE:
                std::cout << "None" << std::endl;
                break;
        }
    }
}

bool Character::Is(std::string type)
{
    switch (charType)
    {
    case PLAYER:
    {
        return (type == "Player" || type == "Character");
        break;
    }
    case ENEMY:
    {
        return (type == "Enemy" || type == "Character");
        break;
    }
    case BOSS:
    {
        return (type == "Boss" || type == "Character");
        break;
    }
    }
}

void Character::Render()
{
}

void Character::Walk(int step, float dt)
{
    associated.box.x += step * dt;
    if (characterState == character_state::IDLE)
    {
        characterState = character_state::WALKING;
    }
}

void Character::Jump()
{
    speed.y = PLAYER_LVL0_JUMP;
    characterState = character_state::JUMPING;
}

void Character::Idle()
{
    characterState = character_state::IDLE;
}

bool Character::IsFlipped()
{
    return flip;
}

void Character::NotifyCollision(GameObject &other)
{

    Collider *otherCollider = (Collider *)other.GetComponent("Collider").get();
    Collider *associatedCollider = (Collider *)associated.GetComponent("Collider").get();

    //TODO: colocar esse metodo em uma classe/arquivo de utilities
    collisionSide(associatedCollider->box, otherCollider->box);

    if (other.GetComponent("CollisionBox").get() != nullptr)
    {
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
        
    }
    verticalCollision = collision_side::NONE_SIDE;
    horizontalCollision = collision_side::NONE_SIDE;
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
        (boxA.x + boxA.w > boxB.x + DEPTH_COLLISION_RANGE) &&
        (boxA.x < boxB.x + boxB.w - DEPTH_COLLISION_RANGE))
    {
        verticalCollision = collision_side::UP;
    }
    else
    {
        if ((boxA.y > boxB.y + boxB.h - DEPTH_COLLISION_RANGE) &&
            (boxA.y < boxB.y + boxB.h + SAFETY_COLLISION_RANGE) &&
            (boxA.x + boxA.w > boxB.x + DEPTH_COLLISION_RANGE) &&
            (boxA.x < boxB.x + boxB.w - DEPTH_COLLISION_RANGE))
        {
            verticalCollision = collision_side::DOWN;
        }   
    }
    
}
