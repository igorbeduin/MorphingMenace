#include "../include/Camera.h"
#include "../include/InputManager.h"

GameObject *Camera::focus;
Vec2 Camera::pos;
Vec2 Camera::speed;
int Camera::Parallax_aux_x;
int Camera::Parallax_aux_y;

void Camera::Follow(GameObject *newFocus)
{
  focus = newFocus;
  // std::cout << "x " << focus->box.x <<" y " << focus->box.y << " w " <<focus->box.w <<" h " << focus->box.h << '\n';
}

void Camera::Unfollow()
{
  focus = nullptr;
  
}

void Camera::Update(float dt)
{
  InputManager &input = InputManager::GetInstance();

  if (focus != nullptr)
  {

    // pos = focus->box.GetCenter();
    // pos.x -= WINDOW_WIDTH/2 ;// A posição da câmera é o calculo da posição do objeto na tels
    // pos.y -= WINDOW_HEIGHT/2 ;

    // pos.x = -focus->box.x - focus->box.w/2 + WINDOW_WIDTH/2;
    // pos.y = -focus->box.y - focus->box.h/2 + WINDOW_HEIGHT/2;

    if (focus->box.x <= -pos.x + LEFT_FOCUS_LIMIT)
    {
      pos.x = -focus->box.x + LEFT_FOCUS_LIMIT;
    }
    else if (focus->box.x >= -pos.x + RIGHT_FOCUS_LIMIT)
    {
      pos.x = -focus->box.x + RIGHT_FOCUS_LIMIT;
    }

    if (focus->box.y >= -pos.y + DOWN_FOCUS_LIMIT)
    {
      pos.y = -focus->box.y + DOWN_FOCUS_LIMIT;
    }
    else if (focus->box.y <= -pos.y + UP_FOCUS_LIMIT)
    {
      pos.y = -focus->box.y + UP_FOCUS_LIMIT;
    }
  }
  else
  {

    if (input.IsKeyDown(LEFT_ARROW_KEY) && (speed.x <= MAX_CAM_SPEED_X))
    { //é definido uma velocidade máxima à qual a câmera pode acelerar
      speed.x += CAMERA_SPEED;
    }
    else if (input.IsKeyDown(RIGHT_ARROW_KEY) && (speed.x >= -MAX_CAM_SPEED_X))
    {
      speed.x -= CAMERA_SPEED;
    }
    else
    {

      if (speed.x > 0) //com essa lógica a movimentação nao para instantâneamente, mas a velocidade diminui gradativamente até 0
        speed.x -= CAMERA_SPEED;
      else if (speed.x < 0)
        speed.x += CAMERA_SPEED;
      else
        speed.x = 0;
    }

    if (input.IsKeyDown(DOWN_ARROW_KEY) && (speed.y >= -MAX_CAM_SPEED_Y))
    {
      speed.y -= CAMERA_SPEED;
    }
    else if (input.IsKeyDown(UP_ARROW_KEY) && (speed.y <= MAX_CAM_SPEED_Y))
    {
      speed.y += CAMERA_SPEED;
    }
    else
    {

      if (speed.y > 0) //com essa lógica a movimentação n~ao para instantâneamente, mas a velocidade diminui até 0
        speed.y -= CAMERA_SPEED;
      else if (speed.y < 0)
        speed.y += CAMERA_SPEED;
      else
        speed.y = 0;
    }
    pos.x += speed.x * dt;
    pos.y += speed.y * dt;
  }
}
void Camera::ParallaxUpdate(int layer, bool ParallaxEnd)
{

  if (!ParallaxEnd)
  { //A variaverl ParallaxEnd só serve para dizer se é antes ou depois da renderização da layer, por isso a função é chamada duas vezes, antes de renderizar para fazer a compensação que o parallax pede, e após a renderização feita para devolver a posição original à câmera
    //Salva a posição original de x e y antes do calculo do parallax
    Parallax_aux_x = pos.x;
    Parallax_aux_y = pos.y;
    //Calcula a compensação para a layer na câmera, fazendo com que layers diferentes se movam em velocidades diferentes
    pos.x = pos.x * (1 + layer);
    pos.y = pos.y * (1 + layer);
  }
  else
  {
    //Retorna a posição original para que seja usada em outras renderizações
    pos.x = Parallax_aux_x;
    pos.y = Parallax_aux_y;
  }
}