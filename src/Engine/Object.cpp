#include <Engine/Object.hpp>

GLuint Object::shaderProgram = -1;

void Object::initShader() {
    ShaderLoader shader;
    shaderProgram = shader.CreateProgram("../../../assets/shaders/texturedModel.vs", "../../../assets/shaders/texturedModel.fs");
}

Object::Object() {
    if (shaderProgram == -1) {
        Object::initShader();
    }
    // TextureLoader texture;
    // btDefaultMotionState* MotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

	// btScalar mass = _mass; 
	// btVector3 Inertia(0, 0, 0);
    // if(mass != 0.0f)
	//     shape->calculateLocalInertia(mass, Inertia);

	// btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape, Inertia);

	// btRigidBody* rigidBody = new btRigidBody(RigidBodyCI);
    // rigidBody->setRestitution(1.0f);
	// rigidBody->setFriction(0.0f);

    // rigidBody->setActivationState(DISABLE_DEACTIVATION);

	// dynamicsWorld->addRigidBody(rigidBody);

    // mesh = new MeshRenderer((MeshType)_mesh, camera, rigidBody);

    // GLuint textureShaderProgram = shader.CreateProgram("../../../assets/shaders/texturedModel.vs", "../../../assets/shaders/texturedModel.fs");
    // GLuint shaderTexture = texture.getTextureID("../../../assets/textures/");

    // mesh->setProgram(textureShaderProgram);
    // mesh->setTexture(shaderTexture);

    // rigidBody->setUserPointer(mesh);
}


void Object::setPosition(const glm::vec3& pos) {
    btTransform transform(rigidBody->getWorldTransform());

    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    rigidBody->setWorldTransform(transform);
    rigidBody->getMotionState()->setWorldTransform(transform);

}

void Object::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    btTransform transform(rigidBody->getWorldTransform());
    btQuaternion rotate(btRadians(yaw), btRadians(pitch), btRadians(roll));
    transform.setRotation(rotate);

    rigidBody->setWorldTransform(transform);
    rigidBody->getMotionState()->setWorldTransform(transform);
}

void Object::drawElements(const std::vector<Object*> objects) {
    // MAKE DRAWING
}