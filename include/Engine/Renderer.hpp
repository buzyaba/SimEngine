#pragma once
#include <Engine/Camera.hpp>
#include <btBulletDynamicsCommon.h>

class Renderer {
    private:
        static Camera* camera;
        static btDiscreteDynamicsWorld* dynamicsWorld;
    public:
        static void initCamera(GLfloat FOV, GLfloat width, GLfloat height, GLfloat nearPlane,
            GLfloat farPlane, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 camUp);
        static void initPhysics();
        static Camera* getCamera() {return camera;}
        static btDiscreteDynamicsWorld* getDynamicsWorld() {return dynamicsWorld;}
        static void terminate() {delete camera; delete dynamicsWorld;};
};
