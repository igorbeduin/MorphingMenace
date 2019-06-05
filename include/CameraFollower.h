#pragma once

#include "Component.h"
#include "Camera.h"

class Camera;
class CameraFollower : public Component{

private:

public:

  CameraFollower(GameObject& associated);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
};
