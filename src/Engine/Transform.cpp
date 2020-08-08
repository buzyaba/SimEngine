#include <Engine/Transform.hpp>

Transform::Transform() {
    pos = glm::vec3(0);
    scale = glm::vec3(1);
    rotation = glm::vec3(0);

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f),
		glm::vec3(pos.x, pos.y, pos.z));

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	modelMatrix = translationMatrix * scaleMatrix;
}
