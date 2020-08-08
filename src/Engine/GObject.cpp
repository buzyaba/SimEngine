#include "Engine/GObject.hpp"
#include "Engine/Renderer.hpp"

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

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, _transform->getPos());
  model = glm::scale(model, _transform->getScale());
  // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
  _shader.setMat4("model", model);
  _model.Draw(_shader);
}