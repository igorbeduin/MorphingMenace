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
    std::cout << "idle" << std::endl;

    enemySprite->RunSpecificAnimation();
    enemySprite->SetStartFrame(ENEMY_1_IDLE_START);
    enemySprite->SetEndFrame(ENEMY_1_IDLE_END);
    enemySprite->SetAnimationTime(ENEMY_1_IDLE_TIME);

        if (restTimer.Get() >= ENEMY_1_COOLDOWN)
        {

            if  (Character::player != nullptr && 
                ( abs( associated.box.x - Character::player->GetPosition().x ) < ENEMY_1_PERCEPTION ) )
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
                
                
                state = CHASING;
                // std::cout << "chama chasing" << std::endl;
            }
            else
            {
                Character *enemyCharacter = (Character *)associated.GetComponent("Character").get();
                if (direction == -1 )
                {
                    // std::cout << "right" << std::endl;
                    destination.x = associated.box.x - WALK_RANGE;
                    destination.y = associated.box.y;
                    distance = destination - associated.box.GetVec2();
                    enemyCharacter->EnableFlip();
                }
                if (direction == 1 )
                {
                    // std::cout << "left" << std::endl;
                    destination.x = associated.box.x + WALK_RANGE;
                    destination.y = associated.box.y;
                    distance = destination - associated.box.GetVec2();
                    enemyCharacter->DisableFlip();
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
    std::cout << "wandering away" << std::endl;

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENEMY_1_WALK_START);
        enemySprite->SetEndFrame(ENEMY_1_WALK_END);
        enemySprite->SetAnimationTime(ENEMY_1_WALK_TIME);

        if  (Character::player != nullptr && 
                ( abs( associated.box.x - Character::player->GetPosition().x ) < ENEMY_1_PERCEPTION ) )
        {                
            state = CHASING;
        }
        else if ( abs(distance.x) >= STOP_RANGE  )
        {
            float movement = direction * ENEMY_1_STEP * dt;
            
            // std::cout << "\ndest: "  << destination.x << ", " << destination.y << std::endl;
            // std::cout << "assc: " << associated.box.x << ", " << associated.box.y << std::endl;
            // std::cout << "dist: " << distance.x << ", " << distance.y << std::endl;
            // std::cout << " mov: " << movement << ", dir: "<< direction <<"\n" <<std::endl;
            
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
        std::cout << "ENTOKRATON used SLASH" << std::endl;
        state = RESTING;
        break;
    
    case CHASING://flipar sprite
        // std::cout << "VOLTA AQUI OTÀRIO" << std::endl;
        std::cout << "CHASING" << std::endl;
        //se aproxima do jogador, muda o estado para attacking

        // enemySprite->RunSpecificAnimation();
        // enemySprite->SetStartFrame(ENEMY_1_WALK_START);
        // enemySprite->SetEndFrame(ENEMY_1_WALK_END);
        // enemySprite->SetAnimationTime(ENEMY_1_WALK_TIME);

        // if (associated.box.x + associated.box.w < Character::player->box.x)
        // {//inimigo à esquerda
        //     std::cout << "->";
        //     distance.x = Character::player->box.x - associated.box.x - associated.box.w;
        //     float movement = ENEMY_1_STEP * dt;

        //     if (distance.x >= abs(movement))
        //     {
        //         associated.box.x += movement;
        //         distance.x -= movement;
        //     }
        //     else if (distance.x < ENEMY_1_ATTACK_RANGE)
        //     {
        //         state = ATTACKING;
        //     }
        // }
        // else if (associated.box.x > Character::player->box.x + Character::player->box.w)
        // {//inimigo à direita
        //     std::cout << "<-";
        //     distance.x = associated.box.x - Character::player->box.x - Character::player->box.w;
        //     float movement = ENEMY_1_STEP * dt;

        //     if (distance.x >= abs(movement))
        //     {
        //         associated.box.x -= movement;
        //         distance.x -= movement;
        //     }
        //     if (distance.x < ENEMY_1_ATTACK_RANGE)
        //     {
        //         state = ATTACKING;
        //     }        
        // }
        // else if (distance.x > ENEMY_1_PERCEPTION)
        // {
        //    state = RESTING;
        // }
        // std::cout << "distance" << distance.x << std::endl;
        /////////////////////////////////////////////////////////////////
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
        state = RESTING;
        
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