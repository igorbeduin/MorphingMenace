#pragma once

#define INCLUDE_SDL_MIXER

#include "Engine_include.h"
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.h"
#include "GameObject.h"


class Sound : public Component {

private:
  std::shared_ptr<Mix_Chunk> chunk;
  int channel;

public:
  Sound(GameObject& associated);
  Sound(GameObject& associated, std::string file);
  ~Sound();

  void Play(int times = 1);
  void Stop();
  void Open(std::string file);
  bool IsOpen();
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
