#pragma once

#define SPRITE
#include "Engine_include.h"

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Character.h"

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

    bool ChangeAnimation;
    int StartFrame;
    int EndFrame;
    float AnimationTime;

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
    void SetScale(float scaleX, float scaleY);
    Vec2 GetScale();

    void SetFrame(int frame);
    void SetFrameCount(int frameCount);
    void SetFrameTime(float frameTime);
    int GetCurrentFrame();

    void SetStartFrame(int startFrame);
    void SetEndFrame(int endFrame);
    void SetAnimationTime(float animationTime);
    void RunSpecificAnimation();
};
