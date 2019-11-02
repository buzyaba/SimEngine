#include <SmartHouse/SmartHouse.hpp>

Camera* camera;

MeshRenderer* sphere;
MeshRenderer* ground;

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
    glClearColor(0.2f, 0.8f, 0.f, 1.f);
    //Drawing objects here
    sphere->draw();
    ground->draw();
}

void initApplication() {
    glEnable(GL_DEPTH_TEST);

    ShaderLoader shader;

    GLuint flatShaderProgram = shader.CreateProgram("../assets/shaders/VertexShader.vs", 
    "../assets/shaders/FragmentShader.fs");
    GLuint texturedShaderProgram = shader.CreateProgram("../assets/shaders/texturedModel.vs",
    "../assets/shaders/texturedModel.fs");
    camera = new Camera(45.0f, 800, 600, 0.1f, 1000.0f, glm::vec3(0.0f, humanTall, 8.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    TextureLoader tLoader;
    GLuint sphereTexture = tLoader.getTextureID("../assets/textures/globe.jpg");
    GLuint groundTexture = tLoader.getTextureID("../assets/textures/ground.jpg");

	//init physics
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.8f, 0));
    
    // Sphere Rigid Body

	btCollisionShape* sphereShape = new btSphereShape(1);
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 15, 0)));

	btScalar mass = 10.0;
	btVector3 sphereInertia(0, 0, 0);
	sphereShape->calculateLocalInertia(mass, sphereInertia);

	btRigidBody::btRigidBodyConstructionInfo sphereRigidBodyCI(mass, sphereMotionState, sphereShape, sphereInertia);

	btRigidBody* sphereRigidBody = new btRigidBody(sphereRigidBodyCI);
	sphereRigidBody->setRestitution(1.0f);
	sphereRigidBody->setFriction(1.0f);

	dynamicsWorld->addRigidBody(sphereRigidBody);
	
	// Sphere Mesh

	sphere = new MeshRenderer(MeshType::kSphere, camera, 
        sphereRigidBody);
	sphere->setProgram(texturedShaderProgram);
	sphere->setTexture(sphereTexture);
    //sphere->setPosition(glm::vec3(2.0f, 2.0f, 2.0f));
	sphere->setScale(glm::vec3(1.0f));

    // Ground Rigid body

	btCollisionShape* groundShape = new btBoxShape(btVector3(15.0f, 0.3f, 15.0f));
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0.0f, 0)));

	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0.0f, groundMotionState, groundShape, btVector3(0, 0, 0));

	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);

	groundRigidBody->setFriction(1.0);
	groundRigidBody->setRestitution(0.9);

	groundRigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

	dynamicsWorld->addRigidBody(groundRigidBody);


	// Ground Mesh
	ground = new MeshRenderer(MeshType::kCube, camera, groundRigidBody);
	ground->setProgram(texturedShaderProgram);
	ground->setTexture(groundTexture);
	ground->setScale(glm::vec3(15.0f, 0.5f, 15.0f));
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