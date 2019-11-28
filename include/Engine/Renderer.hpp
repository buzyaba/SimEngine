#pragma once
#include <Engine/Camera.hpp>
#include <btBulletDynamicsCommon.h>
#include <Engine/TextureLoader.hpp>
#include <vector>

enum Textures {CAR, GRASS, GROUND, ROAD};

class Renderer {
    private:
        static Camera* camera;
        static btDiscreteDynamicsWorld* dynamicsWorld;
        static std::vector<GLuint> textures;
    public:
        static void initCamera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane,
            GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);
        static void initPhysics();
        static void initTextures();
        static Camera* getCamera() {return camera;}
        static btDiscreteDynamicsWorld* getDynamicsWorld() {return dynamicsWorld;}
        static void terminate() {delete camera; delete dynamicsWorld;};
};
