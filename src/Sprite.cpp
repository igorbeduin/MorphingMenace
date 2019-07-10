#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"
#include "../include/Sprite.h"

Sprite::Sprite(GameObject &associated) : Component(associated),
                                         blendMode(SDL_BLENDMODE_NONE)
{//seta texture como nullptr (imagem não carregada)
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
  SDL_GetTextureBlendMode(texture.get(), &blendMode);
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

  SDL_RendererFlip flip = SDL_FLIP_NONE;

  if (associated.GetComponent("Character").get() != nullptr)
  {
    Character* temp = (Character*)associated.GetComponent("Character").get();
    if (temp->IsFlipped())
    {
      flip = SDL_FLIP_HORIZONTAL;
    }
  }
  SDL_SetTextureBlendMode(texture.get(), blendMode);
  RenderError = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstrect, associated.angleDeg, nullptr, flip);
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

void Sprite::Update(float dt)
{
  if (!ChangeAnimation)
  {
    if (secondsToSelfDestruct > 0)
    {
      selfDestructCount.Update(dt);
      if (selfDestructCount.Get() >= secondsToSelfDestruct)
      {
        associated.RequestDelete();
        // std::cout << "fim da explosão" << '\n';
      }
    }

    if (frameCount > 1 && associated.IsMoving())
    {
      timeElapsed += dt;
      if (timeElapsed >= frameTime)
      {//se o tempo passado for maior que o tempo em que o frame deve permanecer, muda o frame
        timeElapsed = 0;
        currentFrame += 1;//se não for o último vai para o próximo frame
        if (frameCount == currentFrame)
        {
          currentFrame = 0; //se o frame atual foir o último, retorna para o fram inicial
        }
        SetClip(  (width/frameCount)*(currentFrame) , clipRect.y, width/frameCount, height);
      }
    }
  } else {
    // std::cout << currentFrame << std::endl;
    if (currentFrame <= EndFrame)
    {
      timeElapsed += dt;
      if (timeElapsed >= AnimationTime)
      {//se o tempo passado for maior que o tempo em que o frame deve permanecer, muda o frame
        // std::cout << "current: " << currentFrame << std::endl;
        // std::cout << "Start: " << StartFrame << std::endl;
        // std::cout << "End: " << EndFrame << std::endl;
        SetClip(  (width/frameCount)*(currentFrame) , clipRect.y, width/frameCount, height);
        timeElapsed = 0;
        currentFrame += 1;//se não for o último vai para o próximo frame
      }
    }
    else if (currentFrame > EndFrame)//para chamar essa animação, na função em que for necessária a mudança faça um GetComponent(sprite) e então deve-se chamar o RunSpecificAnimation para setar a flag que permite esse loop, então setar os parâmetros StartFrame, EndFrame e AnimationTime
    {
      ChangeAnimation = false;
    }
    if (currentFrame < StartFrame)
    {
      ChangeAnimation = false;
    }
    
  }
}

void Sprite::SetScale(float scaleX, float scaleY){

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
  if (frame <= frameCount) {
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

int Sprite::GetCurrentFrame()
{
  return currentFrame;
}

void Sprite::SetStartFrame(int startFrame)
{
  if (this->StartFrame != startFrame)
  {
    this->StartFrame = startFrame;
    currentFrame = startFrame;
  }
}

void Sprite::SetEndFrame(int endFrame)
{
  if (this->EndFrame != endFrame)
  {
    this->EndFrame = endFrame;
  }
}

void Sprite::SetAnimationTime(float animationTime)
{
  this->AnimationTime = animationTime;
}

void Sprite::RunSpecificAnimation()
{
  if (!this->ChangeAnimation)
  {//se essa função é chamada e a condição era falsa, quer dizer que é o primeira vez que a animação vai ser executada, logo o currentframe tem que ser o start frame e o timeelapsed deve ser 0
    currentFrame = StartFrame;
    timeElapsed = 0;
  }
  this->ChangeAnimation = true;
}
        // PARA CHAMAR A ANIMAÇÂO 
        // Sprite *enemySprite = (Sprite *)associated.GetComponent("Sprite").get();
        //     enemySprite->RunSpecificAnimation();
        //     enemySprite->SetStartFrame(ENTOKRATON_1_IDLE_START);
        //     enemySprite->SetEndFrame(ENTOKRATON_1_IDLE_END);
        //     enemySprite->SetAnimationTime(ENTOKRATON_1_IDLE_TIME);

void Sprite::SetBlendMode(SDL_BlendMode blendMode)
{
  this->blendMode = blendMode;
}