#include "Core/Object.h"
#include <filesystem>


GLuint TObject::shaderProgramInstanced = -1;
GLuint TObject::shaderProgramUnique = -1;
std::vector<MeshRenderer*> TObject::meshes = std::vector<MeshRenderer*>(0, nullptr);

void TObject::initShader() {
    ShaderLoader shader;
    auto i = std::filesystem::current_path().string().find("SimEngine");
    auto pwd = std::filesystem::current_path().string();
    if (shaderProgramInstanced == -1)
      shaderProgramInstanced = shader.CreateProgram(pwd.substr(0,i) + "SimEngine/assets/shaders/texturedModel.vs", pwd.substr(0,i) + "SimEngine/assets/shaders/texturedModel.fs");
    if (shaderProgramUnique == -1)
      shaderProgramUnique = shader.CreateProgram(pwd.substr(0,i) + "SimEngine/assets/shaders/texturedModelSingle.vs", pwd.substr(0,i) + "SimEngine/assets/shaders/texturedModel.fs");
}

TObject::TObject(const std::string& _name, ...):rigidBody(nullptr), name(_name) {
  if (shaderProgramInstanced == -1 || shaderProgramUnique == -1) {
    TObject::initShader();
  }
  if ()

}

TObject::TObject(const TObject& obj) {
  properties = obj.properties;
  name = obj.name;
}

void TObject::SetProperty(IProperties& property) {
  GetProperty(property.GetName()).SetValues(property.GetValues());
}

void TObject::SetProperty(const std::map<std::string, std::vector<double>>& values, std::string propertyName) {
  properties[propertyName]->SetValues(values);
}

std::map<std::string, IProperties*>& TObject::GetProperties() {
  return properties;
}
IProperties& TObject::GetProperty(const std::string& _name){
  if (_name == "")
    return *properties.begin;
  for (const auto& i : properties)
    if (i.second->GetName() == _name)
      return *i.second;
  throw - 1;
}

std::string TObject::GetName()
{
  return name;
}

void TObject::SetName(std::string _name)
{
  if (_name.length() > 0)
    name = _name;
  else
    throw - 1;
}

std::string TObject::ClassName()
{
  return std::string("ClassName");
}


