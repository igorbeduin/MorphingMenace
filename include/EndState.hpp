#pragma once

#include "State.hpp"
#include "StageState.hpp"
#include "TitleState.hpp"
#include "Sprite.hpp"
#include "Music.hpp"
#include "Text.hpp"
#include "Game.hpp"

#define VICTORY_PATH "assets/img/win.jpg"
#define VICTORY_MSG "PRESS SPACEBAR TO PLAY AGAIN"
#define VICTORY_MUSIC "assets/audio/endStateWin.ogg"

#define DEFEAT_PATH "assets/img/lose.jpg"
#define DEFEAT_MSG "PRESS SPACEBAR FOR REVENGE"
#define DEFEAT_MUSIC "assets/audio/endStateLose.ogg"

#define INSTRUCTION_MSG "PRESS ESC TO LEAVE THE GAME"

#define TITLE_PATH "assets/img/title.jpg"
#define FONT_PATH "assets/font/Call me maybe.ttf"
#define END_FONT_SIZE 40
#define END_SCREEN_TIME 1




class EndState : public State {

private:

  Music backgroundMusic;

public:

  EndState();
  ~EndState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
};
