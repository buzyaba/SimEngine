#include <SmartHouse/SmartHouse.hpp>

std::vector<Table*> table;
std::vector<Room*> room;
std::vector<Monitor*> monitor;

//physics
bool keys[1024];
GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch =   0.0f;
GLfloat lastX;
GLfloat lastY;
GLfloat humanTall = 5.0f;
int tick = 0;
bool windowFlag = false;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 1.f, 0.f, 1.f);
    //Drawing objects here
    Table::drawElements(table);
	Room::drawElements(room);
	Monitor::drawElements(monitor);
}


void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {
    if (tick>300){
		tick = 0;
		windowFlag = !windowFlag;
		if (windowFlag) {
			GLuint texture = Renderer::getTextures()[WINDOWS];
			monitor[0]->meshScreen->setTexture(texture);
		}
		else
		{
			GLuint texture = Renderer::getTextures()[SCREENSAVER];
			monitor[0]->meshScreen->setTexture(texture);
		}
		
	}
	tick++;

}

void initApplication() {
    glEnable(GL_DEPTH_TEST);

	Renderer::initCamera(45.0f, 800, 600, 0.1f, 10000.0f, glm::vec3(0.0f, humanTall, 8.0f), glm::vec3(.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	Renderer::initTextures();
    //init physics
    Renderer::initPhysics();
	Renderer::getDynamicsWorld()->setInternalTickCallback(myTickCallback);

    //Adding objects
	table.push_back(new Table());
	Table::initDraw(table);
	room.push_back(new Room());
	Room::initDraw(room);
	monitor.push_back(new Monitor());
	Monitor::initDraw(monitor);
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