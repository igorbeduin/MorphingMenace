#include "../include/Force.h"
#include "../include/Character.h"

float Force::deltaTime;

Force::Force(Vec2 acceleration) : acceleration(acceleration)
{}

Force::~Force()
{}

void Force::Update(float dt)
{
    deltaTime = dt;
}
void Force::Apply(Character* character)
{
    character->Accelerate(acceleration /* * deltaTime*/);
}

void Force::SetAcceleration(Vec2 acceleration)
{
    this->acceleration = acceleration;
}
Vec2 Force::GetAcceleration()
{
    return acceleration;
}
