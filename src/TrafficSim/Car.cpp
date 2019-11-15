#include <TrafficSim/Car.hpp>

Car::Car(Camera* camera, btDiscreteDynamicsWorld* dynamicsWorld, const glm::vec3& pos) {
    model = new Object(ObjectType::Cube, camera, dynamicsWorld,
     new btBoxShape(btVector3(5.0f, 3.0f, 2.0f)), pos, glm::vec3(5.0f, 1.5f, 2.0f), 15.0f, "car.jpg");
}