#include <Engine/Renderer.hpp>
#include <algorithm>


Camera* Renderer::camera = nullptr;

void Renderer::initCamera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, 
    GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
        camera = new Camera(FOV, width, height, nearPlane, farPlane, camPos, camFront, camUp);
}
