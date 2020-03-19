#include "Core/Object.h"

TObject::TObject(std::string _name)
{
  SetName(_name);
}

TObject::TObject(const TObject& obj)
{
  properties = obj.properties;
  name = obj.name;
}

void TObject::SetProperty(IProperties& property)
{
  GetProperty(property.GetName()).SetValues(property.GetValues());
}

void TObject::SetProperty(const std::vector<double>& values, std::string propertyName)
{
  GetProperty(propertyName).SetValues(values);
}

std::vector<IProperties*>& TObject::GetProperties()
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
  if (_name.length() > 0)
    name = _name;
  else
    throw - 1;
}

std::string TObject::ClassName()
{
  return std::string("ClassName");
}

IObject* TObject::Clone()
{
  return new TObject(*this);
}
