#pragma once

#include <string>
#include <vector>

#include "Core/DataPacket.h"
#include "Core/ObjectOfObservation.h"

class ISensor
{
protected:
  std::string name;
  std::vector<IObjectOfObservation*> objects;
public:
  virtual TDataPacket GetDataPacket() = 0;
  virtual void AddObject(IObjectOfObservation* object) = 0;
  virtual void ExcludeObject(IObjectOfObservation* object) = 0;
  virtual void ExcludeObject(std::string objectName) = 0;

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