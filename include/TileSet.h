#pragma once

#include "CollisionBox.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Collider.h"

class TileSet{

private:

  Sprite tileSet;

  int rows;
  int columns;
  int tileWidth;
  int tileHeight;

public:
  TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file, Vec2 scale = {1,1});

  void RenderTile(unsigned index, float x, float y);
  int GetTileWidth();
  int GetTileHeight();
  Vec2 scale;
  bool createMapColliders;

};
