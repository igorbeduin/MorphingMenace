#pragma once


#define STATE
#include "MorphingMenace_include.h"
#include "Engine_include.h"
#include "State.h"
#include "Sprite.h"
#include "StageState.h"
#include "TitleState.h"
#include "Text.h"
#include "Music.h"

// #define VICTORY_MSG "PRESS SPACEBAR TO PLAY AGAIN"
// #define DEFEAT_MSG "PRESS SPACEBAR FOR REVENGE"
// #define VICTORY_MUSIC "assets/audio/endStateWin.ogg"
// #define DEFEAT_MUSIC "assets/audio/endStateLose.ogg"

// #define DEFEAT_COLOR {255, 0, 30, 255}
// #define INSTRUCTION_MSG "PRESS ESC TO LEAVE THE GAME"

// #define FONT_PATH "assets/font/Call me maybe.ttf"
// #define END_FONT_SIZE 40
// #define END_SCREEN_TIME 1

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
