#pragma once


#include "Engine_include.h"

#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "Component.h"
#include "Rect.h"

class Component;

class GameObject{

private:
  std::vector< std::shared_ptr<Component> > components;
  bool isDead;
  bool moving;

public:

  GameObject();
  ~GameObject();

  void Start();
  void Update(float dt);
  void Render();
  bool IsDead();
  void RequestDelete();
  void AddComponent(std::shared_ptr<Component> cpt);
  void RemoveComponent(std::shared_ptr<Component> cpt);
  std::shared_ptr<Component> GetComponent(std::string type);

  void NotifyCollision(GameObject& other);
  bool IsMoving();
  double GetAngleRad();
  bool started;
  Rect box;
  double angleDeg;
};
