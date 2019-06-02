#pragma once

#include "Sprite.h"

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

};
