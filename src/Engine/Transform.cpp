#include <Engine/Transform.hpp>

Transform::Transform() {
    pos = glm::vec3(0);
    scale = glm::vec3(1);
    rotation = glm::vec3(0);
    btQuaternion rot(rotation.x, rotation.y, rotation.z);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rot.getAngle()),
    glm::vec3(rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setPosition(const glm::vec3& _pos) {
    pos = _pos;
    btQuaternion rot(rotation.x, rotation.y, rotation.z);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rot.getAngle()),
    glm::vec3(rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    btQuaternion rot(yaw, pitch, roll);
    rotation = glm::vec3(yaw, pitch, roll);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rot.getAngle()),
    glm::vec3(rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}

void Transform::setScale(const glm::vec3& _scale) {
    scale = _scale;
    btQuaternion rot(rotation.x, rotation.y, rotation.z);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::degrees(rot.getAngle()),
    glm::vec3(rot.getAxis().x(), rot.getAxis().y(), rot.getAxis().z()));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
}
