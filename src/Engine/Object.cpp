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
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(const glm::vec3& _pos) {
    pos = _pos;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    rotation = btQuaternion(yaw, pitch, roll);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setScale(const glm::vec3& _scale) {
    scale = _scale;
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rotation.getAngle()),
    glm::vec3(rotation.getAxis().x(), rotation.getAxis().y(), rotation.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

Primitive::Primitive() {
    if (shaderProgram == -1) {
        Primitive::initShader();
    }
}


void Primitive::setPosition(const glm::vec3& pos) {
    btTransform _transform(rigidBody->getWorldTransform());

    _transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    rigidBody->setWorldTransform(_transform);
    rigidBody->getMotionState()->setWorldTransform(_transform);

    transform.setPosition(pos);

}

void Primitive::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    btTransform t(rigidBody->getWorldTransform());
    btQuaternion rotate(btRadians(yaw), btRadians(pitch), btRadians(roll));
    t.setRotation(rotate);

    rigidBody->setWorldTransform(t);
    rigidBody->getMotionState()->setWorldTransform(t);
    transform.setRotation(yaw, pitch, roll);
}
