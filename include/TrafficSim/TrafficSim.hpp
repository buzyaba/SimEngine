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

void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar
timeStep);