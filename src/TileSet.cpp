#include "../include/TileSet.h"
#include "../include/Game.h"

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file, Vec2 scale)
                                                                                         : tileSet(associated, file),
                                                                                           tileWidth(tileWidth),
                                                                                           tileHeight(tileHeight),
                                                                                           createMapColliders(false)
{ //classe que constrói o tileSet

  // this->tileWidth = tileWidth;//seta a largura do tile com a passada para a função
  // this->tileHeight = tileHeight;//seta a largura do tile com qa passada para a função
  // tileSet.Open(file);//Abre o tileset

  if (tileSet.IsOpen()) {
    columns = tileSet.GetWidth()/tileWidth;
    rows = tileSet.GetHeight()/tileHeight;
  } else {
    std::cout << "can't open tileset" << '\n';
    rows = 0;
    columns = 0;
  }

  this->scale = scale;
  // this->tileWidth = tileWidth*scale.x;
  // this->tileHeight = tileHeight*scale.y;

  tileSet.SetScale(scale.x, scale.y);
  //calcula o número de linhas colunas do tileset sado o tamnho dado pela função sprite

}/////////////////////////lista de inicialização?

void TileSet::RenderTile(unsigned index, float x, float y){

  if(  (index < (unsigned)(columns*rows)) ){
    tileSet.SetClip((index%columns)*GetTileWidth(), (index/(columns))*GetTileHeight(), GetTileWidth(), GetTileHeight());//verificar conta
    tileSet.Render(x, y);
  }

  if (createMapColliders == true)
  {
    GameObject* tile = new GameObject();
    tile->box.x = x;
    tile->box.y = y;
    tile->box.w = GetTileWidth()*scale.x;
    tile->box.h = GetTileHeight()*scale.y;

    std::shared_ptr<Collider> collider(new Collider(* tile));
    tile->AddComponent(collider);
    std::shared_ptr<CollisionBox> boxBehaviour(new CollisionBox(* tile));
    tile->AddComponent(boxBehaviour);

    Game::GetInstance().GetCurrentState().AddObject(tile);

    createMapColliders = false;
  }
}

int TileSet::GetTileWidth(){
  return tileWidth;
}

int TileSet::GetTileHeight(){
  return tileHeight;
}
