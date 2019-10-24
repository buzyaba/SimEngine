#include <SmartHouse/SmartHouse.hpp>
#include <chrono>

enum{screenWidth = 800, screenHeight = 600};

extern Camera* camera;
extern MeshRenderer* sphere;
extern MeshRenderer* ground;

//physics
extern btDiscreteDynamicsWorld* dynamicsWorld;

int main(int argc, char** argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Traffic Simulation", NULL, NULL);
  glfwMakeContextCurrent(window);
  glewInit();
  initApplication();
  auto previousTime = std::chrono::high_resolution_clock::now();
  while(!glfwWindowShouldClose(window)) {
    auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();

		dynamicsWorld->stepSimulation(dt);
    // Some render stuff
    renderScene();

    glfwSwapBuffers(window);
    glfwPollEvents();

    previousTime = currentTime;
  }
  glfwTerminate();
  delete camera;
  return 0;
}