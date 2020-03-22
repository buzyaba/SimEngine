#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Engine/Renderer.hpp"


class WindowManager {
protected:
    GLFWwindow* window;
    virtual void cameraMovement(float dt) {};
public: 
    WindowManager(const uint& screenWidth = 800, const uint& screenHeight = 600, 
                  const std::string winName = "Window");
    int isWindowShouldClose() {return glfwWindowShouldClose(window);}
    virtual ~WindowManager() {glfwDestroyWindow(window); glfwTerminate();}
    virtual void runWindow(const float& dt, const std::function<void()>& renderFunc = 
                           [](){glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); glClearColor(1.f, 1.f, 1.f, 1.f);});
};
