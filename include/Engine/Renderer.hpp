#pragma once
#include <Engine/Camera.hpp>
#include <btBulletDynamicsCommon.h>
#include <Engine/TextureLoader.hpp>
#include <vector>
#include <string>

enum Textures {CAR, GRASS, ROAD, GRAY, BLACK, WINDOWS, SCREENSAVER, TABLE, WALL, FLOOR, CEILING, MONITOR, GREEN, RED};

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
        static std::string getCWD();
        static Camera* getCamera() noexcept {return camera;}
        static std::vector<GLuint> getTextures() noexcept {return textures;}
        static btDiscreteDynamicsWorld* getDynamicsWorld() noexcept {return dynamicsWorld;}
        static void terminate() {delete camera; delete dynamicsWorld;};
};
