#include "../include/Ocean.h"

std::vector<std::shared_ptr<GameObject>> Ocean::oceanArray;

Ocean::Ocean()
{}

Ocean::~Ocean()
{}

bool Ocean::Contains(Vec2 position)
{
    for (int i = 0; i < (int)oceanArray.size(); i++)
    {
        if (oceanArray[i]->box.Contains(position.x, position.y))
        {
            return true;
        }
    }
    return false;
}

void Ocean::AddOcean(std::shared_ptr<GameObject> ocean)
{
    oceanArray.push_back(ocean);
}

int Ocean::Size()
{
    return (int)oceanArray.size();
}