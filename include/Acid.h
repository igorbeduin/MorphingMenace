#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Sprite.h"
#include "Sound.h"
#include "macros/Acid_include.h"

class Minion;

class Acid : public Component {

private:

  Vec2 speed;
  float distanceLeft;
  int damage;

public:

  Acid(GameObject& associated, float angle, float speed);

  void Update(float dt);
  void Render();
  bool Is(std::string type);
  int GetDamage();
//   void NotifyCollision(GameObject& other);
    Timer AcidTime;

  bool targetsPlayer;

};
