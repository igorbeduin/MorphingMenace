#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER

#include <iostream>
#include <memory>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>
#include "SDL_include.h"

class Music{

private:
  std::shared_ptr<Mix_Music> music;

public:

  Music();
  Music(std::string file);
  ~Music();

  void Play(int times = -1);
  void Stop(int msToStop = 1500);
  void Open(std::string file);
  bool IsOpen();
};
