#include "../include/Entokraton_2.h"
#include "../include/Game.h"

Entokraton_2::Entokraton_2(GameObject &associated) : Component::Component(associated), state(RESTING)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENTOKRATON_2_SPRITE_PATH, ENTOKRATON_2_SPRITES_NUMB, ENTOKRATON_2_SPRITES_TIME));
    charSprite->SetScale(ENTOKRATON_2_SCALE, ENTOKRATON_2_SCALE);
    associated.AddComponent(charSprite);

}
void Entokraton_2::Update(float dt)
{
    Character *enemyCharacter = (Character *)associated.GetComponent("Character").get();
    Sprite *enemySprite = (Sprite *)associated.GetComponent("Sprite").get();

    Easing();
    if (enemyCharacter->GetLastHP() > enemyCharacter->GetCurrentHP())
    {   
        enemyCharacter->SetLastHP(enemyCharacter->GetCurrentHP());
        state = DAMAGED;
  
    }

    if (enemyCharacter->GetCurrentHP() <= 0)
    {
        state = DYING;
    }
    switch (state)
    {

    case RESTING:


        if (direction == -1 )
        {
            // std::cout << "right" << std::endl;
            destination.x = associated.box.GetCenter().x - ENTOKRATON_2_SWIM_RANGE;
            destination.y = associated.box.GetCenter().y;
            distance = destination - associated.box.GetCenter();
            enemyCharacter->DisableFlip();
        }
        if (direction == 1 )
        {
            // std::cout << "left" << std::endl;
            destination.x = associated.box.GetCenter().x + ENTOKRATON_2_SWIM_RANGE;
            destination.y = associated.box.GetCenter().y;
            distance = destination - associated.box.GetCenter();
            enemyCharacter->EnableFlip();
        }
        state = MOVING;

        
        
        break;

    case MOVING://flipar sprite
    // std::cout << "moving" << std::endl;

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_2_SWIM_START);
        enemySprite->SetEndFrame(ENTOKRATON_2_SWIM_END);
        enemySprite->SetAnimationTime(ENTOKRATON_2_SWIM_TIME);

        if ( abs(distance.x) >= ENTOKRATON_2_STOP_RANGE  )
        {
            float movement = direction * ENTOKRATON_2_STEP * dt;

            if (abs(distance.x) >= abs(movement))
            {
                associated.box.x += movement; 
                distance.x -= movement;
            }
            
        }
        else
        {
            state = RESTING;
            direction = -direction;
        }
        break;

    case DAMAGED:

            enemySprite->SetFrame(ENTOKRATON_2_DAMAGED_END);
            enemySprite->RunSpecificAnimation();
            enemySprite->SetStartFrame(ENTOKRATON_2_DAMAGED_START);
            enemySprite->SetEndFrame(ENTOKRATON_2_DAMAGED_END);
            enemySprite->SetAnimationTime(ENTOKRATON_2_DAMAGED_TIME);

            if (Character::playerChar->GetPosition().x > associated.box.GetCenter().x && enemySprite->GetCurrentFrame() == ENTOKRATON_2_DAMAGED_END)
            {
                associated.box.x -= ENEMY_SPACE_PUSHED;
            }
            else if (Character::playerChar->GetPosition().x < associated.box.GetCenter().x && enemySprite->GetCurrentFrame() == ENTOKRATON_2_DAMAGED_END)
            {
                associated.box.x += ENEMY_SPACE_PUSHED;
            }            

            if (enemySprite->GetCurrentFrame() == ENTOKRATON_2_DAMAGED_END)
            {
                state = RESTING;
            }
            
        break;

    case DYING:

        if (enemyCharacter->GetCurrentHP() <= 0)
        {
            GameObject *enemyDeath = new GameObject();
            std::weak_ptr<GameObject> weak_enemy =  Game::GetInstance().GetCurrentState().AddObject(enemyDeath);
            std::shared_ptr<GameObject> enemy_death = weak_enemy.lock();
            enemy_death->box.y = associated.box.y;
            enemy_death->box.x = associated.box.x;
                    
            std::shared_ptr<Sprite> death_animation_sprite(new Sprite(*enemy_death, ENTOKRATON_2_SPRITE_PATH, ENTOKRATON_2_SPRITES_NUMB, ENTOKRATON_2_DIE_TIME, ENTOKRATON_2_DIE_TIME));
            death_animation_sprite->SetScale(ENTOKRATON_2_SCALE, ENTOKRATON_2_SCALE);
            enemy_death->AddComponent(death_animation_sprite);

            death_animation_sprite->RunSpecificAnimation();
            death_animation_sprite->SetStartFrame(ENTOKRATON_2_DIE_START);
            death_animation_sprite->SetEndFrame(ENTOKRATON_2_DIE_END);
            death_animation_sprite->SetAnimationTime(ENTOKRATON_2_DIE_TIME);
        }

        break;
    
    
    default:
        break;
    } 
}

void Entokraton_2::Render()
{

}

bool Entokraton_2::Is(std::string type)
{
    return (type == "Entokraton_2");
}
void Entokraton_2::Easing()
{
    associated.box.y = Vec2(ENTOKRATON_2_INIT_POS).y + EASING_AMPLITUDE * (MAX_COS - cos(EasingCounter * PI));  
    if (EasingCounter >= EASING_LIMIT)
    {
        EasingCounter = 0;
    }
    EasingCounter += EASING_VARIATION;
}