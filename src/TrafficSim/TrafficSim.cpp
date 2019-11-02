#include <TrafficSim/TrafficSim.hpp>

btDiscreteDynamicsWorld* dynamicsWorld;
Camera* camera;

Object* sphere;
Object* ground;
Object* enemy;

bool keys[1024];
GLfloat pitch =   0.0f;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.f, 1.f, 1.f, 1.f);
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

void initApplication() {
    glEnable(GL_DEPTH_TEST);

        camera = new Camera(45.0f, 800, 600, 0.1f, 1000.0f, glm::vec3(0.0f, 35.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

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
	if (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_RIGHT]){
		if(keys[GLFW_KEY_LEFT])
			pitch-= cameraSpeed * 5.0f;
		if(keys[GLFW_KEY_RIGHT])
			pitch+= cameraSpeed * 5.0f;
		if (pitch > 89.0f)
		pitch = -89.0f;
	if (pitch < -89.0f)
		pitch = +89.0f;

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