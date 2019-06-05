#pragma once

#define JOYSTICK
#define INCLUDE_SDL

#include "SDL_include.h"
#include "Engine_include.h"

#include <unordered_map>
#include <iostream>

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
