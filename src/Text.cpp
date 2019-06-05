#include "../include/Text.h"
#include "../include/Camera.h"
#include "../include/Game.h"
#include "../include/Resources.h"

Text::Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float screenTime, SDL_Color bgcolor):Component(associated){

  this->fontFile = fontFile;
  this->fontSize = fontSize;
  this->style = style;
  this->text = text;
  this->color = color;
  this->bgcolor = bgcolor;
  this->screenTime = screenTime;
  texture = nullptr;
  font = nullptr;

  RemakeTexture();
}

Text::~Text(){

  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
}

void Text::Update(float dt){
  if (screenTime > 0) {
    if (OnOff.Get() > screenTime) {
      OnOff.Restart();
    }
    else {
      OnOff.Update(dt);
    }
  }
}

void Text::Render(){

  int RenderError;

  if (screenTime > 0) {
    if (OnOff.Get() > screenTime) {
      (onScreen%2 == 0 ) ? (onScreen++) : (onScreen--);
    }
    if (onScreen == 1) {
      SDL_Rect clipRect = {0,0, (int)associated.box.w, (int)associated.box.h};
      SDL_Rect dstrect = {(int)associated.box.x + (int)Camera::pos.x, (int)associated.box.y + (int)Camera::pos.y, clipRect.w, clipRect.h};

      RenderError = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
      if (RenderError != 0) {
        std::cout << "Failed to Render Texture, error code: " << SDL_GetError() <<", texture = " << texture << std::endl;
      }
    }

  }
  else if (screenTime == 0) {
    SDL_Rect clipRect = {0,0, (int)associated.box.w, (int)associated.box.h};
    SDL_Rect dstrect = {(int)associated.box.x + (int)Camera::pos.x, (int)associated.box.y + (int)Camera::pos.y, clipRect.w, clipRect.h};

    RenderError = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
    if (RenderError != 0) {
      std::cout << "Failed to Render Texture, error code: " << SDL_GetError() <<", texture = " << texture << std::endl;
    }
  }

  // int RenderError;
  // SDL_Rect clipRect = {0,0, (int)associated.box.w, (int)associated.box.h};
  // SDL_Rect dstrect = {(int)associated.box.x + (int)Camera::pos.x, (int)associated.box.y + (int)Camera::pos.y, clipRect.w, clipRect.h};
  //
  // RenderError = SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
  // if (RenderError != 0) {
  //   std::cout << "Failed to Render Texture, error code: " << SDL_GetError() <<", texture = " << texture << std::endl;
  // }
}

bool Text::Is(std::string type){
  return (type == "Text");
}

void Text::SetText(std::string text){
  this->text = text;
  RemakeTexture();
}

void Text::SetColor(SDL_Color color){
  this->color = color;
  RemakeTexture();

}

void Text::SetBGColor(SDL_Color bgcolor){
  this->bgcolor = bgcolor;
  RemakeTexture();

}

void Text::SetStyle(TextStyle style){
  this->style = style;
  RemakeTexture();

}

void Text::SetFontFile(std::string fontFile){
  this->fontFile = fontFile;
  RemakeTexture();

}

void Text::SetFontSize(int fontSize){
  this->fontSize = fontSize;
  RemakeTexture();

}

void Text::SetScreenTime(float screenTime){
  this->screenTime = screenTime;
}

void Text::RemakeTexture(){

  SDL_Surface* surface = nullptr;

  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  font = Resources::GetFont(fontFile, fontSize);

  if (font == nullptr){
      std::cout << "Error returning font, Error code: "<< SDL_GetError() << std::endl;
  }
  else {
    switch (style) {

      case SOLID:
        surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
        if (surface == nullptr) {
          std::cout << "Error rendering text"<< SDL_GetError() << std::endl;
        }
      break;

      case SHADED:
        surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, bgcolor);
        if (surface == nullptr) {
          std::cout << "Error rendering text"<< SDL_GetError() << std::endl;
        }
      break;

      case BLENDED:
      surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
      if (surface == nullptr) {
        std::cout << "Error rendering text"<< SDL_GetError() << std::endl;
      }
      break;
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    associated.box.w = surface->w;
    associated.box.h = surface->h;
    SDL_FreeSurface(surface);
    // SDL_QueryTexture(texture, nullptr, nullptr, &associated.box.w, &height);//obtém os parâmetros (dimensões) da imagem e armazena-os nos espaçços indicados nos argumentos

  }


}
