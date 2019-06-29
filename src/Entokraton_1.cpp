#include "../include/Entokraton_1.h"

Entokraton_1::Entokraton_1(GameObject &associated) : Component::Component(associated), state(RESTING)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENTOKRATON_1_SPRITE_PATH, ENTOKRATON_1_SPRITES_NUMB, ENTOKRATON_1_SPRITES_TIME));
    charSprite->SetScale(ENTOKRATON_1_SCALE, ENTOKRATON_1_SCALE);
    associated.AddComponent(charSprite);
}
void Entokraton_1::Update(float dt)
{
    Character *enemyCharacter = (Character *)associated.GetComponent("Character").get();
    Sprite *enemySprite = (Sprite *)associated.GetComponent("Sprite").get();
    switch (state)
    {

    case RESTING:
    std::cout << "idle" << std::endl;
    // std::cout << associated.box.x << " - " << Character::player->box.x << std::endl;

    enemySprite->RunSpecificAnimation();
    enemySprite->SetStartFrame(ENTOKRATON_1_IDLE_START);
    enemySprite->SetEndFrame(ENTOKRATON_1_IDLE_END);
    enemySprite->SetAnimationTime(ENTOKRATON_1_IDLE_TIME);

        if  (Character::player != nullptr && 
                ( abs( associated.box.GetCenter().x - Character::player->GetPosition().x ) < ENTOKRATON_1_PERCEPTION )  && abs( associated.box.GetCenter().y - Character::player->GetPosition().y) <  ENTOKRATON_1_PERCEPTION/2.5 )
        {                
            state = CHASING;
        }
        if (restTimer.Get() >= ENTOKRATON_1_COOLDOWN)
        {

            if (direction == -1 )
            {
                // std::cout << "right" << std::endl;
                destination.x = associated.box.GetCenter().x - ENTOKRATON_1_WALK_RANGE;
                destination.y = associated.box.GetCenter().y;
                distance = destination - associated.box.GetVec2();
                enemyCharacter->EnableFlip();
            }
            if (direction == 1 )
            {
                // std::cout << "left" << std::endl;
                destination.x = associated.box.GetCenter().x + ENTOKRATON_1_WALK_RANGE;
                destination.y = associated.box.GetCenter().y;
                distance = destination - associated.box.GetVec2();
                enemyCharacter->DisableFlip();
            }
            state = MOVING;
            
        }
        else
        {
            restTimer.Update(dt);
        }
        
        
        break;

    case MOVING://flipar sprite
    std::cout << "wandering away" << std::endl;

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_1_WALK_START);
        enemySprite->SetEndFrame(ENTOKRATON_1_WALK_END);
        enemySprite->SetAnimationTime(ENTOKRATON_1_WALK_TIME);

        if  (Character::player != nullptr && 
                ( abs( associated.box.GetCenter().x - Character::player->GetPosition().x ) < ENTOKRATON_1_PERCEPTION )  && abs( associated.box.GetCenter().y - Character::player->GetPosition().y) <  ENTOKRATON_1_PERCEPTION/2.5 )
        {                
            state = CHASING;
        }
        else if ( abs(distance.x) >= ENTOKRATON_1_STOP_RANGE  )
        {
            float movement = direction * ENTOKRATON_1_STEP * dt;

            if (abs(distance.x) >= abs(movement))
            {
                associated.box.x += movement; 
                distance.x = destination.x - associated.box.GetCenter().x;
                // distance.y = destination.y - associated.box.y;
            }

        }
        else
        {
            restTimer.Restart();
            state = RESTING;
            direction = -direction;
        }
        
      


        break;
    
    case CHASING:
        std::cout << "CHASING" << std::endl;
        //se aproxima do jogador, muda o estado para attacking

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_1_WALK_START);
        enemySprite->SetEndFrame(ENTOKRATON_1_WALK_END);
        enemySprite->SetAnimationTime(ENTOKRATON_1_WALK_TIME);

        distance = Character::player->GetPosition() - associated.box.GetCenter();
        destination = Character::player->GetPosition();

        if (distance.x < 0)
        {
            direction = -1;
            enemyCharacter->EnableFlip();            
        }
        else
        {
            direction = 1;
            enemyCharacter->DisableFlip();

        }
        // std::cout << "x: "<< (  abs(distance.x) > ENTOKRATON_1_PERCEPTION  ) << ", y: " << (abs(distance.y) > ENTOKRATON_1_PERCEPTION/5) << std::endl;
        if ( abs(distance.x) > ENTOKRATON_1_PERCEPTION && abs(distance.y) < ENTOKRATON_1_PERCEPTION/2.5)
        {
            std::cout << "ROBSON FUGIU" << std::endl;
            state = RESTING;
            direction = -direction;
        }
         else if ( abs(Character::player->GetPosition().x - associated.box.GetCenter().x ) - associated.box.w/2 > ENTOKRATON_1_ATTACK_RANGE && (abs(distance.x) <= ENTOKRATON_1_PERCEPTION && abs(distance.y) <= ENTOKRATON_1_PERCEPTION/2.5) )
        {
            std::cout << "volta aqui" << std::endl;
            float movement = direction * ENTOKRATON_1_STEP * dt;
            
            if (abs(distance.x) >= abs(movement))
            {
                associated.box.x += movement; 
                distance.x = destination.x - associated.box.x;
            }

        } else if (abs(Character::player->GetPosition().x - associated.box.GetCenter().x ) - associated.box.w/2 <= ENTOKRATON_1_ATTACK_RANGE)
        {
            state = ATTACKING;
        }

        break;

    case ATTACKING:        

        std::cout << "ENTOKRATON used SLASH" << std::endl;
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