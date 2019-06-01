#include "../include/StageState.hpp"
#include "../include/Game.hpp"
#include "../include/GameData.hpp"
#include "../include/InputManager.hpp"

StageState::StageState(){


  /////////////////Background
  std::cout << "Loading Stage..." << '\n';
  GameObject *bg_object = new GameObject();

  std::weak_ptr<GameObject> weak_bg =  AddObject(bg_object);
  std::shared_ptr<GameObject> bg = weak_bg.lock();

  // bg->box.x = 9000;
  // bg->box.y = 2000;
  bg->box.y = 0;
  bg->box.x = 0;
  std::shared_ptr<Sprite> bg_sprite(new Sprite(*bg, BG_PATH));
  std::shared_ptr<CameraFollower> CamFollow(new CameraFollower(*bg));
  bg->AddComponent(bg_sprite);
  bg->AddComponent(CamFollow);
  // bg_sprite->SetScaleX(0.1066, 0.5);
  // bg_sprite->SetScaleX(0.1066, 0.2777);

  ////////////////TileSet
  GameObject *tile_object = new GameObject();

  std::weak_ptr<GameObject> weak_tile = AddObject(tile_object);
  std::shared_ptr<GameObject> tileObject = weak_tile.lock();

  tileObject->box.x = Camera::pos.x;
  tileObject->box.y = Camera::pos.y;
  TileSet* tileSet(new TileSet(*tileObject, 1024, 1024, TILESET_PATH, {0.0625, 0.0625} ));
  // TileSet* tileSet(new TileSet(*tileObject, 2048, 2048, TILESET_PATH, {0.03125, 0.03125} ));
  std::shared_ptr<TileMap> tileMap(new TileMap(*tileObject, TILEMAP_PATH , tileSet));
  tileObject->AddComponent(tileMap);
  // tileSet->tileSet.SetScaleX(0.03125, 0.03125);


  ////////////////ALIENS

  ////////////////PENGUIN


  quitRequested = false;//inicializa o quitRequested
  started = false;
  LoadAssets();//carrega as imagens e músicasa serem utilizadas
}

void StageState::LoadAssets(){

  // backgroundMusic.Open(MUSIC_PATH);
  // backgroundMusic.Play(-1);//toca a música carregada

}

void StageState::Update(float dt){//etapa 3 de  Game::Run, atualiza o estado, por enquanto apenas verifica se já vai sair do jogo

  InputManager& input = InputManager::GetInstance();
  Game& game = Game::GetInstance();
  Camera::Update(dt);

  if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    popRequested = true;
  }

  if (input.KeyPress(TAB_KEY)) {
    std::cout << "StageState" << '\n';
  }



  if (input.KeyPress(ENTER_KEY)) {
    popRequested = true;
    EndState* endState = new EndState();
    game.Push(endState);
  }
  if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
    Camera::pos.x -= 50;
    std::cout << "MOVE ->" << '\n';
  }
  if (input.IsKeyDown(LEFT_ARROW_KEY)) {
    Camera::pos.x += 50;
    std::cout << "MOVE <-" << '\n';
  }
  if (input.IsKeyDown(UP_ARROW_KEY)) {
    Camera::pos.y += 50;
    std::cout << "MOVE up " << '\n';
  }
  if (input.IsKeyDown(DOWN_ARROW_KEY)) {
    Camera::pos.y -= 50;
    std::cout << "MOVE down" << '\n';
  }

  UpdateArray(dt);

}

void StageState::Render(){//etapa 4 de Gamme::Run, renderiza o estado do jogoIsso inclui entidades, cenários, HUD, entre outros. Para esse rabalho, é chamdo apenas o render do fundo (bg).
  RenderArray();
}

StageState::~StageState(){
  objectArray.clear();
}

void StageState::Start(){
  LoadAssets();
  StartArray();
  started = true;
}

void StageState::Pause(){

}

void StageState::Resume(){

}
