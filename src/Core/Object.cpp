#include "Core/Object.h"

TObject::TObject()
{
  name = "";
}

TObject::TObject(const TObject& obj)
{
  properties = obj.properties;
  name = obj.name;
}

void TObject::SetProperty(IProperties& _property)
{
  GetProperty(_property.GetName()).SetValues(_property.GetValues());
}

void TObject::SetProperty(IProperties& property, std::string _name)
{
  if (_name == "")
    properties[0]->SetValues(property.GetValues());
  else
    GetProperty(_name).SetValues(property.GetValues());
}
std::vector<IProperties*> TObject::GetProperties()
{
  return properties;
}
IProperties& TObject::GetProperty(std::string _name)
{
  if (_name == "")
    return *properties[0];
  int i = 0;
  for (; i < properties.size(); i++)
    if (properties[i]->GetName() == _name)
      return *properties[i];
  if (i == properties.size())
    throw - 1;
}

std::string TObject::GetName()
{
  return name;
}
void TObject::SetName(std::string _name)
{
  name = _name;
}