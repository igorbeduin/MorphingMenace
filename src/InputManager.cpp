#include "../include/InputManager.h"
#include "../include/Camera.h"

InputManager::InputManager(){//inicializando todas a as variáveis

  for (int i = 0; i < 6; i++) {
    mouseUpdate[i] = 0;
    mouseState[i] = false;
  }
  quitRequested = false;
  updateCounter = 0;
  mouseX = 0;
  mouseY = 0;

}

InputManager::~InputManager(){
  keyState.clear();
  keyUpdate.clear();
}


void InputManager::Update(){
  SDL_Event event;

  updateCounter++;
  SDL_GetMouseState(&mouseX, &mouseY);
  // std::cout << - Camera::pos.x + mouseX << ", " << - Camera::pos.y + mouseY << std::endl;
  quitRequested = false;//se um State já tratou e resolveu não fechar o jogo (ainda), ou não se interessou evento de quit não for tratado por State no frame em que ocorreu, é porque

  while (SDL_PollEvent(&event)) {
    if (event.key.repeat != 1) {//evitar que eventos sejam repetidos
      switch (event.type) {

        case SDL_QUIT:// SDL_QUIT  Clique no X, Alt+F4, etc.
          quitRequested = true;
          break;

        case SDL_KEYDOWN:// SDL_KEYDOWN   Pressionamento de tecla
          keyState[event.key.keysym.sym] = true;
          keyUpdate[event.key.keysym.sym] = updateCounter;
          break;

        case  SDL_KEYUP:// SDL_KEYUP     Uma tecla foi solta
          keyState[event.key.keysym.sym] = false;
          keyUpdate[event.key.keysym.sym] = updateCounter;
          break;

        case SDL_MOUSEBUTTONDOWN:// SDL_MOUSEBUTTONDOWN Pressionamento de botão do mouse
          mouseState[event.button.button] = true;
          mouseUpdate[event.button.button] = updateCounter;
          // std::cout << "down" << '\n';
          break;

        case SDL_MOUSEBUTTONUP:// SDL_MOUSEBUTTONUP Botão do mouse foi solto
          mouseState[event.button.button] = false;
          mouseUpdate[event.button.button] = updateCounter;
          // std::cout << "up" << '\n';
          break;

        default:
          break;
      }
    }
  }
}


bool InputManager::KeyPress(int key){
  return (keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::KeyRelease(int key){
  return (!keyState[key] && keyUpdate[key] == updateCounter);
}

bool InputManager::IsKeyDown(int key){
  return keyState[key];
}


bool InputManager::MousePress(int key){
  return (mouseState[key] && (mouseUpdate[key] == updateCounter));
}

bool InputManager::MouseRelease(int key){
  return (!mouseState[key] && (mouseUpdate[key] == updateCounter));
}

bool InputManager::IsMouseDown(int key){
  return mouseState[key];
}


int InputManager::GetMouseX(){
  return mouseX;
}

int InputManager::GetMouseY(){
  return mouseY;
}


bool InputManager::QuitRequested(){
  return quitRequested;
}


InputManager& InputManager::GetInstance(){
  static InputManager input;
  return input;
}
