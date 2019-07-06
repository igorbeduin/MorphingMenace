#include "../include/Boss_Core.h"

BossCore::BossCore(GameObject &associated):Component(associated)
{
    std::shared_ptr<Sprite> sprite(new Sprite(associated, BOSS_CORE_SPRITE_PATH));
    sprite->SetScale(BOSS_CORE_SCALE, BOSS_CORE_SCALE);
    associated.AddComponent(sprite);
    std::cout << "Criou core" << std::endl;

}

void BossCore::Update(float dt)
{
    
}

void BossCore::Render()
{
    
}

bool BossCore::Is(std::string type)
{
    return (type == "BossCore");
}

void BossCore::Shoot(Vec2 target)
{
    //criar projétil e atirar
    std::cout << "tiro no cu" << std::endl;
}
