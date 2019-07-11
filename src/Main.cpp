#include "../include/Game.h"
#include "../include/TitleState.h"

int main(int argc, char *argv[]) {

  Game& game = Game::GetInstance();//cria o game

  // StageState* stageState = new StageState();
  // game.Push(stageState);
  TitleState* Start = new TitleState();
  game.Push(Start);
  game.Run();//executa o game até a janela ser fechada
  return 0;

}
