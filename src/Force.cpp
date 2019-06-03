#include "../include/Force.h"

Force::Force(Vec2 direction, int acceleration) : direction(direction),
                                                 acceleration(acceleration)
{}

void Force::Apply(GameObject* go)
{
    // TODO: Aplica a aceleração da força no GameObject
}

void Force::SetAcceleration(int acceleration)
{
    this->acceleration = acceleration;
}

void Force::SetDirection(Vec2 direction)
{
    this->direction = direction;
}

int Force::GetAcceleration()
{
    return acceleration;
}

Vec2 Force::GetDirection()
{
    return direction;
}
