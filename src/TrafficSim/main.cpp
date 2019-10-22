#include <TrafficSim/TrafficSim.hpp>

enum{screenWidth = 800, screenHeight = 600};

int main(int argc, char** argv) {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Traffic Simulation", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glewInit();
  while(!glfwWindowShouldClose(window)) {
    // Some render stuff
    renderScene();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}