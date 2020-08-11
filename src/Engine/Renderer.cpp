#include <Engine/Renderer.hpp>
#include <algorithm>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


Camera* Renderer::camera = nullptr;

void Renderer::initCamera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, 
    GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
        camera = new Camera(FOV, width, height, nearPlane, farPlane, camPos, camFront, camUp);
}

std::string Renderer::getCWD() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(buff);
    return current_working_dir;
}

std::string Renderer::getPath(const std::string path) {
    auto cwd = Renderer::getCWD();
    std::transform(cwd.begin(), cwd.end(), cwd.begin(), toupper);
    auto i = cwd.find("SIMENGINE");
    return getCWD().substr(0, i+9) + path;
}
