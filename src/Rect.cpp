#include <iostream>
#include <SDL2/SDL.h>
#include "../include/Rect.hpp"
Rect::Rect(){//inicializa o box como valores nulos
  this->x = 0;
  this->y = 0;
  this->w = 0;
  this->h = 0;
}
Rect::Rect(float a, float b, float c, float d){//inicializa o box com valores dados
  this->x = a;
  this->y = b;
  this->w = c;
  this->h = d;
}
bool Rect::Contains(float mouseX, float mouseY){

  if (mouseX >= this->x && mouseX <= (this->x+this->w) && mouseY >= this->y && mouseY <= (this->y+this->h)){
//verifica se o mouse está dentro da área que contem o inimigo, ou seja entre (x_inimigo) e (x_inimigo + largura )
// e entre (y_inimigo) e (y_inimigo+ altura)
    return true;
  } else {
    return false;
  }
}
Vec2 Rect::GetVec2(){
  return Vec2(this->x, this->y);
}
Vec2 Rect::GetCenter(){
  return Vec2(this->x + this->w/2, this->y + this->h/2);
}
void Rect::operator=(const Vec2& v){
  this->x = v.x;
  this->y = v.y;
}
void Rect::operator+=(const Vec2& v){
  this->x += v.x;
  this->y += v.y;
}
