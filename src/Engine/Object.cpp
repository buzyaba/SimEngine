#include <Engine/Object.hpp>

GLuint Primitive::shaderProgram = -1;


void Primitive::initShader() {
    ShaderLoader shader;
    shaderProgram = shader.CreateProgram("../../../assets/shaders/texturedModel.vs", "../../../assets/shaders/texturedModel.fs");
}


Transform::Transform() {
    pos = glm::vec3(0);
    scale = glm::vec3(1);
    rotation = rotation.getIdentity();
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));

	translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(const glm::vec3& _pos) {
    pos = _pos;
    translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    rotation = btQuaternion(yaw, pitch, roll);
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));;

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setScale(const glm::vec3& _scale) {
    scale = _scale;
    scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

Primitive::Primitive() {
    if (shaderProgram == -1) {
        Primitive::initShader();
    }
}


void Primitive::setPosition(const glm::vec3& pos) {
    btTransform transform(rigidBody->getWorldTransform());

    transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    rigidBody->setWorldTransform(transform);
    rigidBody->getMotionState()->setWorldTransform(transform);

}

void Primitive::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    btTransform transform(rigidBody->getWorldTransform());
    btQuaternion rotate(btRadians(yaw), btRadians(pitch), btRadians(roll));
    transform.setRotation(rotate);

    rigidBody->setWorldTransform(transform);
    rigidBody->getMotionState()->setWorldTransform(transform);
}
