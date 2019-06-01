#pragma once

#define INCLUDE_SDL
#include "SDL_include.h"

#include <unordered_map>
#include <iostream>
// #include <SDL2/SDL.h>


#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d
#define ENTER_KEY SDLK_KP_ENTER
#define TAB_KEY SDLK_TAB

class InputManager{

public:
  InputManager();
  ~InputManager();

  void Update();

  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);

  bool MousePress(int key);
  bool MouseRelease(int key);
  bool IsMouseDown(int key);

  int GetMouseX();
  int GetMouseY();

  bool QuitRequested();

  static InputManager& GetInstance();

private:
  bool mouseState[6];
  int mouseUpdate[6];

  std::unordered_map<int, bool> keyState;
  std::unordered_map<int, int> keyUpdate;

  bool quitRequested;

  int updateCounter;

  int mouseX, mouseY;

protected:

};
