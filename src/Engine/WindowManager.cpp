#include "Engine/WindowManager.hpp"

WindowManager::WindowManager() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glewInit();
    glEnable(GL_DEPTH_TEST);
	Renderer::initCamera(45.0f, 800, 600, 0.1f, 10000.0f, glm::vec3(0.0f, 5.0f, 8.0f), 
                        glm::vec3(.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Renderer::initTextures();
    //init physics
    Renderer::initPhysics();
}