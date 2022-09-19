#ifndef __VIEWPORT_HEADERGUARD__
#define __VIEWPORT_HEADERGUARD__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

namespace viewport_vars{
    static glm::mat4 Projection;
    static glm::mat4 View;
    static glm::mat4 Model = glm::mat4(1.0f);
    static glm::mat4 Transforms;
    
    static glm::vec3 cameraPosition = glm::vec3(0, .5, 5);
    static glm::vec3 cameraEyeLook = glm::vec3(0, 0, 0);
    static glm::vec3 cameraVecNormal = glm::vec3(0, 1, 0);
    static glm::mat4 MVP = Projection * View * Model;

    static int rotationAngle = 0;

}

void rotate_camera(float angle_deg, glm::vec3 axis, glm::vec3& cameraPos);


#endif