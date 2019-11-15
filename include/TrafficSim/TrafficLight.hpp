#pragma once
#include <Engine/Object.hpp>

class TrafficLight {
    Object* column;
    Object* light;

    public:
        explicit TrafficLight(Camera* camera, btDiscreteDynamicsWorld* dynamicsWorld, 
    const glm::vec3& pos = glm::vec3(0.0f));

        void draw() {column->draw(); light->draw();}

};