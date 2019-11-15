#pragma once

#include <string>
#include <vector>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/Object.h"
#include "Core/ObjectOfObservation.h"

class TDataStore
{
protected:
  std::string name;
  std::vector<IProperties*> properties;

public:
  TDataStore()
  {};
  virtual void AddPropertyForObject(const IProperties& property, unsigned long time) = 0;
  virtual std::vector<IProperties*> GddPropertyForObject(unsigned long time) = 0;
};