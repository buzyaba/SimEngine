#include <TrafficSim/TrafficSim.hpp>
#include <chrono>

enum{screenWidth = 800, screenHeight = 600};

extern Camera* camera;
extern Car* car;
extern Object* road1;
extern Object* road2;
extern Object* road3;
extern Object* road4;
extern Object* ground;
extern TrafficLight* light;
extern btDiscreteDynamicsWorld* dynamicsWorld;

int main(int argc, char** argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Traffic Simulation", NULL, NULL);
  glfwMakeContextCurrent(window);
  initMousePosition(screenWidth/2, screenHeight/2); 
  glfwSetKeyCallback(window, updateKeyboard); // keyboard events
  glfwSetCursorPosCallback(window, updateMouse); // mouse events
  glfwSetMouseButtonCallback(window, updateMouseButtons);
  glfwSetScrollCallback(window, updateScroll);
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
    cameraMovement(dt); // every frame movement
    previousTime = currentTime;
  }
  glfwTerminate();
  delete camera;
  delete ground;
  delete road1;
  delete road2;
  delete road3;
  delete road4;
  delete car;
  delete light;
  delete dynamicsWorld;

  return 0;
}