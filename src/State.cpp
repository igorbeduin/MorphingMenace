#include "../include/State.hpp"
#include "../include/Camera.hpp"
#include "../include/TileMap.hpp"

State::State(){
  quitRequested = false;
  started = false;
  popRequested = false;
}

State::~State(){
  objectArray.clear();
}

void State::LoadAssets(){
}

void State::Update(float dt){
}

void State::Start(){
}

void State::Render(){
}

void State::Pause(){
}

void State::Resume(){
}


std::weak_ptr<GameObject> State::AddObject(GameObject* object){

    std::shared_ptr<GameObject> shared(object);
    objectArray.emplace_back(shared);//adicionando o shared object criado no object array

    std::weak_ptr<GameObject> weak;
    weak = objectArray.back();//weak recebe o último elemento adicionado no object array (que é o shared criado)

    if (started) {
      objectArray.back()->Start();
    }

    return weak;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* object){

  std::weak_ptr<GameObject> weak;
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i].get() == object) {
      weak = objectArray[i];
      return weak;
    }
  }
  return weak;
}


bool State::PopRequested(){
  return popRequested;
}

bool State::QuitRequested(){
  return quitRequested;
}

void State::StartArray(){
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    // std::cout << "START" << '\n';
    objectArray[i]->Start();
  }
}

void State::UpdateArray(float dt){
  for (unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Update(dt);
  }

  for (unsigned int i = 0; i < objectArray.size(); i++) {
    if (objectArray[i]->IsDead()) {
      objectArray.erase(objectArray.begin()+i);
    }
  }
}

void State::RenderArray(){

  std::shared_ptr<TileMap> tile_map;

  for (unsigned int i = 0; i < objectArray.size(); i++) {
    objectArray[i]->Render();
    if (objectArray[i]->GetComponent("TileMap") != nullptr) {
      tile_map = std::dynamic_pointer_cast<TileMap>(objectArray[i]->GetComponent("TileMap"));
    }
  }
  if (tile_map != nullptr) {
    // for (int i = 1; i < tile_map->GetDepth(); i++) {
      Camera::ParallaxUpdate(tile_map->GetDepth() - 1, false);
      tile_map->RenderLayer(tile_map->GetDepth() - 1,  Camera::pos.x, Camera::pos.y);
      Camera::ParallaxUpdate(tile_map->GetDepth() - 1, true);
    // }
  }
}

// Camera::ParallaxUpdate(tile_map->GetWidth()-1, false);
// tile_map->RenderLayer(tile_map->GetWidth()-1, Camera::pos.x*( 1 +tile_map->GetWidth()-1 ), Camera::pos.y*(1 +tile_map->GetWidth()-1 ) );
// Camera::ParallaxUpdate(tile_map->GetWidth()-1, true);
