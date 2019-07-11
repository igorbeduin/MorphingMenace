#include "../include/Entokraton_1_Dead.h"
#include "../include/Entokraton_1.h"
#include "../include/Game.h"

Entokraton_1_Dead::Entokraton_1_Dead(GameObject &associated) : Component::Component(associated), state(RESTING)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENTOKRATON_1_SPRITE_PATH, ENTOKRATON_1_SPRITES_NUMB, ENTOKRATON_1_SPRITES_TIME));
    charSprite->SetScale(ENTOKRATON_1_SCALE, ENTOKRATON_1_SCALE);
    associated.AddComponent(charSprite);
}
void Entokraton_1_Dead::Update(float dt)
{
    Sprite *enemySprite = (Sprite *)associated.GetComponent("Sprite").get();
    enemySprite->SetFrame(DEAD_ENTOKRATON_1_FRAME);
}

void Entokraton_1_Dead::Render()
{


}
bool Entokraton_1_Dead::Is(std::string type)
{
    return (type == "Entokraton_1_Dead");
}

void Entokraton_1_Dead::Attack()//verificar friendly fire
{   
    
}
void Entokraton_1_Dead::Start()//verificar friendly fire
{   
    Character *enemyCharacter = (Character *)associated.GetComponent("Character").get();    
    enemyCharacter->ApplyDamage(MAKE_DEAD_ABSORBABLE);
    enemyCharacter->EnableFlip();
}