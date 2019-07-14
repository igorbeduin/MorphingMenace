#include "../include/WaterDamage.h"

WaterDamage::WaterDamage(GameObject &associated) : Component::Component(associated),
                                                   cooldown(WATER_CD)
{}
void WaterDamage::Update(float dt)
{
    clock.Update(dt);
    Player* playerPtr = (Player*)associated.GetComponent("Player").get();
    Character *charPtr = (Character *)associated.GetComponent("Character").get();
    if (playerPtr != nullptr)
    {
        if (charPtr->VerifyOcean())
        {
            if (playerPtr->applyWaterDamage)
            {
                if (playerPtr->GetLvl() != 0)
                {
                    playerPtr->LvlDown();
                }
                if (charPtr != nullptr)
                {
                    if (clock.Get() >= WATER_CD)
                    {
                        charPtr->ApplyDamage(WATER_DAMAGE);
                        std::cout << "Applied water damage" << std::endl;
                        clock.Restart();
                    }
                }
            }
        }
    }
}

void WaterDamage::Render()
{}
bool WaterDamage::Is(std::string type)
{
    return (type == "WaterDamage");
}