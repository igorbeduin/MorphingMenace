#include "../include/CameraFollower.h"

CameraFollower::CameraFollower(GameObject& associated, Vec2 follow_offset)
                                              :Component(associated){
  this->follow_offset = follow_offset;
}

void CameraFollower::Update(float dt){

  associated.box.x = -Camera::pos.x + follow_offset.x;
  associated.box.y = -Camera::pos.y + follow_offset.y;
}

void CameraFollower::Render(){

}

bool CameraFollower::Is(std::string type){
  return (type == "CameraFollower");
}
