#include <SmartHouse/SmartHouse.hpp>

Camera* camera;


Object* sphere;
Object* ground;
Object* enemy;

//physics
btDiscreteDynamicsWorld* dynamicsWorld;
bool keys[1024];
GLfloat yaw   = -90.0f;	// Yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right (due to how Eular angles work) so we initially rotate a bit to the left.
GLfloat pitch =   0.0f;
GLfloat lastX;
GLfloat lastY;
GLfloat humanTall = 5.0f;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 1.f, 0.f, 1.f);
    //Drawing objects here
    sphere->draw();
    ground->draw();
    enemy->draw();
}

void initPhysics() {
    btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
    
    dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
    dynamicsWorld->setInternalTickCallback(myTickCallback);
}

void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {
    
		// Get enemy transform
		glm::vec3 pos = enemy->getPosition();
		// Check if offScreen
		if (pos.x <= -10.0f) {

			enemy->setPosition(glm::vec3(5.0f, -1.0f, 0.0f));
            sphere->setPosition(glm::vec3(0.0f));
		}
        else
            enemy->setPosition(pos+glm::vec3(-10.0f, 0.0f, 0.0f)*timeStep);

}

void initApplication() {
    glEnable(GL_DEPTH_TEST);

        camera = new Camera(45.0f, 800, 600, 0.1f, 1000.0f, glm::vec3(0.0f, humanTall, 8.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    //init physics
    initPhysics();

    //Adding objects
    sphere = new Object(ObjectType::Sphere, camera, dynamicsWorld, new btSphereShape(1), glm::vec3(0.0f), glm::vec3(1.0f), 10.0f,"globe.jpg");
    ground = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(10.0f, 0.2f, 2.0f)),
    glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(10.0f, 0.1f, 2.0f), 0.0f,"road.jpg");
    ground->setCollisionFlags(CollisionType::STATIC);
    enemy = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(1.0f, 1.0f, 1.0f)),
    glm::vec3(5.0f, -1.0f, 0.0f), glm::vec3(1.0f), 0.0f);
    enemy->setCollisionFlags(CollisionType::KINEMATIC);
    //ground->setRotation(0.0f, 0.0, -45.0f);
    //ground->setPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
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
	glm::vec3 prevCamPos = camera->getCameraPosition();
	if (keys[GLFW_KEY_W])
	{
		prevCamPos += cameraSpeed * camera->getCameraFront();
	}
	if (keys[GLFW_KEY_S])
	{
		prevCamPos -= cameraSpeed * camera->getCameraFront();
	}
	if (keys[GLFW_KEY_D])
	{
		prevCamPos += glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) *cameraSpeed;
	}
	if (keys[GLFW_KEY_A])
	{
		prevCamPos -= glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) *cameraSpeed;
	}
	prevCamPos[1] = humanTall;
	camera = camera->moveCamera(prevCamPos);
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
	camera->rotateCamera(glm::normalize(front));
}