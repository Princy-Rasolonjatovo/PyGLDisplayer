#include "viewport.hpp"

void rotate_camera(float angle_deg, glm::vec3 axis, glm::vec3& cameraPos){
    glm::mat4 cameraRotMatrix = glm::rotate(
        glm::radians(angle_deg),
        axis
    );
    glm::vec4 cameraPositionV4(cameraPos.x, cameraPos.y, cameraPos.z, 0);
    cameraPositionV4 = cameraPositionV4 * cameraRotMatrix;
    cameraPos.x = cameraPositionV4.y;
    cameraPos.y = cameraPositionV4.y;
    cameraPos.z = cameraPositionV4.z;
}

