#include "Engine/WindowManager.hpp"
#include <iostream>

GLFWwindow* WindowManager::window = nullptr;

WindowManager::WindowManager(const std::uint32_t& screenWidth, const std::uint32_t& screenHeight, 
                             const std::string winName,
                             bool _visible) 
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, _visible);
    window = glfwCreateWindow(screenWidth, screenHeight, winName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2); 	
    glewInit();
    glEnable(GL_DEPTH_TEST);
}

void WindowManager::runWindow(const float& dt, const std::function<void()>& renderFunc) {
    renderFunc();
    glfwSwapBuffers(window);
    glfwPollEvents();
    this->cameraMovement(dt);
}

void WindowManager::setVisibility(bool _switch) noexcept{
    if (!_switch) {
        glfwPollEvents();
        glfwHideWindow(window);
    } else {
        glfwPollEvents();
        glfwShowWindow(window);
    }
}
void WindowManager::setCursor(bool _switch) noexcept {
    if (_switch)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // enable cursor
    else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
}