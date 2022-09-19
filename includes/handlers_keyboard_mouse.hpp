#ifndef __HANDLER_KEYBOARD_MOUSE_HEADER__
#define __HANDLER_KEYBOARD_MOUSE_HEADER__

#include <GLFW/glfw3.h>

#define MOUSE_MOVE_LEFT 0x10
#define MOUSE_MOVE_RIGHT 0x10 >> 1
#define MOUSE_MOVE_UP 0x10 >> 2
#define MOUSE_MOVE_DOWN 0x10 >> 3


typedef unsigned int MOUSE_MOVE_FLAG;
typedef void (*CALLBACK_FUNC )(...);

namespace keyboard_mouse{
    static double lastMouseX = 0.0,
                  lastMouseY = 0.0,
                  deltaMouseX = 0.0,
                  deltaMouseY = 0.0;
                  
}


void cursor_position_callback(GLFWwindow* glWindow, double mouseX, double mouseY);
void mouse_button_callback(GLFWwindow* glWindow, int button, int action, int mods);
void manage_keyboard_mouse(GLFWwindow* glWindow);
void mouse_scroll_callback(GLFWwindow* glWindow, double offsetx, double offsety);
MOUSE_MOVE_FLAG getMouseDirection();

#endif // header guard
