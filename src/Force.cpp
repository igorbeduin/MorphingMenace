#include "../include/Force.h"
#include "../include/Character.h"

Force::Force(Vec2 acceleration) : acceleration(acceleration)
{}

Force::~Force()
{}

void Force::Apply(Character* character)
{
    character->Accelerate(acceleration);
}

void Force::SetAcceleration(Vec2 acceleration)
{
    this->acceleration = acceleration;
}
Vec2 Force::GetAcceleration()
{
    return acceleration;
}
