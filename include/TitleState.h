#pragma once

#define STATE
#include "MorphingMenace_include.h"
#include "Engine_include.h"
#include "State.h"
#include "Sprite.h"
#include "StageState.h"
#include "Text.h"
#include "Music.h"

// #define FONT_PATH "assets/font/Call me maybe.ttf"
// #define FONT_SIZE 60
// #define TITLE_TEXT "PRESS SPACEBAR TO BEGIN"
// #define TEXT_COLOR {0, 0, 100, 255}
// #define SCREEN_TIME 0.3

class TitleState : public State {

private:
  bool started;

public:

  TitleState();
  ~TitleState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
};
