#pragma once

#include <string>
#include <vector>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/Object.h"
#include "Core/ObjectOfObservation.h"

class ISmartThing : public IObject
{
protected:
  std::vector<ISensor*> sensors;
  std::vector<IActuator*> actuators;

public:

  virtual std::vector<ISensor*> GetSensors() = 0;
  virtual std::vector<IActuator*> GetActuators() = 0;

  virtual void AddObject(IObjectOfObservation& object) = 0;
  virtual void ExcludeObject(IObjectOfObservation& object) = 0;
  virtual void ExcludeObject(std::string _name) = 0;


};