#include "Engine/GObject.hpp"
#include "Engine/Renderer.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/quaternion.hpp>

void TGObject::draw() {
  _shader.use();

  //TODO : ADD LIGHT PROPERTIES TO RENDER
  _shader.setVec3("light.position", {0, 10, 0});
  _shader.setVec3("viewPos", Renderer::getCamera()->getCameraPosition());

  // light properties
  _shader.setVec3("light.ambient", 0.6f, 0.6f, 0.6f); 
  _shader.setVec3("light.diffuse", 0.3f, 0.3f, 0.3f);
  _shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

  // material properties
  _shader.setVec3("texture_specular1", 0.3f, 0.3f, 0.3f);
  _shader.setFloat("shininess", 75.0f);

  _shader.setMat4("projection", Renderer::getCamera()->getProjectionMatrix());
  _shader.setMat4("view", Renderer::getCamera()->getViewMatrix());

  auto quat = glm::quat(_transform->getAngles());
  
  glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::angle(quat), glm::axis(quat));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), _transform->getPos());

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), _transform->getScale());

	glm::mat4 modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

  _shader.setMat4("model", modelMatrix);
  _model->changeMeshTextures(_transform->getTextures());
  _model->Draw(_shader);
}