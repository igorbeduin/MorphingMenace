#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"
#include "Engine_include.h"
#include "MorphingMenace_include.h"

#include <stack>
#include <iostream>
#include <string>
#include <memory>

#include "State.h"


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
