#include "Engine/FirstPersonView.hpp"

static bool keys[1024];
static GLfloat lastX;
static GLfloat lastY;
static GLfloat yaw;	
static GLfloat pitch;

FirstPersonView::FirstPersonView(const std::uint32_t& screenWidth, const std::uint32_t& screenHeight, 
                                 const std::string winName, bool _visible): WindowManager(screenWidth, screenHeight, winName, _visible) {
    Renderer::initCamera(45.0f, screenWidth, screenHeight, 0.1f, 10000.0f, glm::vec3(0.0f, 5.0f, 8.0f), 
                        glm::vec3(.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    lastX = screenWidth/2;
    lastY = screenHeight/2;
    yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
    pitch =   0.0f;

	// setCursor(false);
    glfwSetKeyCallback(window, updateKeyboard); // keyboard events
    glfwSetCursorPosCallback(window, updateMouse); // mouse events
}

void FirstPersonView::cameraMovement(float dt) {
    GLfloat cameraSpeed = 12.0f * dt;
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
	prevCamPos[1] = 5.0f;
	Renderer::getCamera()->moveCamera(prevCamPos);
}

void FirstPersonView::updateKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window,true);
	}
	if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }
}

void FirstPersonView::updateMouse(GLFWwindow* window, double xpos, double ypos) {
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
