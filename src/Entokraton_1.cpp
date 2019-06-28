#include "../include/Entokraton_1.h"

Entokraton_1::Entokraton_1(GameObject &associated) : Component::Component(associated), state(RESTING)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENEMY_1_SPRITE_PATH, ENEMY_1_SPRITES_NUMB, ENEMY_1_SPRITES_TIME));
    charSprite->SetScale(ENEMY_1_SCALE, ENEMY_1_SCALE);
    associated.AddComponent(charSprite);
}
void Entokraton_1::Update(float dt)
{
    Sprite *enemySprite = (Sprite *)associated.GetComponent("Sprite").get();
    switch (state)
    {

    case RESTING:

    enemySprite->RunSpecificAnimation();
    enemySprite->SetStartFrame(ENEMY_1_IDLE_START);
    enemySprite->SetEndFrame(ENEMY_1_IDLE_END);
    enemySprite->SetAnimationTime(ENEMY_1_IDLE_TIME);

        if (restTimer.Get() >= ENEMY_1_COOLDOWN)
        {

            if (Character::player != nullptr && ( associated.box.GetVec2() - Character::player->GetPosition() ).Absolute() < 200 ) 
            {
                // distance = Character::player->GetPosition() - associated.box.GetVec2();
                // if (distance.x < 0)
                // {
                //     direction = -1;
                // }
                // else
                // {
                //     direction = 1;
                // }
                
                
                // state = CHASING;
            }
            else
            {

                if (direction == -1 )
                {
                    std::cout << "right" << std::endl;
                    destination.x = associated.box.x - WALK_RANGE;
                    destination.y = associated.box.y;
                    distance = destination - associated.box.GetVec2();
                }
                if (direction == 1 )
                {
                    std::cout << "left" << std::endl;
                    destination.x = associated.box.x + WALK_RANGE;
                    destination.y = associated.box.y;
                    distance = destination - associated.box.GetVec2();
                }
                state = MOVING;
            }
        }
        else
        {
            restTimer.Update(dt);
        }
        
        
        break;

    case MOVING://flipar sprite

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENEMY_1_WALK_START);
        enemySprite->SetEndFrame(ENEMY_1_WALK_END);
        enemySprite->SetAnimationTime(ENEMY_1_WALK_TIME);

        if ( abs(distance.x) >= STOP_RANGE  )
        {
            float movement = direction * ENEMY_1_STEP * dt;
            std::cout << "\ndest: "  << destination.x << ", " << destination.y << std::endl;
            std::cout << "assc: " << associated.box.x << ", " << associated.box.y << std::endl;
            std::cout << "dist: " << distance.x << ", " << distance.y << std::endl;
            std::cout << " mov: " << movement << ", dir: "<< direction <<"\n" <<std::endl;
            
            if (abs(distance.x) >= abs(movement))
            {
                associated.box.x += movement; 
                distance.x = destination.x - associated.box.x;
                distance.y = destination.y - associated.box.y;
            }
            if (abs(distance.x) < STOP_RANGE +1)
            {
                associated.box.x = destination.x;
            }

        }
        else
        {
            restTimer.Restart();
            state = RESTING;
            direction = -direction;
        }
        
      


        break;
        
    case ATTACKING:
        //para o movimento e chama o método attacking
        break;
    
    case CHASING://flipar sprite
        //se aproxima do jogador, muda o estado para attacking

        // enemySprite->RunSpecificAnimation();
        // enemySprite->SetStartFrame(ENEMY_1_WALK_START);
        // enemySprite->SetEndFrame(ENEMY_1_WALK_END);
        // enemySprite->SetAnimationTime(ENEMY_1_WALK_TIME);
        
        // if ( distance.Absolute() >= STOP_RANGE  )
        // {
        //     float movement = direction * ENEMY_1_STEP * dt;
        //     // std::cout << "\ndest: "  << destination.x << ", " << destination.y << std::endl;
        //     // std::cout << "assc: " << associated.box.x << ", " << associated.box.y << std::endl;
        //     // std::cout << "dist: " << distance.x << ", " << distance.y << std::endl;
        //     // std::cout << " mov: " << movement << ", dir: "<< direction <<"\n" <<std::endl;
            
        //     if (distance.Absolute() >= abs(movement))
        //     {
        //         associated.box.x += movement;
        //         distance = Character::player->GetPosition() - associated.box.GetVec2();
        //     }
        // }
        
        break;
    
    default:
        break;
    }

}

void Entokraton_1::Render()
{}
bool Entokraton_1::Is(std::string type)
{
    return (type == "Entokraton_1");
}