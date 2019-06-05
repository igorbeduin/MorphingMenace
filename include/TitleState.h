#pragma once

#include "State.h"
#include "Sprite.h"
#include "StageState.h"
#include "Text.h"

#define TITLE_PATH "assets/img/title.jpg"
#define FONT_PATH "assets/font/Call me maybe.ttf"
#define FONT_SIZE 60
#define TITLE_TEXT "PRESS SPACEBAR TO BEGIN"
#define TEXT_COLOR {0, 0, 100, 255}
#define SCREEN_TIME 0.3

class TitleState : public State {

private:

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
