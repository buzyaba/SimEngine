#pragma once

#include <Engine/MeshRenderer.hpp>
#include <Engine/Camera.hpp>
#include <Engine/ShaderLoader.hpp>
#include <Engine/TextureLoader.hpp>

enum ObjectType {Sphere = 3, Cube = 2};
enum RigidBodyType {};
enum CollisionType{
    STATIC=btCollisionObject::CF_STATIC_OBJECT, 
    KINEMATIC=btCollisionObject::CF_KINEMATIC_OBJECT,
    NO_RESPONSE=btCollisionObject::CF_NO_CONTACT_RESPONSE,
};

class Object {
    private:
        Camera* camera;
        btDiscreteDynamicsWorld* dynamicsWorld;
        MeshRenderer* mesh;
    public:
       explicit Object(const ObjectType& _mesh, Camera* _camera, btDiscreteDynamicsWorld* _dynamicsWorld, btCollisionShape* shape, 
       const glm::vec3& pos= glm::vec3(0.0f), const glm::vec3& scale=glm::vec3(1.0f), const btScalar& _mass=0.0f,const std::string& texture_path="default.jpg");
       ~Object(){};
       void setScale(glm::vec3 _size);
       void setPosition(const glm::vec3& pos);
       void setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll);
       void setCollisionFlags(const CollisionType& _flag) {mesh->rigidBody->setCollisionFlags(_flag);} 
       glm::vec3 getPosition() {return glm::vec3(mesh->rigidBody->getWorldTransform().getOrigin().x(),
        mesh->rigidBody->getWorldTransform().getOrigin().y(), mesh->rigidBody->getWorldTransform().getOrigin().z());}
       void draw() {mesh->draw();}
       bool isStatic() {return (mesh->rigidBody->getCollisionFlags() == CollisionType::STATIC) ? true : false;};
};
