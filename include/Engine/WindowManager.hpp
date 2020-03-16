#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Engine/Renderer.hpp"

enum{screenWidth = 800, screenHeight = 600};

class WindowManager {
protected:
    GLFWwindow* window;
public: 
    WindowManager();
    virtual void cameraMovement(float dt) = 0;
    virtual void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
    virtual void updateMouse(GLFWwindow* window, double xpos, double ypos) = 0;
};