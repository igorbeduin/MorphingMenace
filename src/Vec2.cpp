#include "../include/Vec2.hpp"

Vec2::Vec2(){
  this->x = 0;
  this->y = 0 ;
}

Vec2::Vec2(float a, float b){
  this->x = a;
  this->y = b;
}
void Vec2::Rotate(float angle){
  float temp_x;
  float temp_y;
  temp_x = this->x*cos(angle) - this->y*sin(angle);
  temp_y = this->y*cos(angle) - this->x*sin(angle);

  this->x = temp_x;
  this->y = temp_y;
}
Vec2 Vec2::GetRotated(float angle){
  this->Rotate(angle);
  return *(this);
}
Vec2 Vec2::Normalize(){
  return Vec2(this->x/this->Absolute(), this->y/this->Absolute());
}

float Vec2::Absolute(){
  return (sqrt(this->x*this->x + this->y*this->y));
}

Vec2 Vec2::operator+(const Vec2& v) {
  Vec2 sum;
  sum.x = this->x + v.x;
  sum.y = this->y + v.y;

  return (sum);
}

Vec2 Vec2::operator-(const Vec2& v) {
  Vec2 dif;
  dif.x = this->x - v.x;
  dif.y = this->y - v.y;

  return (dif);
}
Vec2 Vec2::operator*(const Vec2& v){
  Vec2 prod;
  prod.x = this->x*v.x;
  prod.y = this->y*v.y;
  return (prod);
}
Vec2 Vec2::operator/(const Vec2& v){
  Vec2 divs;
  divs.x = this->x/v.x;
  divs.y = this->y/v.y;

  return (divs);
}
Vec2 Vec2::operator*(float mult) {
  Vec2 prod;
  prod.x = this->x*mult;
  prod.y = this->y*mult;

  return (prod);
}
Vec2 Vec2::operator/(float divs){
  Vec2 res;
  res.x = this->x/divs;
  res.y = this->y/divs;

  return (res);
}
void Vec2::operator+=(const Vec2& v){
  this->x += v.x;
  this->y += v.y;
}
