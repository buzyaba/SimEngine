#pragma once

#include "Core/Object.h"

class IObjectOfObservation : public IObject
{
protected:

public:
  virtual void AddParentObject(IObjectOfObservation& obect) = 0;
  virtual void AddChildObject(IObjectOfObservation& obect) = 0;
  virtual void AddNeighboringObject(IObjectOfObservation& obect) = 0;
  virtual void ExcludeChildObject(IObjectOfObservation& obect) = 0;
};

class TCoordinateObject: public IObjectOfObservation
{
protected:

public:

  TCoordinateObject()
  {
    this->name = "CoordinateObject";
    properties.resize(2);
    properties[0] = new IProperties({ 0, 0 }, { "x", "y" }, "coordinate");
  }

  virtual void AddParentObject(IObjectOfObservation& obect)
  {

  }
  virtual void AddChildObject(IObjectOfObservation& obect)
  {

  }
  virtual void AddNeighboringObject(IObjectOfObservation& obect)
  {

  }
  virtual void ExcludeChildObject(IObjectOfObservation& obect)
  {

  }

  virtual void SetProperty(IProperties& property, std::string _name = "")
  {
    if (_name == "")
      properties[0]->SetValues(property.GetValues());
    else
      GetProperty(_name).SetValues(property.GetValues());
  }
  virtual std::vector<IProperties*> GetProperties()
  {
    return properties;
  }
  virtual IProperties& GetProperty(std::string _name = "")
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

  virtual std::string GetName()
  {
    return name;
  }
  virtual void SetName(std::string _name)
  {
    name = _name;
  }
};