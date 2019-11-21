#include "Core/SmartThing.h"

TSmartThing::TSmartThing(std::vector<ISensor*> _sensors, std::vector<IActuator*> _actuators)
{
  this->sensors = _sensors;
  this->actuators = _actuators;
}

TSmartThing::TSmartThing(const TSmartThing& thing)
{
  this->sensors = thing.sensors;
  this->actuators = thing.actuators;
}

std::vector<ISensor*> TSmartThing::GetSensors()
{
  return sensors;
}

std::vector<IActuator*> TSmartThing::GetActuators()
{
  return actuators;
}

void TSmartThing::AddObject(TObjectOfObservation& object)
{
  for (int i = 0; i < actuators.size(); i++)
    if (actuators[i] != nullptr)
      actuators[i]->AddObject(object);
  for (int i = 0; i < sensors.size(); i++)
    if (sensors[i] != nullptr)
      sensors[i]->AddObject(object);
}

void TSmartThing::ExcludeObject(TObjectOfObservation& object)
{
  for (int i = 0; i < actuators.size(); i++)
    if (actuators[i] != nullptr)
      actuators[i]->ExcludeObject(object);
  for (int i = 0; i < sensors.size(); i++)
    if (sensors[i] != nullptr)
      sensors[i]->ExcludeObject(object);
}

void TSmartThing::ExcludeObject(std::string _name)
{
  for (int i = 0; i < actuators.size(); i++)
    if (actuators[i] != nullptr)
      actuators[i]->ExcludeObject(_name);
  for (int i = 0; i < sensors.size(); i++)
    if (sensors[i] != nullptr)
      sensors[i]->ExcludeObject(_name);
}
