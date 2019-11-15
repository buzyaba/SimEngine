#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    public:
        Camera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane,
            GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);
        ~Camera();

        glm::mat4 getViewMatrix();
        glm::mat4 getProjectionMatrix();
        glm::vec3 getCameraPosition();
        glm::vec3 getCameraFront();
        glm::vec3 getCameraUp();
        Camera* moveCamera(glm::vec3 camPos);
        Camera* rotateCamera(glm::vec3 camFront);
        Camera* rotateUpCamera(glm::vec3 camUp);

    private:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
};