#pragma once

#include <iostream>
// #include <SDL2/SDL.h>
#include "Vec2.hpp"

class Rect{
private:
public:

  float x;
  float y;
  float w;
  float h;

  Rect();
  Rect(float a, float b, float c, float d);
  bool Contains(float mouseX, float mouseY);
  Vec2 GetVec2();
  Vec2 GetCenter();

  void operator=(const Vec2& v);
  void operator+=(const Vec2& v);

};
