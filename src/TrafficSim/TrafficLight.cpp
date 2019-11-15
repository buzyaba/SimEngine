#include <TrafficSim/TrafficLight.hpp>

TrafficLight::TrafficLight(Camera* camera, btDiscreteDynamicsWorld* dynamicsWorld, const glm::vec3& pos) {
    column = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(0.2f, 5.0f, 0.2f)),
    pos, glm::vec3(0.2f, 5.0f, 0.2f), 0.0f, "gray.jpg");
    light = new Object(ObjectType::Cube, camera, dynamicsWorld, new btBoxShape(btVector3(1, 2, 1)), 
    pos + glm::vec3(0, 5, 0), glm::vec3(1, 2, 1), 0.0f, "greenlight.jpg");
}