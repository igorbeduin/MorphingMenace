#include "../include/CameraFollower.hpp"

CameraFollower::CameraFollower(GameObject& associated)
                                              :Component(associated){
}

void CameraFollower::Update(float dt){

  associated.box.x = -Camera::pos.x - 2900;
  associated.box.y = -Camera::pos.y - 1300;

}

void CameraFollower::Render(){

}

bool CameraFollower::Is(std::string type){
  return (type == "CameraFollower");
}
