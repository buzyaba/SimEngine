#include "Core/Object.h"
#include <Engine/Renderer.hpp>
#include <algorithm>


GLuint TObject::shaderProgramInstanced = -1;
GLuint TObject::shaderProgramUnique = -1;

void TObject::initShader() {
    ShaderLoader shader;
    auto cwd = Renderer::getCWD();
    std::transform(cwd.begin(), cwd.end(), cwd.begin(), toupper);
    auto i = cwd.find("SIMENGINE");
    if (shaderProgramInstanced == -1)
      shaderProgramInstanced = shader.CreateProgram(Renderer::getCWD().substr(0,i+9) + "/assets/shaders/texturedModel.vs", Renderer::getCWD().substr(0,i+9) + "/assets/shaders/texturedModel.fs");
    if (shaderProgramUnique == -1)
      shaderProgramUnique = shader.CreateProgram(Renderer::getCWD().substr(0,i+9) + "/assets/shaders/texturedModelSingle.vs", Renderer::getCWD().substr(0,i+9) + "/assets/shaders/texturedModel.fs");
}

TObject::TObject(const std::string& _name):rigidBody(nullptr), name(_name) {
  if (shaderProgramInstanced == -1 || shaderProgramUnique == -1) {
    TObject::initShader();
  }
  meshes = MeshContainer::getInstance();
}

TObject::TObject(const TObject& obj) {
  properties = obj.properties;
  name = obj.name;
}

void TObject::SetProperty(IProperties& property) {
  GetProperty(property.GetName()).SetValues(property.GetValues());
}

void TObject::SetProperty(const std::map<std::string, double>& values, std::string propertyName) {
  properties[propertyName]->SetValues(values);
}

std::map<std::string, IProperties*>& TObject::GetProperties() {
  return properties;
}

IProperties& TObject::GetProperty(const std::string& _name) {
//   if (_name == "")
//     return *properties.begin()->second; // What is this?????
  for (const auto& i : properties)
    if (i.second->GetName() == _name)
      return *i.second;
  throw - 1;
}

std::string TObject::GetName() {
  return name;
}

void TObject::SetName(std::string _name) {
  if (_name.length() > 0)
    name = _name;
  else
    throw - 1;
}

void TObject::setPosition(const glm::vec3& pos) {
    btTransform _transform(rigidBody->getWorldTransform());

    _transform.setOrigin(btVector3(pos.x, pos.y, pos.z));
    rigidBody->setWorldTransform(_transform);
    rigidBody->getMotionState()->setWorldTransform(_transform);
    // Child classes should have correct transform implementation
}

void TObject::setRotation(const btScalar& yaw, const btScalar& pitch, const btScalar& roll) {
    btTransform t(rigidBody->getWorldTransform());
    btQuaternion rotate(btRadians(yaw), btRadians(pitch), btRadians(roll));
    t.setRotation(rotate);

    rigidBody->setWorldTransform(t);
    rigidBody->getMotionState()->setWorldTransform(t);
    // Child classes should have correct transform implementation
}

void TObject::setCollisionFlags(const CollisionType& _flag) {
    rigidBody->setCollisionFlags(_flag);
}

glm::vec3 TObject::getPosition() {
    return glm::vec3(rigidBody->getWorldTransform().getOrigin().x(), 
                     rigidBody->getWorldTransform().getOrigin().y(), 
                     rigidBody->getWorldTransform().getOrigin().z());
}

glm::vec3 TObject::getRotation() {
    return transforms[0].getRotation();
}

btRigidBody* TObject::getRigidBody() {
    return rigidBody;
}

bool TObject::isStatic() {
    return (rigidBody->getCollisionFlags() == CollisionType::STATIC) ? true : false;
}

std::vector<glm::mat4> TObject::getModelMatrixes() {
    std::vector<glm::mat4> vec(transforms.size());
    for (size_t i = 0; i < transforms.size(); ++i)
        vec[i] = transforms[i].getModelMatrix();
    return vec;
}

TObject::~TObject() {
  Renderer::getDynamicsWorld()->removeRigidBody(rigidBody);
  delete rigidBody;
}

// IObject* TObject::Clone()
// {
//   return new TObject(*this);
// }
