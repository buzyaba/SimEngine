#include <TrafficSim/TrafficSim.hpp>
#include <list>

btDiscreteDynamicsWorld* dynamicsWorld;
Camera* camera;

Object* sphere;
Object* ground;
Object* enemy;

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

    camera = new Camera(45, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 4.0f, 20.0f));

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

    //ground->setRotation(0.0f, 0.0, 45.0f);
    //ground->setPosition(glm::vec3(-2.0f, 2.0f, 0.0f));
}

void myTickCallback(btDynamicsWorld *dynamicsWorld, btScalar
    timeStep) {
    
		// Get enemy transform
		glm::vec3 pos = enemy->getPosition();
		// Check if offScreen
		if (pos.x <= -18.0f) {

			enemy->setPosition(glm::vec3(5.0f, -1.0f, 0.0f));
		}
        else
            enemy->setPosition(pos+glm::vec3(-5.0f, 0.0f, 0.0f)*timeStep);

}