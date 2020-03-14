#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Engine/Renderer.hpp>
#include <SmartHouse/Table.hpp>
#include <SmartHouse/Room.hpp>
#include <SmartHouse/Desktop.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "Core/WorkManager.h"
#include "Core/EmptyProgram.h"

#include "Core/common.h"

enum{screenWidth = 800, screenHeight = 600};

bool keys[1024];
GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch =   0.0f;
GLfloat lastX;
GLfloat lastY;
GLfloat humanTall = 5.0f;

// std::vector<Table*> table;
// std::vector<Room*> room;
// std::vector<Monoblock*> monitor;
// std::vector<Desktop*> desktop;
// std::vector<IObject*> allObject(2);
// std::vector<TObjectOfObservation*> objects(5);
// std::vector<TSmartThing*> things(1);
// TEnvironmentScript* script;
TWorkManager* workManager;

int tick = 0;
// bool windowFlag[400] = { false };
bool windowFlag = false;

void renderScene();
void initApplication();
void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar timeStep);
void initPhysics();
void initMousePosition(GLfloat x, GLfloat y);
void cameraMovement(float dt);
void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateMouse(GLFWwindow* window, double xpos, double ypos);

int main(int argc, char** argv) {
	
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Smart House", NULL, NULL);
  glfwMakeContextCurrent(window);
  initMousePosition(screenWidth/2, screenHeight/2); 
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
  glfwSetKeyCallback(window, updateKeyboard); // keyboard events
  glfwSetCursorPosCallback(window, updateMouse); // mouse events
  glewInit();

  initApplication();
  auto mainSet = TSetFactory::Create(0);//!!!!
//   objects = mainSet->GetObject();///!!!
//   things = mainSet->GetThing();
//   auto maxStep = 1000;
//     std::vector<IObject*> allObject(objects.size() + things.size());
//   int j = 0;
//   for (int i = 0; i < objects.size(); i++)
//   {
//     allObject[j] = objects[i];
//     j++;
//   }
//   for (int i = 0; i < things.size(); i++)
//   {
//     allObject[j] = things[i];
//     j++;
//   }
//   script = new TEnvironmentScript(allObject, "", maxStep);///!!!!
  workManager = new TWorkManager(mainSet);
  workManager->InitDraw();
  auto previousTime = std::chrono::high_resolution_clock::now();
  while(!glfwWindowShouldClose(window)) {
    auto currentTime = std::chrono::high_resolution_clock::now();
	float dt = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
	Renderer::getDynamicsWorld()->stepSimulation(dt);
    
    // Some render stuff
    renderScene();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    cameraMovement(dt); // every frame movement
    previousTime = currentTime;
  }
  glfwTerminate();
  Renderer::terminate();
  return 0;
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 1.f, 0.f, 1.f);
	//Drawing objects here
    workManager->DrawElements();
	// table[0]->drawElements(table);
	// Room::drawElements(room);
	// Monoblock::drawElements(monitor);
	// Desktop::drawElements(desktop);
}


void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {
		
  	// if (tick >= 399){
	// 	tick = 0;
	// 	windowFlag = !windowFlag;
	// 	if (windowFlag) {
	// 		GLuint texture = Renderer::getTextures()[WINDOWS];
	// 		monitor[0]->setScreenTexture(texture);
	// 	} else {
			// GLuint texture = Renderer::getTextures()[SCREENSAVER];
			// monitor[0]->setScreenTexture(texture);
	// 	}
	// }
	// tick++;
	// auto time = tick*timeStep;
	// workManager->Iteration(time);
	// if (objects[0]->GetProperties()[0]->GetValues()[0] == 0) {
	// 	GLuint texture = Renderer::getTextures()[WINDOWS];
	// 	monitor[0]->setScreenTexture(texture);
	// } else {
	// 	GLuint texture = Renderer::getTextures()[SCREENSAVER];
	// 	monitor[0]->setScreenTexture(texture);
	// }
}

void initApplication() {
    glEnable(GL_DEPTH_TEST);
	Renderer::initCamera(45.0f, 800, 600, 0.1f, 10000.0f, glm::vec3(0.0f, humanTall, 8.0f), glm::vec3(.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Renderer::initTextures();

  //init physics
    Renderer::initPhysics();
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

void initMousePosition(GLfloat x, GLfloat y){
    lastX = x;
    lastY = y;
}

void updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window,true);
	}
	if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void cameraMovement(float dt)
{
	GLfloat cameraSpeed = 15.0f * dt;
	glm::vec3 prevCamPos = Renderer::getCamera()->getCameraPosition();
	glm::vec3 prevCamFront = Renderer::getCamera()->getCameraFront();
	if (keys[GLFW_KEY_W])
	{
		prevCamPos += cameraSpeed * glm::normalize(glm::vec3(prevCamFront[0]/abs(prevCamFront[0]+prevCamFront[2]), 0.0f, prevCamFront[2]/abs(prevCamFront[0]+prevCamFront[2])));
	}
	if (keys[GLFW_KEY_S])
	{
		prevCamPos -= cameraSpeed * glm::normalize(glm::vec3(prevCamFront[0]/abs(prevCamFront[0]+prevCamFront[2]), 0.0f, prevCamFront[2]/abs(prevCamFront[0]+prevCamFront[2])));
	}
	if (keys[GLFW_KEY_D])
	{
		prevCamPos += glm::normalize(glm::cross(Renderer::getCamera()->getCameraFront(), Renderer::getCamera()->getCameraUp())) *cameraSpeed;
	}
	if (keys[GLFW_KEY_A])
	{
		prevCamPos -= glm::normalize(glm::cross(Renderer::getCamera()->getCameraFront(), Renderer::getCamera()->getCameraUp())) *cameraSpeed;
	}
	prevCamPos[1] = humanTall;
	Renderer::getCamera()->moveCamera(prevCamPos);
}

void updateMouse(GLFWwindow* window, double xpos, double ypos){
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;	// Change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Renderer::getCamera()->rotateCamera(glm::normalize(front));
}