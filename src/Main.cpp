#include "../include/Game.hpp"
#include "../include/TitleState.hpp"

int main(int argc, char *argv[]) {

  Game& game = Game::GetInstance();//cria o game

  // StageState* stageState = new StageState();
  // game.Push(stageState);
  TitleState* Start = new TitleState();
  game.Push(Start);
  // game.storedState = stageState;
  // game.Push(storedState);
  game.Run();//executa o game até a janela ser fechada
  // game.~Game();//desaloca a memória, destrói as janelas, etc
  return 0;

}
