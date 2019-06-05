#include "../include/Character.h"
#include "../include/Environment.h"
#include "../include/InputManager.h"

Character::Character(GameObject &associated, float mass, char_type charType) : Component::Component(associated),
                                                                               charType(charType),
                                                                               speed(Vec2(0, 0))
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
    if (InputManager::GetInstance().KeyPress(SPACE_KEY))
    {
        Jump();
    }
    if (InputManager::GetInstance().IsKeyDown(D_KEY))
    {
        Walk(PLAYER_LVL0_STEP, dt);
    }
    if (InputManager::GetInstance().IsKeyDown(A_KEY))
    {
        Walk((-1) * PLAYER_LVL0_STEP, dt);
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