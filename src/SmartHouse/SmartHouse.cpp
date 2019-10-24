#include <SmartHouse/SmartHouse.hpp>

Camera* camera;

MeshRenderer* sphere;
MeshRenderer* ground;

//physics
btDiscreteDynamicsWorld* dynamicsWorld;

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.f, 1.f, 0.f, 1.f);
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
    camera = new Camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(3.0f, -1.0f, 15.0f));

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
	btDefaultMotionState* sphereMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 5, 0)));

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
	btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -5.0f, 0)));

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