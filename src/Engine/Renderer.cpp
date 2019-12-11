#include <Engine/Renderer.hpp>

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
    textures.push_back(tex.getTextureID("../../../assets/textures/car.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/grass.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/ground.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/road.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/gray.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/black.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/windows.jpg"));
    textures.push_back(tex.getTextureID("../../../assets/textures/windows98.jpg"));
}
