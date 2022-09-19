#include "displayer_native.hpp"

/**
 * Initialize a glWindow
 **/
int disp_initConfigureWindow(GLFWwindow* glWindow, int width, int height, int antialias, const char* windowTitle){
    // Init GLFW
    if (!glfwInit())
        return GLFW_INIT_ERROR;

    glfwWindowHint(GLFW_SAMPLES, antialias);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glWindow = NULL;
    // glWindow = glfwCreateWindow(width, height, "GLWindow"/*windowTitle*/, NULL, NULL);
    // if (glWindow == NULL){
    //     glfwTerminate();
    //     return GLFW_WINDOW_CREATE_ERROR;
    // }
    // glfwMakeContextCurrent(glWindow);
    
    // glewExperimental = true;
    // if (glewInit() != GLEW_OK)
    //     return GLEW_INIT_FAILED;
    
    // glfwSetInputMode(glWindow, GLFW_STICKY_KEYS, GL_TRUE);

    return 0;
}



void disp_deallocAllAndTerminate(void){
    // Delete Buffers

    // Terminate glfw
    glfwTerminate();
}

glm::mat4 setMVP(ProjectionSettings p_s, ViewSettings v_s){
    glm::mat4 P, V, M;
    P = glm::perspective(
        p_s.fov,
        p_s.aspect,
        p_s.clip_near,
        p_s.clip_far        
    );

    V = glm::lookAt(
        glm::vec3(4, 3, 3),// eye
        glm::vec3(0, 0, 0), // center
        glm::vec3(0, 1, 0) // orientation
    );

    M = glm::mat4(1.0f);
    
    return P * V * M;
}