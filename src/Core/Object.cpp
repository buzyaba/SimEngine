#include "Core/Object.h"

#include <algorithm>


TObject::TObject(const std::string& _name):name(_name)

{
}

TObject::TObject(const TObject& obj) {
  properties = obj.properties;
  name = obj.name;
  textures=obj.textures;
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

