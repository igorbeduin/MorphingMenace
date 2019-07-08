#include "../include/Boss_Core.h"

BossCore::BossCore(GameObject &associated):Component(associated)
{
    std::shared_ptr<Sprite> sprite(new Sprite(associated, BOSS_CORE_SPRITE_PATH));
    sprite->SetScale(BOSS_CORE_SCALE, BOSS_CORE_SCALE);
    associated.AddComponent(sprite);
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
    Character* associatedCharacter = (Character *)associated.GetComponent("Character").get();

    GameObject *acid_object = new GameObject;
    std::weak_ptr<GameObject> weak_acid =  Game::GetInstance().GetCurrentState().AddObject(acid_object);//pega a função AddObject do state para adicionar o novo acid ao array de objetos
    std::shared_ptr<GameObject> acid = weak_acid.lock();

    acid->box.x = associated.box.GetCenter().x;//a posição em que a acid sai é a mesma possição so minion
    acid->box.y = associated.box.GetCenter().y;

    float angle = atan2(target.y - associated.box.y - associated.box.h/2, target.x - associated.box.x - associated.box.w/2);

    std::shared_ptr<Acid> acid_s(new Acid(*acid, angle, ACID_SPEED));//divide o arco de 360 graus pela quantidade de acids desejada para que tenham a mesma distância entre si
    acid->AddComponent(acid_s);


    std::shared_ptr<Damage> acidBehaviour(new Damage(*acid, ACID_DAMAGE, ACID_DAMAGE_TIME, associatedCharacter->Type()));
    acid->AddComponent(acidBehaviour);
}
