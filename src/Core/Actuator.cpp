#include "Core/Actuator.h"
#include <algorithm>

TActuator::TActuator(std::string _name)
{
  SetName(_name);
}

TActuator::TActuator(const TActuator& actuator)
{
  this->name = actuator.name;
  this->objects = actuator.objects;
  this->property = actuator.property;
}

void TActuator::AddObject(TObjectOfObservation& object)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] == &object)
      return;
  }
  objects.push_back(&object);
  //objectsProperties.resize(objects.size());
}

void TActuator::ExcludeObject(TObjectOfObservation& object)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] == &object)
    {
      objects[i] = nullptr;
      auto&& it = std::remove(objects.begin(), objects.end(), nullptr);
      objects.resize(it-objects.begin());
    }
  }
}

void TActuator::ExcludeObject(std::string objectName)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == objectName)
      {
        objects[i] = nullptr;
        auto it = std::remove(objects.begin(), objects.end(), nullptr);
        objects.resize(it-objects.begin());
      }
    }
  }
}

void TActuator::ChangeActuatorProperty(IProperties& _property)
{
  this->property = &_property;
}

void TActuator::ChangeProperty(IProperties& property, TObjectOfObservation& object)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] == &object)
    {
      objects[i]->SetProperty(property);
    }
  }
}

void TActuator::ChangeProperty(IProperties& property, std::string _objectName)
{
  for (int i = 0; i < objects.size(); i++)
  {
    if (objects[i] != nullptr)
    {
      if (objects[i]->GetName() == _objectName)
      {
        objects[i]->SetProperty(property);
      }
    }
  }
}

void TActuator::SetDataPacket(TDataPacket& packet)
{
  this->packet=&packet;
}

std::string TActuator::GetName()
{
  return name;
}

void TActuator::SetName(std::string _name)
{
  if (_name.length() > 0)
    name = _name;
  else
    throw - 1;
}