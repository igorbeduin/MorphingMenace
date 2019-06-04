#include "../include/Character.h"
#include "../include/Environment.h"

Character::Character(GameObject &associated, float mass, char_type charType) : Component::Component(associated),
                                                                               mass(mass),
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

void Character::SetMass(float mass)
{
    this->mass = mass;
}

float Character::GetMass()
{
    return mass;
}

void Character::Accelerate(Vec2 acceleration)
{
    speed += acceleration;
}

void Character::Update(float dt)
{
    Environment::ApplyForces(this);
    
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