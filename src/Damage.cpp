#include "../include/Damage.h"
#include "../include/Character.h"

Damage::Damage(GameObject &associated, int damage, float destrTime, char_type shooter) : Component::Component(associated),
                                                                                         damage(damage),
                                                                                         destrTime(destrTime),
                                                                                         shooter(shooter)
{
    std::cout << "damage shooter  " << shooter << std::endl;
}
void Damage::Update(float dt)
{
    autodestruction.Update(dt);
    // std::cout << dt << std::endl;
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
    // Character* associatedCharacter = (Character *)associated.GetComponent("Character").get();
    // Character* otherCharacter = (Character *)other.GetComponent("Character").get();
    // if ((other.GetComponent("Character").get() != nullptr) && (other.GetComponent("Player").get() == nullptr))
    // {
    // //     // std::cout << " asdasda" << otherCharacter->ISEnemy << ", " << associatedCharacter->ISEnemy << std::endl;
    //     associated.RequestDelete();
    // }
}

char_type Damage::Shooter()
{
    return shooter;
}