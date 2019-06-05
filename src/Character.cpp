#include "../include/Character.h"
#include "../include/Environment.h"
#include "../include/InputManager.h"

Character::Character(GameObject &associated, float mass, char_type charType) : Component::Component(associated),
                                                                               charType(charType),
                                                                               speed(Vec2(0, 0)),
                                                                               flip(false),
                                                                               applyNormal(false)
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

        associated.moving = false;
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
}

void Character::Update(float dt)
{
    Environment::ApplyForces(this);

    // Joystick
    if (charType == PLAYER)
    {
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
    

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;
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
{}

void Character::Walk(int step, float dt)
{
    associated.box.x += step * dt;
}

void Character::Jump()
{
    speed.y = PLAYER_LVL0_JUMP;
}

bool Character::IsFlipped()
{
    return flip;
}

void Character::NotifyCollision(GameObject &other)
{
    if (other.GetComponent("CollisionBox").get() != nullptr)
    {   
        if (!applyNormal && speed.y >= 0)
        {
            if (((associated.box.y + associated.box.h) < (1 + COLLISION_RANGE) * other.box.y) && 
                ((associated.box.y + associated.box.h) > (1 - COLLISION_RANGE) * other.box.y))
            {   
                associated.box.y = other.box.y - associated.box.h;
                speed.y = 0;
                applyNormal = true;
            }
        }
    }
}
