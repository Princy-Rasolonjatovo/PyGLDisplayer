#include <stdio.h>
#include "handlers_keyboard_mouse.hpp"
#include "viewport.hpp"


void 
mouse_button_callback(GLFWwindow* glWindow, int button, int action, int mods){
    using namespace keyboard_mouse;
    if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE){
        lastMouseX = lastMouseY = deltaMouseX = deltaMouseY = 0.0;
    }   
}


void 
cursor_position_callback(GLFWwindow* glWindow, double mouseX, double mouseY){
    using namespace keyboard_mouse;
    deltaMouseX = lastMouseX - mouseX;
    deltaMouseY = lastMouseY - mouseY;
    lastMouseX = mouseX;
    lastMouseY = mouseY;
    
    // Orbiting
    int mouseState = glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_MIDDLE);
    if (mouseState == GLFW_PRESS){
        MOUSE_MOVE_FLAG mouseDirection = getMouseDirection();
        glm::vec3 rotAxis(0, 0, 0);

        if (mouseDirection & MOUSE_MOVE_DOWN){
            printf("[MouseEvent] MOVE DOWN\n");
            
        }
        if (mouseDirection & MOUSE_MOVE_UP){
            printf("[MouseEvent] MOVE UP\n");
        }
        if (mouseDirection & MOUSE_MOVE_LEFT){
            printf("[MouseEvent] MOVE LEFT\n");
            rotAxis = glm::vec3(0, 1, 0);
            //viewport_vars::rotationAngle++;
            //printf("rotation angle : %d\n", viewport_vars::rotationAngle);
            //viewport_vars::rotationAngle = viewport_vars::rotationAngle > 360 ? 0 : viewport_vars::rotationAngle;
            // rotate_camera(viewport_vars::rotationAngle, rotAxis, viewport_vars::cameraPosition);
            // viewport_vars::View = glm::lookAt(
            //     viewport_vars::cameraPosition,
            //     viewport_vars::cameraEyeLook,
            //     viewport_vars::cameraVecNormal);
        }
        if (mouseDirection & MOUSE_MOVE_RIGHT){
            printf("[MouseEvent] MOVE RIGHT\n");
        }
        else{

        }
    }

}


void 
manage_keyboard_mouse(GLFWwindow* glWindow){
    glfwSetCursorPosCallback(glWindow, cursor_position_callback);
    glfwSetMouseButtonCallback(glWindow, mouse_button_callback);
    glfwSetScrollCallback(glWindow, mouse_scroll_callback);
}

void mouse_scroll_callback(GLFWwindow* glWindow, double offsetx, double offsety){
    // offsety < 0 : zoom out
    // offsety > 0 : zoom in
    if (offsetx > 0 ){
        // zoomValue = zoomValue > zoomMax ? zoomMax : zoomValue + scaleStep;
    }else{
        
    }
}



MOUSE_MOVE_FLAG 
getMouseDirection(){
    MOUSE_MOVE_FLAG ret = 0;
    using namespace keyboard_mouse;
    ret |= deltaMouseX < 0 ? MOUSE_MOVE_RIGHT : MOUSE_MOVE_LEFT;
    ret |= deltaMouseY < 0 ? MOUSE_MOVE_DOWN : MOUSE_MOVE_UP;
    return ret;
}
