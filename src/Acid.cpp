  #include "../include/Acid.h"
  #include "../include/Character.h"
  
Acid::Acid(GameObject& associated, float angle, float speed): Component(associated)
{
    std::shared_ptr<Sprite> acid_sprite(new Sprite(associated, ACID_SPRITE_PATH, ACID_SPRITES_NUMB, ACID_SPRITES_TIME));
    associated.AddComponent(acid_sprite);

    std::shared_ptr<Collider> acid_collider(new Collider(associated));//criando a sprite e adicionando ao vetor de Components
    associated.AddComponent(acid_collider);

    this->speed.x = speed*cos(angle);//define o vetor velocidade de acordo com o valor passado para o consturtor
    this->speed.y = speed*sin(angle);

    associated.angleDeg = angle*180/PI;
    AcidTime.Restart();
}

void Acid::Update(float dt)
{
    associated.box.x += speed.x*dt;
    associated.box.y += speed.y*dt;
    // std::cout << associated.box.x << ", " << associated.box.y << std::endl;
    if ( AcidTime.Get() <= ACID_DAMAGE_TIME )
    {
        AcidTime.Update(dt);
    }
    else
    {
        associated.RequestDelete();
    }
}
void Acid::Render()
{
    
}

bool Acid::Is(std::string type)
{
      
}
int Acid::GetDamage()
{
      
}