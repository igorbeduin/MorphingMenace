#pragma once

#include "MorphingMenace_include.h"
#include "Engine_include.h"

#include "State.h"
#include "Music.h"
#include "TileSet.h"

class StageState : public State {

private:

  TileSet* tileSet;
  Music backgroundMusic;

public:

  StageState();
  ~StageState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
};
