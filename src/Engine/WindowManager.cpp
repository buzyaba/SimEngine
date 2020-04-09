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
	// Renderer::initCamera(45.0f, screenWidth, screenHeight, 0.1f, 10000.0f, glm::vec3(0.0f, 5.0f, 8.0f), 
    //                     glm::vec3(.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Renderer::initTextures();
    //init physics
    Renderer::initPhysics();
}

void WindowManager::runWindow(const float& dt, const std::function<void()>& renderFunc) {
    Renderer::getDynamicsWorld()->stepSimulation(dt);
    renderFunc();
    glfwSwapBuffers(window);
    glfwPollEvents();
    this->cameraMovement(dt);
}