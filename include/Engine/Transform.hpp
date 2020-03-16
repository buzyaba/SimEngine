#pragma once
#include <Engine/Camera.hpp>
#include <Engine/ShaderLoader.hpp>
#include <Engine/TextureLoader.hpp>
#include <btBulletDynamicsCommon.h>

enum CollisionType{
    STATIC=btCollisionObject::CF_STATIC_OBJECT, 
    KINEMATIC=btCollisionObject::CF_KINEMATIC_OBJECT,
    NO_RESPONSE=btCollisionObject::CF_NO_CONTACT_RESPONSE,
};

class Transform {
    private:
        glm::vec3 pos, scale;
        glm::vec3 rotation;
        glm::mat4 modelMatrix;
    public:
        explicit Transform();
        glm::mat4 getModelMatrix() {return modelMatrix;};
        void setPosition(const glm::vec3& _pos);
        void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll);
        void setScale(const glm::vec3& _scale);
        glm::vec3 getRotation() {return rotation;}

};
