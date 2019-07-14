#include "../include/Window.h"
#include "../include/Camera.h"
#include "../include/Rect.h"

Rect Window::window;

void Window::SetWindow()
{
    window.x = -Camera::pos.x;
    window.y = -Camera::pos.y;
    window.h = WINDOW_HEIGHT;
    window.w = WINDOW_WIDTH;
}
void Window::UpdateWindow()
{
    window.x = -Camera::pos.x;
    window.y = -Camera::pos.y;
}
