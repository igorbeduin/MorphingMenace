#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE

#include "SDL_include.h"

#include "GameObject.h"
#include "Timer.h"

class Sprite: public Component{//implementar update, is e render da classe mãe (component)

  private:
    std::shared_ptr<SDL_Texture> texture;
    SDL_Rect clipRect;
    Vec2 scale;

    int width;
    int height;

    int frameCount;
    int currentFrame;
    float timeElapsed;
    float frameTime;

    Timer selfDestructCount;
    float secondsToSelfDestruct;

  public:
    Sprite(GameObject& associated);
    Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1, float secondsToSelfDestruct = 0);
    ~Sprite();

    void Open(std::string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(int x, int y);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
    bool Is(std::string type);
    void Update(float dt);
    void SetScaleX(float scaleX, float scaleY);
    Vec2 GetScale();

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
};
