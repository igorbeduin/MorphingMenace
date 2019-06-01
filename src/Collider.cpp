#include "../include/Collider.hpp"

// #define DEbu
#ifdef DEBUG
#include "Camera.hpp"
#include "Game.hpp"

#include <SDL2/SDL.h>
#endif // DEBUG

#define PI 3.14159265359

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset):Component(associated){
  this->scale = scale;
  this->offset = offset;

  this->box.w = associated.box.w*scale.x;//multiplica a largura e a altura pela escala
  this->box.h = associated.box.h*scale.y;
}

void Collider::Update(float dt){

  this->box.x = associated.box.x + associated.box.w/2 - this->box.w/2;//realinha o centro da box do collider com a do associated
  this->box.y = associated.box.y + associated.box.h/2 - this->box.h/2;
  // std::cout << this->box.x << '\n';

  offset.Rotate(associated.angleDeg*PI/180);//rotaciona o offset com o mesmo angulo do associated

  this->box.x += offset.x;//soma o offset à box do collider
  this->box.y += offset.y;

  // box.x += offset.GetRotated(associated.angleDeg*PI/180).x;
  // box.y += offset.GetRotated(associated.angleDeg*PI/180).y;
  // std::cout << this->box.x << '\n';

}
void Collider::Render(){
  #ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( -associated.angleDeg/(180/PI) )	+ center + Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( -associated.angleDeg/(180/PI) ) + center + Camera::pos;
	points[1] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( -associated.angleDeg/(180/PI) ) + center + Camera::pos;
	points[2] = {(int)point.x, (int)point.y};

	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( -associated.angleDeg/(180/PI) ) + center + Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

  int temp = points[0].x;
  points[0].x = points[3].x;
  points[3].x = temp;
  points[4].x = points[0].x;

  temp = points[1].x;
  points[1].x = points[2].x;
  points[2].x = temp;


	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
  #endif // DEBUG

}
bool Collider::Is(std::string type){
  return (type == "Collider");
}
void Collider::SetScale(Vec2 scale){
  this->scale = scale;

  this->box.w = associated.box.w*scale.x;
  this->box.h = associated.box.h*scale.y;
}
void Collider::SetOffset(Vec2 offset){
  this->offset = offset;
}
