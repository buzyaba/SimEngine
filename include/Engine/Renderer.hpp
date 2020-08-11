#pragma once
#include <Engine/Camera.hpp>
#include <vector>
#include <string>


class Renderer {
    private:
        static Camera* camera;
    public:
        static void initCamera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane,
            GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);
        static std::string getCWD();
        static std::string getPath(const std::string path);
        static Camera* getCamera() noexcept {return camera;}
        static void terminate() { delete camera; };
};
