/************************************************
*					Math						*
*************************************************/
#define PI 3.14159265359
#define DEGtoRAD PI / 180
#define RADtoDEG 180 / PI

/************************************************
*					Window						*
*************************************************/
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

/************************************************
*				 Camera					*
*************************************************/
#define CAMERA_SPEED 100
#define MAX_CAM_SPEED_X 300
#define MAX_CAM_SPEED_Y 300
#define LEFT_FOCUS_LIMIT 342
#define RIGHT_FOCUS_LIMIT 482 

/************************************************
*				 Audio					*
*************************************************/
#define MIX_CHUNKSIZE 1024
#define AUDIO_CHANNELS 32
#define EMPTY_CHANNEL -1

/************************************************
*				 Joystick					*
*************************************************/
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d
#define ENTER_KEY SDLK_KP_ENTER
#define TAB_KEY SDLK_TAB

/************************************************
*				 Sprite					*
*************************************************/
#ifdef SPRITE
#include "GameObject.h"
#include "Timer.h"
#endif

/************************************************
*				 Character					*
*************************************************/
#ifdef CHARACTER
#include <string>
#include <iostream>

#include "Sprite.h"
#include "Component.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Rect.h"
#endif
