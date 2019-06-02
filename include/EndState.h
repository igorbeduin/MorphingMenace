#pragma once

#include "Music.h"
#include "State.h"

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
