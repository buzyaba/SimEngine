#pragma once
#include <Engine/Object.hpp>

class Car {
    private:
        Object* model;
    public:
        explicit Car(Camera* camera, btDiscreteDynamicsWorld* dynamicsWorld, 
        const glm::vec3& pos = glm::vec3(0.0f));
        ~Car(){delete model;}
        void draw() {model->draw();}
        glm::vec3 getPostition() {return model->getPosition();}
        void setPostition(const glm::vec3& pos) {model->setPosition(pos);}
        void setRotation(const btScalar& yaw,const btScalar& pitch, const btScalar& roll) {
            model->setRotation(yaw, pitch, roll);
        }
};