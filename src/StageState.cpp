#include "../include/StageState.h"
#include "../include/InputManager.h"
#include "../include/Environment.h"

StageState::StageState()
{   
    // Creating gravity
    std::shared_ptr<Gravity> gravity(new Gravity());
    Environment::AddForce(gravity);

    // Creating normal force
    std::shared_ptr<Normal> normal(new Normal());
    Environment::AddForce(normal);

    // Opening background music
    backgroundMusic.Open(STAGE_BG_MUSIC_PATH);


    //Creating Stars background
    GameObject *stars_object = new GameObject();
    std::weak_ptr<GameObject> weak_stars =  AddObject(stars_object);
    std::shared_ptr<GameObject> stars = weak_stars.lock();
    stars->box.y = 0;
    stars->box.x = 0;
    std::shared_ptr<Sprite> stars_sprite(new Sprite(*stars, STARS_BACKGROUND_PATH));
    std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*stars));
    stars->AddComponent(stars_sprite);
    stars->AddComponent(CamFollow);
    
    //Creating planet background
    GameObject *planet_object = new GameObject();
    std::weak_ptr<GameObject> weak_planet =  AddObject(planet_object);
    std::shared_ptr<GameObject> planet = weak_planet.lock();
    planet->box.y = 0;
    planet->box.x = 0;
    std::shared_ptr<Sprite> planet_sprite(new Sprite(*planet, PLANET_BACKGROUND_PATH));
    planet->AddComponent(planet_sprite);
    planet_sprite->SetScale(PLANET_BACKGROUND_SCALE, PLANET_BACKGROUND_SCALE);

    //Creating TileSet and TileMap
    GameObject *tile_object = new GameObject();
    std::weak_ptr<GameObject> weak_tile = AddObject(tile_object);
    std::shared_ptr<GameObject> tileObject = weak_tile.lock();
    tileObject->box.x = 0;
    tileObject->box.y = 0;
    TileSet* tileSet(new TileSet(*tileObject, TILE_WIDTH, TILE_HEIGHT, TILESET_PATH, {TILE_SCALE, TILE_SCALE} ));
    std::shared_ptr<TileMap> tileMap(new TileMap(*tileObject, TILEMAP_PATH , tileSet));
    tileObject->AddComponent(tileMap);

    //Creating player
    GameObject* player = new GameObject();
    std::shared_ptr<Character> playerBehaviour(new Character(*player, PLAYER_LVL0_MASS, char_type::PLAYER));
    player->AddComponent(playerBehaviour);
    std::shared_ptr<Collider> playerCollider(new Collider(*player, Vec2(0.8, 0.58) ));
    player->AddComponent(playerCollider);

    Vec2 initPos = Vec2(PLAYER_INIT_POS);
    player->box.x = initPos.x;
    player->box.y = initPos.y;

    AddObject(player);

    //Creating enemy
    GameObject *enemy = new GameObject();
    std::shared_ptr<Character> enemyBehaviour(new Character(*enemy, PLAYER_LVL0_MASS, char_type::ENTOKRATON_1));
    enemy->AddComponent(enemyBehaviour);
    std::shared_ptr<Collider> enemyCollider(new Collider(*enemy));
    enemy->AddComponent(enemyCollider);

    initPos = Vec2(ENEMY_1_INIT_POS);
    enemy->box.x = initPos.x;
    enemy->box.y = initPos.y;

    AddObject(enemy);

    /*
    //Creating boss
    GameObject *boss = new GameObject();
    std::shared_ptr<Character> BOSSBehaviour(new Character(*boss, PLAYER_LVL0_MASS, char_type::BOSS));
    boss->AddComponent(BOSSBehaviour);
    std::shared_ptr<Collider> BOSSCollider(new Collider(*boss));
    boss->AddComponent(BOSSCollider);

    initPos = Vec2(BOSS_INIT_POS);
    boss->box.x = initPos.x;
    boss->box.y = initPos.y;

    AddObject(boss);
    */
}

void StageState::LoadAssets()
{
}

void StageState::Update(float dt)
{
    Camera::Update(dt);

    // Verify collisions
    std::vector<std::shared_ptr<GameObject>> objWithCollider;
    for (int i = (int)objectArray.size() - 1; i >= 0; i--)
    {
        std::shared_ptr<Collider> colliderComponent = std::dynamic_pointer_cast<Collider>(objectArray[i]->GetComponent("Collider"));
        // If GO DOES has a "Collider" component
        if (colliderComponent != nullptr)
        {
            objWithCollider.push_back(objectArray[i]);
            for (int j = 0; j < (int)objWithCollider.size(); j++)
            {
                std::shared_ptr<Collider> ObjWithcolliderComponent = std::dynamic_pointer_cast<Collider>(objWithCollider[j]->GetComponent("Collider"));
                if (objectArray[i] != objWithCollider[j])
                {
                    if (Collision::IsColliding(colliderComponent->box, ObjWithcolliderComponent->box, objectArray[i]->GetAngleRad(), objWithCollider[j]->GetAngleRad()))
                    {
                        objectArray[i]->NotifyCollision(*objWithCollider[j].get());
                        objWithCollider[j]->NotifyCollision(*objectArray[i].get());
                    }
                }
            }
        }
    }

    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }
    
    // std::cout << "(int)objectArray.size(): " << (int)objectArray.size() << std::endl;
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
}

void StageState::Render()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
}

StageState::~StageState()
{
}

void StageState::Start()
{
    backgroundMusic.Play(-1);
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}
