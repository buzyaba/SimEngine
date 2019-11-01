#include <Engine/Object.hpp>

Object::Object(const ObjectType& _mesh, Camera* _camera, btDiscreteDynamicsWorld* _dynamicsWorld, btCollisionShape* shape, 
       const glm::vec3& pos, const glm::vec3& scale, const btScalar& _mass,const std::string& texture_path):
camera(_camera), dynamicsWorld(_dynamicsWorld){
    ShaderLoader shader;
    TextureLoader texture;
    btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

	btScalar mass = _mass; 
	btVector3 Inertia(0, 0, 0);
    if(mass != 0.0f)
	    shape->calculateLocalInertia(mass, Inertia);

	btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);

	btRigidBody* rigidBody = new btRigidBody(RigidBodyCI);
    rigidBody->setRestitution(1.0f);
	rigidBody->setFriction(0.0f);

    rigidBody->setActivationState(DISABLE_DEACTIVATION);

	dynamicsWorld->addRigidBody(rigidBody);

    mesh = new MeshRenderer((MeshType)_mesh, camera, rigidBody);

    GLuint textureShaderProgram = shader.CreateProgram("../../assets/shaders/texturedModel.vs", "../../assets/shaders/texturedModel.fs");
    GLuint shaderTexture = texture.getTextureID("../../assets/textures/" + texture_path);

    mesh->setProgram(textureShaderProgram);
    mesh->setTexture(shaderTexture);
    mesh->setPosition(pos);
    mesh->setScale(scale);

    rigidBody->setUserPointer(mesh);
}

void Object::setScale(glm::vec3 _size) {
    mesh->setScale(_size);
}

void Object::setPosition(const glm::vec3& pos) {
    btTransform transform(mesh->rigidBody->getWorldTransform());

    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    mesh->rigidBody->setWorldTransform(transform);
    mesh->rigidBody->getMotionState()->setWorldTransform(transform);

}

void Object::setRotation(const btScalar& dx, const btScalar& dy, const btScalar& dz) {
    btTransform transform(mesh->rigidBody->getCenterOfMassTransform());



    mesh->rigidBody->setCenterOfMassTransform(transform);

}