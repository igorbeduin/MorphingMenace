#include "../include/TileSet.hpp"
// #include "../include/Sprite.hpp"
// TileSet::TileSet():tileSet{
// }

TileSet::TileSet(GameObject& associated, int tileWidth, int tileHeight, std::string file, Vec2 scale)
                                                                                         : tileSet(associated, file),
                                                                                           tileWidth(tileWidth),
                                                                                           tileHeight(tileHeight){ //classe que constrói o tileSet

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

  tileSet.SetScaleX(scale.x, scale.y);
  //calcula o número de linhas colunas do tileset sado o tamnho dado pela função sprite

}/////////////////////////lista de inicialização?

void TileSet::RenderTile(unsigned index, float x, float y){

  if(  (index < (unsigned)(columns*rows)) ){
    tileSet.SetClip((index%columns)*GetTileWidth(), (index/(columns))*GetTileHeight(), GetTileWidth(), GetTileHeight());//verificar conta
    tileSet.Render(x, y);
  }
}

int TileSet::GetTileWidth(){
  return tileWidth;
}

int TileSet::GetTileHeight(){
  return tileHeight;
}
