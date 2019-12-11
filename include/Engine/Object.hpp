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
        btQuaternion rotation;
        glm::mat4 modelMatrix;
    public:
        explicit Transform();
        glm::mat4 getModelMatrix() {return modelMatrix;};
        void setPosition(const glm::vec3& _pos);
        void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll);
        void setScale(const glm::vec3& _scale);

};

class Primitive {
    private:
        static void initShader();
    protected:
        static GLuint shaderProgram;
        Transform transform;
        btRigidBody* rigidBody;
        virtual void initMesh() = 0;
    public:
       explicit Primitive();
       virtual ~Primitive(){delete rigidBody;};
       virtual void setScale(const glm::vec3& _size) = 0;
       void setPosition(const glm::vec3& pos);
       void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll);
       void setCollisionFlags(const CollisionType& _flag) {rigidBody->setCollisionFlags(_flag);} 
       glm::vec3 getPosition() {return glm::vec3(rigidBody->getWorldTransform().getOrigin().x(),
        rigidBody->getWorldTransform().getOrigin().y(), rigidBody->getWorldTransform().getOrigin().z());}
       bool isStatic() {return (rigidBody->getCollisionFlags() == CollisionType::STATIC) ? true : false;};
       btRigidBody* getRigidBody()  {return rigidBody;}
};
