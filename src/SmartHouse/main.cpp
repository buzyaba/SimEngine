#define WITHOUT_NUMPY
#include <Engine/Renderer.hpp>
// #include <SmartHouse/Table.hpp>
// #include <SmartHouse/Room.hpp>
// #include <SmartHouse/Desktop.hpp>
#include <chrono>
#include <thread>
#include <iostream>
#include <Engine/FirstPersonView.hpp>

#include "Core/WorkManager.h"
#include "Core/EmptyProgram.h"

#include "Core/common.h"
#include "matplotlibcpp.h"

TWorkManager* workManager;
namespace plt = matplotlibcpp;

int tick = 0;
bool windowFlag = false;

void renderScene();
void initApplication();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
void initPhysics();
void initMousePosition(GLfloat x, GLfloat y);
void cameraMovement(float dt);
void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateMouse(GLFWwindow* window, double xpos, double ypos);

void drawPlot() {
	float x_i = 0;
	std::vector<float> x;
	std::vector<float> y;
	while(x_i < 10) {
		x.emplace_back(x_i);
		y.emplace_back(std::sin(x_i));
		x_i += 0.01;
	}
	plt::plot(x, y);
	plt::show();
}

void startWork() {
	auto mainSet = TSetFactory::Create(0);//!!!!
  	workManager = new TWorkManager(mainSet);
  	workManager->InitDraw();
  	workManager->Start(1);
}

int main(int argc, char** argv) {
	auto plt_thread = std::thread(drawPlot);
	auto work_thread = std::thread(startWork);
//   auto previousTime = std::chrono::high_resolution_clock::now();
//   while(!window.isWindowShouldClose()) {
//     auto currentTime = std::chrono::high_resolution_clock::now();
// 	float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
// 	Renderer::getDynamicsWorld()->stepSimulation(dt);
	work_thread.join();
	delete workManager;
	std::cout << "Workmanager stopped\n";
	std::cout << "Waiting for plt\n";
	plt_thread.join();
  	Renderer::terminate();
  	return 0;
}

void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {
		
}

void initApplication() {
//     glEnable(GL_DEPTH_TEST);
// 	Renderer::initCamera(45.0f, 800, 600, 0.1f, 10000.0f, glm::vec3(0.0f, humanTall, 8.0f), glm::vec3(.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
// 	Renderer::initTextures();

//   //init physics
//     Renderer::initPhysics();
	Renderer::getDynamicsWorld()->setInternalTickCallback(myTickCallback);
  //Adding objects
	// table.push_back(new Table());
	// table.push_back(new Table(glm::vec3(-7.0f, 0.0f, 0.0f)));
	// Table::initDraw(table);
	// room.push_back(new Room());
	// Room::initDraw(room);
	// // for (int i = -10; i < 10; i++)
	// // 	for (int j = -10; j<10; j++)
	// monitor.push_back(new Monoblock(glm::vec3(0.0f, 3.1f, 0.0f)));
	// Monoblock::initDraw(monitor);
	// desktop.push_back(new Desktop(glm::vec3 (-6.5f, 3.1f, 0.0f)));
	// Desktop::initDraw(desktop);
}

// void initMousePosition(GLfloat x, GLfloat y){
//     lastX = x;
//     lastY = y;
// }

// void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods){
// 	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
// 		glfwSetWindowShouldClose(window,true);
// 	}
// 	if (key >= 0 && key < 1024)
//     {
//         if (action == GLFW_PRESS)
//             keys[key] = true;
//         else if (action == GLFW_RELEASE)
//             keys[key] = false;
//     }
// }

// void cameraMovement(float dt)
// {
// 	GLfloat cameraSpeed = 15.0f * dt;
// 	glm::vec3 prevCamPos = Renderer::getCamera()->getCameraPosition();
// 	glm::vec3 prevCamFront = Renderer::getCamera()->getCameraFront();
// 	if (keys[GLFW_KEY_W])
// 	{
// 		prevCamPos += cameraSpeed * glm::normalize(glm::vec3(prevCamFront[0]/abs(prevCamFront[0]+prevCamFront[2]), 0.0f, prevCamFront[2]/abs(prevCamFront[0]+prevCamFront[2])));
// 	}
// 	if (keys[GLFW_KEY_S])
// 	{
// 		prevCamPos -= cameraSpeed * glm::normalize(glm::vec3(prevCamFront[0]/abs(prevCamFront[0]+prevCamFront[2]), 0.0f, prevCamFront[2]/abs(prevCamFront[0]+prevCamFront[2])));
// 	}
// 	if (keys[GLFW_KEY_D])
// 	{
// 		prevCamPos += glm::normalize(glm::cross(Renderer::getCamera()->getCameraFront(), Renderer::getCamera()->getCameraUp())) *cameraSpeed;
// 	}
// 	if (keys[GLFW_KEY_A])
// 	{
// 		prevCamPos -= glm::normalize(glm::cross(Renderer::getCamera()->getCameraFront(), Renderer::getCamera()->getCameraUp())) *cameraSpeed;
// 	}
// 	prevCamPos[1] = humanTall;
// 	Renderer::getCamera()->moveCamera(prevCamPos);
// }

// void updateMouse(GLFWwindow* window, double xpos, double ypos){
// 	GLfloat xoffset = xpos - lastX;
// 	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
// 	lastX = xpos;
// 	lastY = ypos;

// 	GLfloat sensitivity = 0.05;	// Change this value to your liking
// 	xoffset *= sensitivity;
// 	yoffset *= sensitivity;

// 	yaw   += xoffset;
// 	pitch += yoffset;

// 	// Make sure that when pitch is out of bounds, screen doesn't get flipped
// 	if (pitch > 89.0f)
// 		pitch = 89.0f;
// 	if (pitch < -89.0f)
// 		pitch = -89.0f;

// 	glm::vec3 front;
// 	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
// 	front.y = sin(glm::radians(pitch));
// 	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
// 	Renderer::getCamera()->rotateCamera(glm::normalize(front));
// }