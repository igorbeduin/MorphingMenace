#include "../include/Damage.h"
#include "../include/Character.h"

Damage::Damage(GameObject &associated, int damage, float destrTime, char_type shooter) : Component::Component(associated),
                                                                                         destrTime(destrTime)
{
    std::cout << "damage tipo " << shooter << std::endl;
    this->damage = damage;
    this->shooter = shooter;
}
void Damage::Update(float dt)
{
    autodestruction.Update(dt);
    std::cout << "shooter: " << shooter << " damage: " << damage << std::endl;
    if (autodestruction.Get() >= destrTime)
    {
        associated.RequestDelete();
    }

}
void Damage::Render()
{}
bool Damage::Is(std::string type)
{
    return (type == "Damage");
}

int Damage::GetDamage()
{
    return damage;
}

void Damage::NotifyCollision(GameObject &other)
{
    Character* associatedCharacter = (Character *)associated.GetComponent("Character").get();
    Character* otherCharacter = (Character *)other.GetComponent("Character").get();

    if (otherCharacter->Type() != shooter)
    {
        associated.RequestDelete();
        std::cout << shooter << std::endl;
    }
}

char_type Damage::Shooter()
{
    std::cout << "retornando damage tipo " << shooter << std::endl;
    return shooter;

}