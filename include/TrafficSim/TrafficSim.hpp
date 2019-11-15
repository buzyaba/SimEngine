#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine/Camera.hpp>
#include <Engine/ShaderLoader.hpp>
#include <Engine/LightRenderer.hpp>
#include <Engine/MeshRenderer.hpp>
#include <Engine/TextureLoader.hpp>
#include <btBulletDynamicsCommon.h>
#include <Engine/Object.hpp>


void renderScene();

void initApplication();
void initPhysics();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
void cameraMovement(float dt);
void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void initMousePosition(GLfloat x, GLfloat y);
void updateMouse(GLFWwindow* window, double xpos, double ypos);
void updateMouseButtons(GLFWwindow* window, int button, int action, int mods);
void updateScroll(GLFWwindow* window, double xoffset, double yoffset);

glm::vec3 cartesianToSpherical(glm::vec3 vec);
glm::vec3 sphericalToCartesian(glm::vec3 vec);
