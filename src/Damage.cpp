#include "../include/Damage.h"
#include "../include/Character.h"

Damage::Damage(GameObject &associated, int damage, float destrTime, char_type shooter) : Component::Component(associated),
                                                                                         destrTime(destrTime)
{
    this->damage = damage;
    this->shooter = shooter;
}
void Damage::Update(float dt)
{
    autodestruction.Update(dt);
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
    // Collider* associatedCollider = (Collider *)associated.GetComponent("Collider").get();
    Character* otherCharacter = (Character *)other.GetComponent("Character").get();

    if (other.GetComponent("Player").get() && otherCharacter->Type() != shooter)
    {
        // associated.RequestDelete();
        if (associated.box.GetCenter().x > other.box.GetCenter().x)
        {
            other.box.x -= SPACE_PUSHED /* * (1 + (int)otherCharacter->Type()) */ ;
        }
        else
        {
            other.box.x += SPACE_PUSHED;
        }
    }
    
}

char_type Damage::Shooter()
{
    return shooter;

}