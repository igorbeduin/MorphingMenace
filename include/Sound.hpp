#pragma once

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include <iostream>
#include <string>

#include "Component.hpp"
#include "GameObject.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>


class Sound : public Component {

private:
  // Mix_Chunk* chunk;
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
