#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
// #include <SDL2/SDL.h>
// #include <SDL_include.h>
// #include <SDL2/SDL_ttf.h>
#include <stack>
#include <iostream>
#include <string>
#include <memory>

#include "SDL_include.h"
#include "State.hpp"
// #include "StageState.hpp"
// #include "Resources.hpp"
// #include "TitleState.hpp"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#define MIX_CHUNKSIZE 1024
#define AUDIO_CHANNELS 32

class State;
class Resources;

class Game{

  private:

    int frameStart;
    float dt;

    static Game* instance;

    State* storedState;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::stack< std::unique_ptr<State> > stateStack;

    void CalculateDeltaTime();

  public:

    Game (std::string title, int width, int height);
    ~Game();

    static Game& GetInstance();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();

    void Push(State* state);
    void Run();
    float GetDeltaTime();


};
