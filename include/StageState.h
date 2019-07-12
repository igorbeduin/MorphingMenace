#pragma once

#define CHARACTER
#define STATE
#define ENVIRONMENT
#include "MorphingMenace_include.h"
#include "Engine_include.h"

#include "GUI.h"
#include "Collider.h"
#include "State.h"
#include "Music.h"
#include "TileSet.h"
#include "EndState.h"
#include "Ocean.h"

class StageState : public State {

private:

  TileSet* tileSet;
  Music backgroundMusic;
  std::vector<std::shared_ptr<GameObject>> collisionObjectsArray;
  Ocean ocean;
  

public:

  StageState();
  ~StageState();

  void LoadAssets();
  void Update(float dt);
  void Render();

  void Start();
  void Pause();
  void Resume();
  std::weak_ptr<GameObject> AddCollisionObject(GameObject *object);
};
