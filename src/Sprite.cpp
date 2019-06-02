#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"
#include "../include/Sprite.h"

Sprite::Sprite(GameObject& associated) : Component(associated){//seta texture como nullptr (imagem não carregada)
  texture = nullptr;
  currentFrame = 0;
  timeElapsed = 0;
  frameTime = 1;
  frameCount = 1;

  scale = Vec2(1,1);
  width = 0;
  height = 0;

  secondsToSelfDestruct = 0;
}

Sprite::Sprite(GameObject& associated, std::string file, int frameCount, float frameTime, float secondsToSelfDestruct):Component(associated) {//seta texture como nullptr e em seguida chama Open para abrir uma imagem
  texture = nullptr;
  scale = Vec2(1,1);
  width = 0;
  height = 0;

  currentFrame = 0;
  timeElapsed = 0;
  this->frameCount = frameCount;
  this->frameTime = frameTime;
  this->secondsToSelfDestruct = secondsToSelfDestruct;

  Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(std::string file){//carrega a imagem indicada pelo caminho file

  texture = Resources::GetImage(file);

  if (texture == nullptr){
      std::cout << "Error returning texture, Error code: "<< SDL_GetError() << std::endl;//caso o IMG_LoadTexture retorne nullptr (erro comum)
  }
  else {
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);//obtém os parâmetros (dimensões) da imagem e armazena-os nos espaçços indicados nos argumentos
  }
  // width = width/frameCount;
  SetClip(0, 0, width/frameCount, height);//seta o clip com as dimensões da imagem
  associated.box.w = width/frameCount;//seta o tamanho e a largura do goameobject associado com aqueles setados pelas funções anteriores
  associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h){// seta o clip com os parâmetros sasos
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Render(){//chama o render utilizando o associated como argumento
  Render(associated.box.x + Camera::pos.x, associated.box.y + Camera::pos.y);
}

void Sprite::Render(int x, int y){// wrapper para a SDL_RenderCopy que possui quatro argumentos
  SDL_Rect dstrect;// um dos parâmetros de RenderCOpy, é o retâncgulo de destino, determina a posição da tela em que a textura será renderizada,
  // se a altura e largura forem diferentes da original, há uma mudança de escala da imagem
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w*scale.x;
  dstrect.h = clipRect.h*scale.y;
  int RenderError;

  RenderError = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
  if (RenderError != 0) {
    std::cout << "Failed to Render Texture, error code: " << SDL_GetError() <<", texture = " << texture << std::endl;
  }
}

int Sprite::GetWidth(){//retorna a largura da imagem
  return width*scale.x/frameCount;
}
int Sprite::GetHeight(){//retorna a altura da imagem
  return height*scale.y;
}

bool Sprite::IsOpen(){//verifica se a imagem foi aberta
  if (texture == nullptr) {
    return false;
  }
  else {
    return true;
  }
}

bool Sprite::Is(std::string type){
  return(type == "Sprite");
}

void Sprite::Update(float dt){


  if (secondsToSelfDestruct > 0) {
    selfDestructCount.Update(dt);
    if (selfDestructCount.Get() >= secondsToSelfDestruct) {
      associated.RequestDelete();
      // std::cout << "fim da explosão" << '\n';
    }
  }

  if (frameCount > 1) {
    timeElapsed += dt;
    if (timeElapsed >= frameTime) {//se o tempo passado for maior que o tempo em que o frame deve permanecer, muda o frame
      timeElapsed = 0;
      currentFrame += 1;//se não for o último vai para o próximo frame
      if (frameCount == currentFrame) {
        currentFrame = 1; //se o frame atual foir o último, retorna para o fram inicial
      }
      SetClip(  (width/frameCount)*(currentFrame) , clipRect.y, width/frameCount, height);
    }
  }
}

void Sprite::SetScaleX(float scaleX, float scaleY){

  if (scaleX > 0 ){
    scale.x = scaleX;
    associated.box.w = GetWidth();
  }
  if (scaleY > 0) {
    scale.y = scaleY;
    associated.box.h = GetHeight();
  }

}

Vec2 Sprite::GetScale(){
  return scale;
}

void Sprite::SetFrame(int frame){
  if (frame <= frameCount && frame > 0) {
    currentFrame = frame;
    SetClip(  (width/frameCount)*currentFrame , 0, width/frameCount, height);
  }
}

void Sprite::SetFrameCount(int frameCount){
  if (frameCount > 0) {
    this->frameCount = frameCount;
    associated.box.w = width/frameCount;
    SetClip(0 , 0, width/frameCount, height);
  }
}

void Sprite::SetFrameTime(float frameTime){
  this->frameTime = frameTime;
  timeElapsed = 0;
}
