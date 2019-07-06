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
    std::cout << "bang" << std::endl;
    Character* associatedCharacter = (Character *)associated.GetComponent("Character").get();

    GameObject *acid_object = new GameObject();
    std::weak_ptr<GameObject> weak_acid =  Game::GetInstance().GetCurrentState().AddObject(acid_object);//pega a função AddObject do state para adicionar o novo acid ao array de objetos
    std::shared_ptr<GameObject> acid = weak_acid.lock();
    // Vec2 shoot_dist = (target - associated.box.GetCenter());// a distância do tiro é o vetor resultante da diferença da posição do tiro e da posição do minion que vai atirar

    acid->box.x = associated.box.x + associated.box.w/2;//a posição em que a acid sai é a mesma possição so minion
    acid->box.y = associated.box.y + associated.box.h/2;

    float angle = atan2(target.y - associated.box.y - associated.box.h/2, target.x - associated.box.x - associated.box.w/2);

    std::shared_ptr<Acid> acid_s(new Acid(*acid, angle, ACID_SPEED));//divide o arco de 360 graus pela quantidade de acids desejada para que tenham a mesma distância entre si
    acid->AddComponent(acid_s);

    // std::shared_ptr<Damage> acidBehaviour(new Damage(*acid, ACID_DAMAGE, ACID_DAMAGE_TIME, char_type::BOSS_CORE));
    std::cout << "passando pro damage: " << associatedCharacter->Type() << std::endl;
    // acid->AddComponent(acidBehaviour);
}
void BossCore::CoreDeath(int killed_core)
{
    // std::shared_ptr<Boss> hivemind = boss.lock();
    // if (hivemind->coreArray.size() != 0)
    // {
    //     hivemind->coreArray.erase(hivemind->coreArray.begin() + killed_core);
    // }
    
}
