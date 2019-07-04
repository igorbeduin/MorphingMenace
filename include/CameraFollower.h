#pragma once

#include "Component.h"
#include "Camera.h"

class Camera;
class CameraFollower : public Component{

private:
  Vec2 follow_offset = {0,0};

public:

  CameraFollower(GameObject& associated, Vec2 offset = {0,0});
  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
