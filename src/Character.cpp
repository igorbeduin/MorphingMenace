#include "../include/Character.h"

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
        std::shared_ptr<Sprite> charSprite(new Sprite(associated, PLAYER_LVL0_SPRITE_PATH, 3));
        charSprite->SetScale(0.1, 0.1);
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

void Character::Move(Vec2 dst)
{
    // TODO: Rotina de movimento da posição atual para a posição de destino
    Sprite* sprite = (Sprite*) associated.GetComponent("Sprite").get();
    sprite->SetFrame(sprite->GetCurrentFrame() + 1);
}

void Character::Update(float dt)
{
}

bool Character::Is(std::string type)
{
    switch (charType)
    {
    case PLAYER:
    {
        return (type == "Player");
        break;
    }
    case ENEMY:
    {
        return (type == "Enemy");
        break;
    }
    }
}