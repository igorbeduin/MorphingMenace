#pragma once

#include "Vec2.h"
#include "GameObject.h"
#include <iostream>

class Ocean
{
public:
    Ocean();
    ~Ocean();
    static int Size();
    static bool Contains(Vec2 position);
    void AddOcean(std::shared_ptr<GameObject> ocean);
private:
    static std::vector<std::shared_ptr<GameObject>> oceanArray;
};