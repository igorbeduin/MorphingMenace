#pragma once

#include "State.hpp"
#include "Sprite.hpp"
#include "StageState.hpp"
#include "Text.hpp"

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
