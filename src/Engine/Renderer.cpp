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
btDiscreteDynamicsWorld* Renderer::dynamicsWorld = nullptr;
std::vector<GLuint>Renderer::textures;

void Renderer::initCamera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane, 
    GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp) {
        camera = new Camera(FOV, width, height, nearPlane, farPlane, camPos, camFront, camUp);
    }

void Renderer::initPhysics() {
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    
    dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
    dynamicsWorld->setInternalTickCallback(nullptr);
}

std::string Renderer::getCWD() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir(buff, FILENAME_MAX);
    std::string current_working_dir(std::move(buff));
    return current_working_dir;
}

void Renderer::initTextures() {
    TextureLoader tex;
    auto cwd = Renderer::getCWD();
    auto c_cwd = cwd;
    std::transform(c_cwd.begin(), c_cwd.end(), c_cwd.begin(), toupper);
    auto i = c_cwd.find("SIMENGINE");
    
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/car.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/grass.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/road.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/gray.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/black.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/windows.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/windows98.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/table.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/wall.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/floor.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/ceiling.jpg"));
    textures.emplace_back(tex.getTextureID(cwd.substr(0,i+9) + "/assets/textures/monitor.jpg"));
}
