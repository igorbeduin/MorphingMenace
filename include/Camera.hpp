#pragma once

#define CAMERA
#define WINDOW

#include "Engine_include.hpp"

#include "GameObject.hpp"
#include "Vec2.hpp"

class Camera{

private:

  static GameObject* focus;

public:

  static void Follow(GameObject* newFocus);
  static void Unfollow();
  static void Update(float dt);
  static void ParallaxUpdate(int layer, bool ParallaxEnd);

  static Vec2 pos;
  static Vec2 speed;
  static int Parallax_aux_x;
  static int Parallax_aux_y;
};
