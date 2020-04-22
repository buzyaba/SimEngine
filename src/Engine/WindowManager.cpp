#include "Engine/WindowManager.hpp"

GLFWwindow* WindowManager::window = nullptr;

WindowManager::WindowManager(const std::uint32_t& screenWidth, const std::uint32_t& screenHeight, const std::string winName) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(screenWidth, screenHeight, winName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
	Renderer::initTextures();
    Renderer::initPhysics();
}

void WindowManager::runWindow(const float& dt, const std::function<void()>& renderFunc) {
    Renderer::getDynamicsWorld()->stepSimulation(dt);
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