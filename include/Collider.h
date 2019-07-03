#pragma once

#define INCLUDE_SDL
#define MATH
// #define DEBUG

#include "SDL_include.h"
#include "Engine_include.h"

#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#endif // DEBUG

#include "Component.h"
#include "Collision.h"

class Collider : public Component {

private:

  Vec2 scale;
  Vec2 offset;

public:

  Collider(GameObject& associated, Vec2 scale = Vec2(1,1), Vec2 offset = {0,0} );

  Rect box;

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  void SetScale(Vec2 scale);
  void SetOffset(Vec2 offset);
};
