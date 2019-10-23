#include <SmartHouse/SmartHouse.hpp>

enum{screenWidth = 800, screenHeight = 600};

extern Camera* camera;
extern LightRenderer* light;
MeshRenderer* sphere;

int main(int argc, char** argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Traffic Simulation", NULL, NULL);
  glfwMakeContextCurrent(window);
  glewInit();
  initApplication();
  while(!glfwWindowShouldClose(window)) {
    // Some render stuff
    renderScene();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  delete camera;
  delete light;
  return 0;
}