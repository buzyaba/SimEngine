#include <TrafficSim/TrafficSim.hpp>

btDiscreteDynamicsWorld* dynamicsWorld;
Camera* camera;
Car* car;
Object* road1;
Object* road2;
Object* road3;
Object* road4;
Object* ground;
TrafficLight* light;

bool keys[1024];
glm::vec3 sphereCam;
double lastX;
double lastY;
bool rightMouseClick;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.f, 1.f, 1.f, 1.f);
    //Drawing objects here
    car->draw();
    ground->draw();
	light->draw();
	road1->draw();
	road2->draw();
	road3->draw();
	road4->draw();
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

void initApplication() {
    glEnable(GL_DEPTH_TEST);

        camera = new Camera(45.0f, 800, 600, 0.1f, 10000.0f, glm::vec3(20.0f, 780.0f, 20.0f), glm::vec3(-20.0f, -780.0f, -20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		sphereCam = cartesianToSpherical(camera->getCameraPosition() - (camera->getCameraPosition() + camera->getCameraFront()));

    //init physics
    initPhysics();

    //Adding objects
    car = new Car(camera, dynamicsWorld, glm::vec3(0.0f, 0.0f, 253.0f));

	road1 = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(500, 0.2, 7)), 
	glm::vec3(0, -1, 257.0f), glm::vec3(500, 0.2, 7), 0.0f, "road.jpg");

	road2 = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(500, 0.2, 7)), 
	glm::vec3(0, -1, -257.0f), glm::vec3(500, 0.2, 7), 0.0f, "road.jpg");

	road3 = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(500, 0.2, 7)), 
	glm::vec3(-257, -1, 0), glm::vec3(500, 0.2, 7), 0.0f, "road.jpg");
	road3->setRotation(90, 0, 0);

	road4 = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(500, 0.2, 7)), 
	glm::vec3(257, -1, 0), glm::vec3(500, 0.2, 7), 0.0f, "road.jpg");
	road4->setRotation(90, 0, 0);

	light = new TrafficLight(camera, dynamicsWorld, glm::vec3(-264.0f, 2.0f, 264.0f));
    ground = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(500.0f, 0.2f, 500.0f)),
    glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(500.0f, 0.2f, 500.0f), 0.0f,"grass.jpg");
    ground->setCollisionFlags(CollisionType::STATIC);
	
}

void myTickCallback(btDynamicsWorld *_dynamicsWorld, btScalar
    timeStep) {
    
    glm::vec3 pos = car->getPostition();
    car->setPostition(pos + glm::vec3(-5.0f, 0.0f, 0.0f)*timeStep);

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

void updateMouseButtons(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		rightMouseClick = true;
		glfwGetCursorPos(window, &lastX, &lastY);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	} else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		rightMouseClick = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void updateMouse(GLFWwindow* window, double xpos, double ypos){
	if (rightMouseClick) {
		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to left
		lastX = xpos;
		lastY = ypos;

		GLfloat sensitivity = 0.05;	// Change this value to your liking
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		glm::vec3 prevCamPos = camera->getCameraPosition();	
		glm::vec3 prevCamFront = camera->getCameraFront();	
		glm::vec3 offsetCam = prevCamPos + prevCamFront; 
		prevCamPos -= offsetCam;

		sphereCam[2] -= xoffset;
		sphereCam[1] -= yoffset;

		if(sphereCam[1] <= 1.5)
				sphereCam[1] = 1.5;
		if(sphereCam[1] >= 85)
				sphereCam[1] = 85;
		prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
		prevCamPos = sphericalToCartesian(sphereCam);

		camera = camera->moveCamera(prevCamPos + offsetCam);
		camera = camera->rotateCamera(prevCamFront);
	}
}

void updateScroll(GLFWwindow* window, double xoffset, double yoffset) {
	glm::vec3 prevCamPos = camera->getCameraPosition();	
	glm::vec3 prevCamFront = camera->getCameraFront();	
	glm::vec3 offsetCam = prevCamPos + prevCamFront; 
	prevCamPos -= offsetCam;
		
	GLfloat sensitivity = 15;	// Change this value to your liking
	yoffset *= sensitivity;

	sphereCam[0] -= yoffset;
	if (sphereCam[0] >= 990)
		sphereCam[0] = 990;
	if (sphereCam[0] <= 0.5)
		sphereCam[0] = 0.5;	
	prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
	prevCamPos = sphericalToCartesian(sphereCam);

	camera = camera->moveCamera(prevCamPos + offsetCam);
	camera = camera->rotateCamera(prevCamFront);
}

void cameraMovement(float dt)
{
	GLfloat cameraSpeed = 155.0f * dt;
	glm::vec3 prevCamPos = camera->getCameraPosition();	
	glm::vec3 prevCamFront = camera->getCameraFront();	
	glm::vec3 offsetCam = prevCamPos + prevCamFront; 
	prevCamPos -= offsetCam;
	if (keys[GLFW_KEY_W])
	{
		offsetCam += cameraSpeed * glm::normalize(glm::vec3(prevCamFront[0]/abs(prevCamFront[0]+prevCamFront[2]), 0.0f, prevCamFront[2]/abs(prevCamFront[0]+prevCamFront[2])));
	
	}
	if (keys[GLFW_KEY_S])
	{
		offsetCam -= cameraSpeed * glm::normalize(glm::vec3(prevCamFront[0]/abs(prevCamFront[0]+prevCamFront[2]), 0.0f, prevCamFront[2]/abs(prevCamFront[0]+prevCamFront[2])));
	}
	if (keys[GLFW_KEY_D])
	{
		offsetCam += glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * 1.5f * cameraSpeed;
	}
	if (keys[GLFW_KEY_A])
	{
		offsetCam -= glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * 1.5f * cameraSpeed;
	}
	if (!rightMouseClick) {
		if (keys[GLFW_KEY_LEFT])
		{
			sphereCam[2] -= cameraSpeed * 5.0f;
			prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
			prevCamPos = sphericalToCartesian(sphereCam);
		}
		if (keys[GLFW_KEY_RIGHT])
		{
			sphereCam[2] += cameraSpeed * 5.0f;
			prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
			prevCamPos = sphericalToCartesian(sphereCam);
		}
		if (keys[GLFW_KEY_UP])
		{	
			if(sphereCam[1] >= 1.5)
				sphereCam[1] -= cameraSpeed * 5.0f;
			prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
			prevCamPos = sphericalToCartesian(sphereCam);
		}
		if (keys[GLFW_KEY_DOWN])
		{
			if(sphereCam[1] <= 85)
				sphereCam[1] += cameraSpeed * 5.0f;
			prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
			prevCamPos = sphericalToCartesian(sphereCam);
		}

		// !!!!!!!!!!!!ZOOM HERE!!!!!!!!!
		if (keys[GLFW_KEY_E])
		{
			if (sphereCam[0] <= 990) 
				sphereCam[0] += cameraSpeed * 5.0f;
			prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
			prevCamPos = sphericalToCartesian(sphereCam);
		}
		if (keys[GLFW_KEY_Q])
		{
			if (sphereCam[0] >= 0.5)
				sphereCam[0] -= cameraSpeed * 5.0f;
			prevCamFront += prevCamPos - sphericalToCartesian(sphereCam);
			prevCamPos = sphericalToCartesian(sphereCam);
		}
	}
	camera = camera->moveCamera(prevCamPos + offsetCam);
	camera = camera->rotateCamera(prevCamFront);

}

glm::vec3 cartesianToSpherical(glm::vec3 vec){
	glm::vec3 spherical;
	spherical[0] = sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
	spherical[1] = glm::degrees(acos(vec[1] / sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2])));
	spherical[2] = glm::degrees(atan(vec[0]/vec[2]));
	return spherical;
}

glm::vec3 sphericalToCartesian(glm::vec3 vec){
	glm::vec3 cartesian;
	vec[1] = glm::radians(vec[1]);
	vec[2] = glm::radians(vec[2]);
	cartesian[0] = vec[0]*sin(vec[1])*sin(vec[2]);
	cartesian[1] = vec[0]*cos(vec[1]);
	cartesian[2] = vec[0]*sin(vec[1])*cos(vec[2]);
	return cartesian;
}

void initMousePosition(GLfloat x, GLfloat y){
    lastX = x;
    lastY = y;
}
