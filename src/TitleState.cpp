#include "../include/TitleState.hpp"
#include "../include/InputManager.hpp"
#include "../include/Game.hpp"

TitleState::TitleState(){

}

TitleState::~TitleState(){
  objectArray.clear();
}


void TitleState::LoadAssets(){

}

void TitleState::Update(float dt){
  // std::cout << "titulo" << '\n';
  InputManager& input = InputManager::GetInstance();
  Game& game = Game::GetInstance();

  if(input.QuitRequested() || input.KeyPress(ESCAPE_KEY)) {
    quitRequested = true;
  }


  if (input.KeyPress(SPACE_KEY)) {
    StageState* stageState = new StageState();
    game.Push(stageState);
    std::cout << "chamou o state" << '\n';
  }

  if (input.KeyPress(TAB_KEY)) {
    std::cout << "TitleState" << '\n';
  }

  UpdateArray(dt);
}

void TitleState::Render(){
  RenderArray();
}


void TitleState::Start(){
  LoadAssets();
  StartArray();
  started = true;
}

void TitleState::Pause(){

}

void TitleState::Resume(){
}
