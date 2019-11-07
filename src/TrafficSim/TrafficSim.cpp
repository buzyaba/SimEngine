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
GLfloat pitch = 0.0f;
GLfloat yaw = 0.0f;
GLfloat roll = 0.0f;

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

    camera = new Camera(45.0f, 800, 600, 0.1f, 1000.0f, glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(0.0, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

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


void cameraMovement(float dt)
{
	GLfloat cameraSpeed = 200.0f * dt;
	if (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_RIGHT]){
		if(keys[GLFW_KEY_LEFT])
			pitch-= cameraSpeed * dt * 20;
		if(keys[GLFW_KEY_RIGHT])
			pitch+= cameraSpeed * dt * 20;
		// if (pitch > 89.0f)
		// 	pitch = -89.0f;
		// if (pitch < -89.0f)
		// 	pitch = +89.0f;

		camera->rotateUpCamera(glm::normalize(glm::vec3(cos(glm::radians(pitch)), 0.0f, sin(glm::radians(pitch)))));
	}
	else{
		glm::vec3 prevCamPos = camera->getCameraPosition();	
		GLfloat prevHeight = prevCamPos[1];
		if (keys[GLFW_KEY_W])
		{
			prevCamPos += cameraSpeed * camera->getCameraUp();
		}
		if (keys[GLFW_KEY_S])
		{
			prevCamPos -= cameraSpeed * camera->getCameraUp();
		}
		if (keys[GLFW_KEY_D])
		{
			prevCamPos += glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * cameraSpeed;
		}
		if (keys[GLFW_KEY_A])
		{
			prevCamPos -= glm::normalize(glm::cross(camera->getCameraFront(), camera->getCameraUp())) * cameraSpeed;
		}
		prevCamPos[1] = prevHeight;
		camera = camera->moveCamera(prevCamPos);
	}
}