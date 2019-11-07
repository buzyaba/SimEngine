#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine/Camera.hpp>
#include <btBulletDynamicsCommon.h>
#include <Engine/Object.hpp>
#include <TrafficSim/Car.hpp>
#include <TrafficSim/TrafficLight.hpp>


void renderScene();

void initApplication();
void initPhysics();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
void cameraMovement(float dt);
void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
