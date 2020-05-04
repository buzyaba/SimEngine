#include "SmartHouse/Room.h"

// unsigned int TRoom::meshBuffer = -1;

TRoom::TRoom(std::string _name, const glm::vec3 &pos, const glm::vec3 &scale)
    : TStaticObject(_name) {
  properties.insert({std::string("Dimensions"),
                     new TProperties(
                         std::map<std::string, double>{
                             {"Width", 20}, {"Length", 20}, {"Height", 20}},
                         false, "Dimensions")});
  // GL
  otherTextures.insert({"wall", Renderer::getTextures()[WALL]});
  otherTextures.insert({"ceiling", Renderer::getTextures()[CEILING]});
  otherTextures.insert({"floor", Renderer::getTextures()[FLOOR]});

  btDefaultMotionState *MotionState = new btDefaultMotionState(btTransform(
      btQuaternion(0.0f, 0.0f, 0.0f, 1.0f), btVector3(pos.x, pos.y, pos.z)));

  btCollisionShape *shape =
      new btBoxShape(btVector3(scale.x, scale.y, scale.z));

  btScalar mass = 0.0f;
  btVector3 Inertia(0, 0, 0);
  if (mass != 0.0f)
    shape->calculateLocalInertia(mass, Inertia);

  btRigidBody::btRigidBodyConstructionInfo RigidBodyCI(mass, MotionState, shape,
                                                       Inertia);

  rigidBody = new btRigidBody(RigidBodyCI);
  rigidBody->setRestitution(1.0f);
  rigidBody->setFriction(0.0f);

  rigidBody->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);

  Renderer::getDynamicsWorld()->addRigidBody(rigidBody);

  transforms.resize(7);

  transforms[0].setPosition(pos); // main Transform
  transforms[0].setScale(scale);

  transforms[1].setPosition(pos + glm::vec3(0.0f, -0.1f, 0.0f)); // floor
  transforms[1].setScale(glm::vec3(30.0f, 0.1f, 30.0f) * scale);
  transforms[2].setPosition(pos + glm::vec3(0.0f, 10.0f, 0.0f)); // ceiling
  transforms[2].setScale(glm::vec3(30.0f, 0.1f, 30.0f) * scale);
  transforms[3].setPosition(pos + glm::vec3(30.0f, 5.0f, 0.0f)); // rightWall
  transforms[3].setScale(glm::vec3(0.1f, 5.0f, 30.0f) * scale);
  transforms[4].setPosition(pos + glm::vec3(-30.0f, 5.0f, 0.0f)); // leftWall
  transforms[4].setScale(glm::vec3(0.1f, 5.0f, 30.0f) * scale);
  transforms[5].setPosition(pos + glm::vec3(0.0f, 5.0f, -30.0f)); // frontWall
  transforms[5].setScale(glm::vec3(30.0f, 5.0f, 0.1f) * scale);
  transforms[6].setPosition(pos + glm::vec3(0.0f, 5.0f, 30.0f)); // backWall
  transforms[6].setScale(glm::vec3(30.0f, 5.0f, 0.1f) * scale);
}

// void TRoom::initBuffer() {
//   if (meshBuffer == -1)
//     glGenBuffers(1, &meshBuffer);
// }

void TRoom::setScale(const glm::vec3 &_size) {
  transforms[0].setScale(_size);
  transforms[1].setPosition(glm::vec3(0.0f, -0.1f, 0.0f));  // floor
  transforms[2].setPosition(glm::vec3(0.0f, 10.0f, 0.0f));  // ceiling
  transforms[3].setPosition(glm::vec3(30.0f, 5.0f, 0.0f));  // rightWall
  transforms[4].setPosition(glm::vec3(-30.0f, 5.0f, 0.0f)); // leftWall
  transforms[5].setPosition(glm::vec3(0.0f, 5.0f, -30.0f)); // frontWall
  transforms[6].setPosition(glm::vec3(0.0f, 5.0f, 30.0f));  // backWall
  for (size_t i = 1; i < transforms.size(); ++i)
    transforms[i].setModelMatrix(transforms[0].getModelMatrix() *
                                 transforms[i].getModelMatrix());
}

void TRoom::setPosition(const glm::vec3 &pos) {
  TObject::setPosition(pos);
  transforms[0].setPosition(pos);
  transforms[1].setPosition(glm::vec3(0.0f, -0.1f, 0.0f));  // floor
  transforms[2].setPosition(glm::vec3(0.0f, 10.0f, 0.0f));  // ceiling
  transforms[3].setPosition(glm::vec3(30.0f, 5.0f, 0.0f));  // rightWall
  transforms[4].setPosition(glm::vec3(-30.0f, 5.0f, 0.0f)); // leftWall
  transforms[5].setPosition(glm::vec3(0.0f, 5.0f, -30.0f)); // frontWall
  transforms[6].setPosition(glm::vec3(0.0f, 5.0f, 30.0f));  // backWall
  for (size_t i = 1; i < transforms.size(); ++i)
    transforms[i].setModelMatrix(transforms[0].getModelMatrix() *
                                 transforms[i].getModelMatrix());
}

void TRoom::setRotation(const btScalar &yaw, const btScalar &pitch,
                        const btScalar &roll) {
  TObject::setRotation(yaw, pitch, roll);
  transforms[0].setRotation(yaw, pitch, roll);
  transforms[1].setPosition(glm::vec3(0.0f, -0.1f, 0.0f));  // floor
  transforms[2].setPosition(glm::vec3(0.0f, 10.0f, 0.0f));  // ceiling
  transforms[3].setPosition(glm::vec3(30.0f, 5.0f, 0.0f));  // rightWall
  transforms[4].setPosition(glm::vec3(-30.0f, 5.0f, 0.0f)); // leftWall
  transforms[5].setPosition(glm::vec3(0.0f, 5.0f, -30.0f)); // frontWall
  transforms[6].setPosition(glm::vec3(0.0f, 5.0f, 30.0f));  // backWall
  for (size_t i = 1; i < transforms.size(); ++i)
    transforms[i].setModelMatrix(transforms[0].getModelMatrix() *
                                 transforms[i].getModelMatrix());
}

void TRoom::drawElements(const std::vector<TObject *> &objects) {
  GLuint vao = meshes->getMesh(kCube)->getVAO();
  glUseProgram(shaderProgramUnique);
  glBindVertexArray(vao);
  glm::mat4 vp = Renderer::getCamera()->getProjectionMatrix() *
                 Renderer::getCamera()->getViewMatrix();
  GLint vpLoc = glGetUniformLocation(shaderProgramUnique, "vp");
  glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
  for (auto iter : objects) {
    std::vector<glm::mat4> vec = iter->getModelMatrixes();
    GLint modelLoc = glGetUniformLocation(shaderProgramUnique, "model");
    glBindTexture(GL_TEXTURE_2D, iter->getTexture("wall"));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[3]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[4]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[5]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[6]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, iter->getTexture("floor"));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[1]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, iter->getTexture("ceiling"));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE,
                       glm::value_ptr(iter->getModelMatrixes()[2]));
    glDrawElements(GL_TRIANGLES, meshes->getMesh(kCube)->getIndices().size(),
                   GL_UNSIGNED_INT, 0);
  }
  glBindVertexArray(0);
}
