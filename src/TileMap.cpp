#include "../include/TileMap.h"
#include "../include/Camera.h"

TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet):Component(associated){

  if (tileSet != nullptr) {
    SetTileSet(tileSet);
    Load(file);
  } else {
    std::cout << "tileSet null" << std::endl;
  }

}

void TileMap::Load(std::string file){
  std::fstream map;
  map.open(file);
  int tile;

//Pega as primeiras três informações do arquivo que são a largura, a altura e a prifundidade do tilemap
  map >> mapWidth;
  map.seekg (1, map.cur);
  map >> mapHeight;
  map.seekg (1, map.cur);
  map >> mapDepth;
  map.seekg (1, map.cur);

//Nesse laço, percorre-se o resto do arquivo salvando todos os tiles no tilemap em um único vector
  for (int i = 0; i < (mapWidth*mapHeight*mapDepth); i++){
    map >> tile;
    tileMatrix.push_back(tile-1);
    map.seekg (1, map.cur);
  }
  map.close();
// std::cout << tileMatrix.size() << '\n';
}

void TileMap::SetTileSet(TileSet* tileSet){
  this->tileSet = tileSet;//seta o tileset
}

int& TileMap::At(int x, int y, int z = 0){//x é coluna, y é linha e z é profundidade
  //o cálculo é feito por linha + (tamanho da linha)*coluna + (área do tilemap)*profundidade
  return (tileMatrix[x + mapWidth*y + mapWidth*mapHeight*z]);
}

void TileMap::Render(){
  for (int z = 0; z < mapDepth; z++) {
    Camera::ParallaxUpdate(z, false);//Chamma a função que vai mudar a velocidade do objeto no jogo dependendo do layer
    RenderLayer(z, Camera::pos.x, Camera::pos.y);
    // RenderLayer(z, this->associated.box.x + Camera::pos.x, this->associated.box.y + Camera::pos.y);
    // RenderLayer(z, this->associated.box.x + Camera::pos.x*(1+z), this->associated.box.y + Camera::pos.y*(1+z)); Outra opção seria fazer desse jeito, mas manter uma função para calcular a mudança no layers pode se tornar útil mais para frente, caso alguma mudança na lógica seja necessária
    Camera::ParallaxUpdate(z, true);//Chama a função de novo para resetar os parâmetros originais
  }
}

void TileMap::RenderLayer(int layer, int cameraX = 0, int cameraY = 0){

  for (int i = 0; i < GetHeight(); i++) {
    for (int j = 0; j < GetWidth(); j++) {
      tileSet->RenderTile(At(j, i, layer), cameraX + tileSet->GetTileWidth()*j*tileSet->scale.x , cameraY + tileSet->GetTileHeight()*i*tileSet->scale.y);

    }
  }
}

int TileMap::GetWidth(){
  return mapWidth;
}

int TileMap::GetHeight(){
  return mapHeight;
}

int TileMap::GetDepth(){
  return mapDepth;
}

bool TileMap::Is(std::string type){
  if (type == "TileMap") {
    return true;
  } else {
    return false;
  }
}

void TileMap::Update(float dt){
}
