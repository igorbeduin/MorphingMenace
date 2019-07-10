#include "../include/Transformation.h"
#include "../include/Player.h"

void Transformation::Downgrade()
{}
void Transformation::Absorb()
{
    Player::player->LvlDown();
    Player::player->Absorb();
}

float Transformation::GetWidth()
{
    return sprite->GetWidth();
}
float Transformation::GetHeight()
{
    return sprite->GetHeight();
}