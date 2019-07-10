#include "../include/Environment.h"

std::vector<std::shared_ptr<Force>> Environment::forcesArray;

Environment::Environment()
{
}

Environment::~Environment()
{}

void Environment::ApplyForces(Character* character)
{
    for (int i = 0; i < (int)forcesArray.size(); i++)
    {
        if (forcesArray[i]->Applicable(character))
        {
            forcesArray[i]->Apply(character);
        }
    }
}

void Environment::AddForce(std::shared_ptr<Force> force)
{
    forcesArray.push_back(force);
}