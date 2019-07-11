#include "../include/Entokraton_1.h"
#include "../include/Game.h"
#include "../include/Player.h"

Entokraton_1::Entokraton_1(GameObject &associated) : Component::Component(associated), state(RESTING)
{
    std::shared_ptr<Sprite> charSprite(new Sprite(associated, ENTOKRATON_1_SPRITE_PATH, ENTOKRATON_1_SPRITES_NUMB, ENTOKRATON_1_SPRITES_TIME));
    charSprite->SetScale(ENTOKRATON_1_SCALE, ENTOKRATON_1_SCALE);
    associated.AddComponent(charSprite);

    std::shared_ptr<Sound> idle1(new Sound(associated,ENTOKRATON_1_IDLE1_SOUND));
    associated.AddComponent(idle1);
    sounds.emplace_back(idle1);

    std::shared_ptr<Sound> idle2(new Sound(associated, ENTOKRATON_1_IDLE2_SOUND));
    associated.AddComponent(idle2);
    sounds.emplace_back(idle2);

    std::shared_ptr<Sound> walk1(new Sound(associated, ENTOKRATON_1_WALK1_SOUND));
    associated.AddComponent(walk1);
    sounds.emplace_back(walk1);

    std::shared_ptr<Sound> attack(new Sound(associated, ENTOKRATON_1_ATTACK_SOUND));
    associated.AddComponent(attack);
    sounds.emplace_back(attack);
}
void Entokraton_1::Update(float dt)
{
    Character *enemyCharacter = (Character *)associated.GetComponent("Character").get();
    Sprite *enemySprite = (Sprite *)associated.GetComponent("Sprite").get();

    if (enemyCharacter->GetCurrentHP() <= 0)
    {
        state = DYING;
    }
    if (enemyCharacter->GetLastHP() > enemyCharacter->GetCurrentHP())
    {   
        enemyCharacter->SetLastHP(enemyCharacter->GetCurrentHP());
        state = DAMAGED;
  
    }

    switch (state)
    {

    case RESTING:

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_1_IDLE_START);
        enemySprite->SetEndFrame(ENTOKRATON_1_IDLE_END);
        enemySprite->SetAnimationTime(ENTOKRATON_1_IDLE_TIME);

        if  (Character::playerChar != nullptr && 
                ( abs( associated.box.GetCenter().x - Character::playerChar->GetPosition().x ) < ENTOKRATON_1_PERCEPTION )  && abs( associated.box.GetCenter().y - Character::playerChar->GetPosition().y) <  ENTOKRATON_1_PERCEPTION/2.5 )
        {   
            sounds[0]->Play(1);                
            state = CHASING;
        }
        if (restTimer.Get() >= ENTOKRATON_1_COOLDOWN)
        {

            if (direction == -1 )
            {
                // std::cout << "right" << std::endl;
                destination.x = associated.box.GetCenter().x - ENTOKRATON_1_WALK_RANGE;
                destination.y = associated.box.GetCenter().y;
                distance = destination - associated.box.GetCenter();
                enemyCharacter->EnableFlip();
            }
            if (direction == 1 )
            {
                // std::cout << "left" << std::endl;
                destination.x = associated.box.GetCenter().x + ENTOKRATON_1_WALK_RANGE;
                destination.y = associated.box.GetCenter().y;
                distance = destination - associated.box.GetCenter();
                enemyCharacter->DisableFlip();
            }
            sounds[1]->Play(1);
            state = MOVING;
            
        }
        else
        {
            restTimer.Update(dt);
        }
        
        
        break;

    case MOVING://flipar sprite
    // std::cout << "moving" << std::endl;

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_1_WALK_START);
        enemySprite->SetEndFrame(ENTOKRATON_1_WALK_END);
        enemySprite->SetAnimationTime(ENTOKRATON_1_WALK_TIME);
        
        if (enemySprite->GetCurrentFrame() == 13 && firstTime == false)
        {
            sounds[2]->Play(1);
            firstTime = true;
        }
        else if (enemySprite->GetCurrentFrame() == 15 && firstTime == false)
        {
            sounds[2]->Play(1);
            firstTime = true;
        }
         
        else if (enemySprite->GetCurrentFrame() == 16)
        {
            // sounds[2]->Stop();
            firstTime = false;
        }

        if  (Character::playerChar != nullptr && 
                ( abs( associated.box.GetCenter().x - Character::playerChar->GetPosition().x ) < ENTOKRATON_1_PERCEPTION )  && abs( associated.box.GetCenter().y - Character::playerChar->GetPosition().y) <  ENTOKRATON_1_PERCEPTION/2.5 )
        {                
            sounds[0]->Play(1);
            state = CHASING;
        }
        else if ( abs(distance.x) >= ENTOKRATON_1_STOP_RANGE  )
        {
            float movement = direction * ENTOKRATON_1_STEP * dt;

            if (abs(distance.x) >= abs(movement))
            {
                associated.box.x += movement; 
                distance.x -= movement; 
                // distance.x = destination.x - associated.box.GetCenter().x;
                // distance.y = destination.y - associated.box.y;
            }

        }
        else
        {
            restTimer.Restart();
            state = RESTING;
            sounds[0]->Play(1);
            direction = -direction;
        }
        
      


        break;
    
    case CHASING:
        // std::cout << "CHASING" << std::endl;
        //se aproxima do jogador, muda o estado para attacking

        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_1_WALK_START);
        enemySprite->SetEndFrame(ENTOKRATON_1_WALK_END);
        enemySprite->SetAnimationTime(ENTOKRATON_1_WALK_TIME);

        if (enemySprite->GetCurrentFrame() == 13 && firstTime == false)
        {
            sounds[2]->Play(1);
            firstTime = true;
        }
        else if (enemySprite->GetCurrentFrame() == 15 && firstTime == false)
        {
            sounds[2]->Play(1);
            firstTime = true;
        }
         
        else if (enemySprite->GetCurrentFrame() == 16)
        {
            // sounds[2]->Stop();
            firstTime = false;
        }

        distance = Character::playerChar->GetPosition() - associated.box.GetCenter();
        destination = Character::playerChar->GetPosition();

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
        if ( abs(distance.x) > ENTOKRATON_1_PERCEPTION || abs(distance.y) > ENTOKRATON_1_PERCEPTION/2.5)
        {
            // std::cout << "ROBSON FUGIU" << std::endl;
            state = RESTING;
            sounds[1]->Play(1);
            direction = -direction;
        }
         else if ( abs(Character::playerChar->GetPosition().x - associated.box.GetCenter().x ) - associated.box.w/2 > ENTOKRATON_1_ATTACK_RANGE && (abs(distance.x) <= ENTOKRATON_1_PERCEPTION && abs(distance.y) <= ENTOKRATON_1_PERCEPTION/2.5) )
        {
            // std::cout << "volta aqui" << std::endl;
            float movement = direction * ENTOKRATON_1_STEP * dt;
            
            if (abs(distance.x) >= abs(movement))
            {
                associated.box.x += movement; 
                distance.x = destination.x - associated.box.x;
            }

        } else if (abs(Character::playerChar->GetPosition().x - associated.box.GetCenter().x ) - associated.box.w/2 <= ENTOKRATON_1_ATTACK_RANGE)
        {
            state = ATTACKING;
            sounds[3]->Play(1);
        }

        break;

    case ATTACKING:        

        // std::cout << "Entokraton used CUT" << std::endl;
        enemySprite->RunSpecificAnimation();
        enemySprite->SetStartFrame(ENTOKRATON_1_ATTACK_START);
        enemySprite->SetEndFrame(ENTOKRATON_1_ATTACK_END);
        enemySprite->SetAnimationTime(ENTOKRATON_1_ATTACK_TIME);

        if (enemySprite->GetCurrentFrame() == 4)
        {
            Attack();
        }
        if (enemySprite->GetCurrentFrame() == 6)
        {
            state = RESTING;
        }
        break;

    case DAMAGED:


            enemySprite->SetFrame(ENTOKRATON_1_DAMAGED_END);
            enemySprite->RunSpecificAnimation();
            enemySprite->SetStartFrame(ENTOKRATON_1_DAMAGED_START);
            enemySprite->SetEndFrame(ENTOKRATON_1_DAMAGED_END);
            enemySprite->SetAnimationTime(ENTOKRATON_1_DAMAGED_TIME);

            if (Character::playerChar->GetPosition().x > associated.box.GetCenter().x && enemySprite->GetCurrentFrame() == ENTOKRATON_1_DAMAGED_END)
            {
                associated.box.x -= ENEMY_SPACE_PUSHED;
                std::cout << "ai porra" << std::endl;
            }
            else if (Character::playerChar->GetPosition().x < associated.box.GetCenter().x && enemySprite->GetCurrentFrame() == ENTOKRATON_1_DAMAGED_END)
            {
                associated.box.x += ENEMY_SPACE_PUSHED;
                std::cout << "ai porra" << std::endl;
            }            

            if (enemySprite->GetCurrentFrame() == ENTOKRATON_1_DAMAGED_END)
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
                    
            std::shared_ptr<Sprite> death_animation_sprite(new Sprite(*enemy_death, ENTOKRATON_1_SPRITE_PATH, ENTOKRATON_1_SPRITES_NUMB, ENTOKRATON_1_DIE_TIME, ENTOKRATON_1_DIE_TIME));
            death_animation_sprite->SetScale(ENTOKRATON_1_SCALE, ENTOKRATON_1_SCALE);
            enemy_death->AddComponent(death_animation_sprite);

            death_animation_sprite->RunSpecificAnimation();
            death_animation_sprite->SetStartFrame(ENTOKRATON_1_DIE_START);
            death_animation_sprite->SetEndFrame(ENTOKRATON_1_DIE_END);
            death_animation_sprite->SetAnimationTime(ENTOKRATON_1_DIE_TIME);
        }

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
void Entokraton_1::Attack()//verificar friendly fire
{   
    Collider* associatedCollider = (Collider *)associated.GetComponent("Collider").get();
    Character* associatedCharacter = (Character *)associated.GetComponent("Character").get();

    //Creating attack
    GameObject *attack = new GameObject();
    attack->box.w = associated.box.w/2;
    attack->box.h = associated.box.h;
    if (associatedCharacter->IsFlipped())
    {
        attack->box.x = associatedCollider->box.x - attack->box.w/2;
    }
    else
    {
        attack->box.x = associatedCollider->box.x + associatedCollider->box.w/2;
    }
    attack->box.y = associatedCollider->box.GetVec2().y ;

    std::shared_ptr<Damage> attackBehaviour(new Damage(*attack, ENTOKRATON_1_ATTACK_DAMAGE, ENTOKRATON_1_ATTACK_TIME, associatedCharacter->Type()));
    attack->AddComponent(attackBehaviour);
    std::shared_ptr<Collider> attackCollider(new Collider(*attack));
    attack->AddComponent(attackCollider);
    Game::GetInstance().GetCurrentState().AddObject(attack);
    // std::cout << "ATTACK" << std::endl;
}