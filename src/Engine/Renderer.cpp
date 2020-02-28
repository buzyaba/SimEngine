#include <Engine/Renderer.hpp>
#include <filesystem>

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

void Renderer::initTextures() {
    TextureLoader tex;
    auto i = std::filesystem::current_path().string().find("SimEngine");
    auto pwd = std::filesystem::current_path().string();
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/car.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/grass.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/road.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/gray.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/black.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/windows.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/windows98.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/table.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/wall.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/floor.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/ceiling.jpg"));
    textures.push_back(tex.getTextureID(pwd.substr(0,i) + "SimEngine/assets/textures/monitor.jpg"));
}
