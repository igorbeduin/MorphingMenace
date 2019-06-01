#include "../include/EndState.hpp"
#include "../include/InputManager.hpp"
#include "../include/GameData.hpp"

EndState::EndState(){
  std::cout << "end" << '\n';

}

EndState::~EndState(){

}

void EndState::LoadAssets(){

}

void EndState::Update(float dt){

  InputManager& input = InputManager::GetInstance();
  Game& game = Game::GetInstance();

  if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
    std::cout << "sai" << '\n';
  }

  if (input.KeyPress(TAB_KEY)) {
    std::cout << "EndState" << '\n';
  }

  if (input.KeyPress(SPACE_KEY)) {
    std::cout << "sai" << '\n';
    popRequested = true;
    TitleState* titleState = new TitleState();
    game.Push(titleState);
  }

  UpdateArray(dt);

}

void EndState::Render(){
  RenderArray();
}

void EndState::Start(){
  LoadAssets();
  StartArray();
}

void EndState::Pause(){

}

void EndState::Resume(){

}
