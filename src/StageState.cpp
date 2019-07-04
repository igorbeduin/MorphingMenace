#include "../include/StageState.h"
#include "../include/InputManager.h"
#include "../include/Environment.h"
#include "../include/Resources.h"

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
    std::shared_ptr<Character> playerCharacter(new Character(*player, PLAYER_INITIAL_HP, char_type::PLAYER));
    player->AddComponent(playerCharacter);
    std::shared_ptr<Collider> playerCollider(new Collider(*player));
    player->AddComponent(playerCollider);

    Vec2 initPos = Vec2(PLAYER_INIT_POS);
    player->box.x = initPos.x;
    player->box.y = initPos.y;

    AddObject(player);

    //Creating GUI
    GameObject *gui = new GameObject();
    std::shared_ptr<CameraFollower> guiCamFollow(new CameraFollower(*gui));
    gui->AddComponent(guiCamFollow);
    std::shared_ptr<GUI> playerGUI(new GUI(*gui, *player));
    gui->AddComponent(playerGUI);

    AddObject(gui);

    //Creating enemy
    GameObject *enemy = new GameObject();
    std::shared_ptr<Character> enemyCharacter(new Character(*enemy, ENTOKRATON_1_HP, char_type::ENTOKRATON_1));
    enemy->AddComponent(enemyCharacter);
    std::shared_ptr<Collider> enemyCollider(new Collider(*enemy));
    enemy->AddComponent(enemyCollider);

    initPos = Vec2(ENTOKRATON_1_INIT_POS);
    enemy->box.x = initPos.x;
    enemy->box.y = initPos.y;

    AddObject(enemy);

    
    //Creating boss
    GameObject *boss = new GameObject();
    std::shared_ptr<Character> bossCharacter(new Character(*boss, 100, char_type::BOSS));
    boss->AddComponent(bossCharacter);
    std::shared_ptr<Collider> BOSSCollider(new Collider(*boss));
    boss->AddComponent(BOSSCollider);

    initPos = Vec2(BOSS_INIT_POS);
    boss->box.x = initPos.x;
    boss->box.y = initPos.y;

    AddObject(boss);
    
}

void StageState::LoadAssets()//sempre que tiver uma imagem/som/texto novo, carregar ele no load
{
    Resources::AddImage(PLAYER_LVL0_SPRITE_PATH);
    Resources::AddImage(PLAYER_LVL1_SPRITE_PATH);
    Resources::AddImage(ENTOKRATON_1_SPRITE_PATH);
    Resources::AddImage(STARS_BACKGROUND_PATH);
    Resources::AddImage(TILESET_PATH);
    Resources::AddImage(PLANET_BACKGROUND_PATH);
    Resources::AddImage(GUI_LIFE_PATH);
    Resources::AddImage(GUI_INFLUENCE_PATH);
    Resources::AddImage(GUI_BONE_DUST_PATH);
    ////////////////////////////////////////////
    Resources::AddSound(ENTOKRATON_1_IDLE1_SOUND);
    Resources::AddSound(ENTOKRATON_1_IDLE2_SOUND);
    Resources::AddSound(ENTOKRATON_1_WALK1_SOUND);
}

void StageState::Update(float dt)
{
    Camera::Update(dt);

    // Verify collisions
    std::vector<std::shared_ptr<GameObject>> objWithCollider;
    Vec2 distanceToBox;
    for (int i = (int)objectArray.size() - 1; i >= 0; i--)
    {
        std::shared_ptr<Collider> colliderComponent = std::dynamic_pointer_cast<Collider>(objectArray[i]->GetComponent("Collider"));
        // If GO DOES has a "Collider" component
        if (colliderComponent != nullptr)
        {
            objWithCollider.push_back(objectArray[i]);
            // Verify collision with other GameObjects
            for (int j = 0; j < (int)objWithCollider.size(); j++)
            {
                distanceToBox = objectArray[i]->box.GetCenter() - objWithCollider[j]->box.GetCenter();
                if (distanceToBox.Absolute() <= SCENARIO_COLLISION_RADIUS)
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
            // Verify collision with SCENARIO collision objects
            for (int j = 0; j < (int)collisionObjectsArray.size(); j++)
            {   
                distanceToBox = objectArray[i]->box.GetCenter() - collisionObjectsArray[j]->box.GetCenter();
                if (distanceToBox.Absolute() <= SCENARIO_COLLISION_RADIUS)
                {
                    std::shared_ptr<Collider> collisionObjectComponent = std::dynamic_pointer_cast<Collider>(collisionObjectsArray[j]->GetComponent("Collider"));
                    if (Collision::IsColliding(colliderComponent->box, collisionObjectComponent->box, objectArray[i]->GetAngleRad(), collisionObjectsArray[j]->GetAngleRad()))
                    {
                        objectArray[i]->NotifyCollision(*collisionObjectsArray[j].get());
                    }
                }
            }
        }
    }
    if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
    {
        quitRequested = true;
    }
    
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Update(dt);
    }
    for (int i = 0; i < (int)collisionObjectsArray.size(); i++)
    {
        collisionObjectsArray[i]->Update(dt);
    }

    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        if (objectArray[i]->IsDead())
        {
            objectArray.erase(objectArray.begin() + i);
        }
    }
    // std::cout << "objectArray.size():" << objectArray.size() << std::endl;
}

void StageState::Render()
{
    for (int i = 0; i < (int)objectArray.size(); i++)
    {
        objectArray[i]->Render();
    }
    for (int i = 0; i < (int)collisionObjectsArray.size(); i++)
    {
        collisionObjectsArray[i]->Render();
    }
}

StageState::~StageState()
{
}

void StageState::Start()
{
    LoadAssets();
    backgroundMusic.Play(-1);
}

void StageState::Pause()
{
}

void StageState::Resume()
{
}

std::weak_ptr<GameObject> StageState::AddCollisionObject(GameObject *object)
{

    std::shared_ptr<GameObject> shared(object);
    collisionObjectsArray.emplace_back(shared); //adicionando o shared object criado no object array

    std::weak_ptr<GameObject> weak;
    weak = collisionObjectsArray.back(); //weak recebe o último elemento adicionado no object array (que é o shared criado)

    if (started)
    {
        collisionObjectsArray.back()->Start();
    }

    return weak;
}