#ifndef __DISPLAYER_NATIVE_INCLUDED__
#define __DISPLAYER_NATIVE_INCLUDED__

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>


#include "shader.hpp"

#define DISP_DEFAULT_WINDOW_NAME "GLWindow"

#define GLFW_INIT_ERROR 512
#define GLFW_WINDOW_CREATE_ERROR GLFW_INIT_ERROR >> 1
#define GLEW_INIT_FAILED GLFW_INIT_ERROR >> 2

typedef struct ProjectionSettings ProjectionSettings;
typedef struct ViewSettings ViewSettings;



struct ProjectionSettings{
    float fov; //  in radians
    float aspect; // screen_format
    float clip_near; // zoom in ?
    float clip_far; // zoom out ?
};

// Why not use a vec3 ?
struct ViewSettings{
    float posX;
    float posY;
    float posZ;
};



int disp_initConfigureWindow(GLFWwindow* glWindow, int width, int height, int antialias=4,  const char* windowTitle=DISP_DEFAULT_WINDOW_NAME);
void disp_deallocAllAndTerminate(void);

// static
glm::mat4 setMVP(ProjectionSettings p_s, ViewSettings v_s);


#endif // end __DISPLAYER_NATIVE_INCLUDED__