#pragma once

#include <string>
#include <vector>

#include "Core/DataPacket.h"
#include "Core/Properties.h"
#include "Core/ObjectOfObservation.h"


class IActuator
{
protected:
  std::string name;
  std::vector<IObjectOfObservation*> objects;
  std::vector <IProperties*> property;
public:

  virtual void AddObject(IObjectOfObservation* object) = 0;
  virtual void ExcludeObject(IObjectOfObservation* object) = 0;
  virtual void ExcludeObject(std::string objectName) = 0;

  virtual void ChangeActuatorProperty(IProperties& _property) = 0;
  virtual void ChangeProperty(IProperties& property, IObjectOfObservation& object) = 0;
  virtual void ChangeProperty(IProperties& property, std::string _objectName) = 0;
    virtual void SetDataPacket(TDataPacket& packet) = 0;

  std::string GetName()
  {
    return name;
  }

  void SetName(std::string _name)
  {
    if (_name.length() > 0)
      name = _name;
    else
      throw - 1;
  }
};