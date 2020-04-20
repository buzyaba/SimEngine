#pragma once

#include <string>
#include <vector>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/Object.h"
#include "Core/ObjectOfObservation.h"

/// Класс описывающий умную вещь
class TSmartThing : public TObject
{
protected:
  /// Сенсор
  std::vector<ISensor*> sensors;
  /// Актуаторы
  std::vector<IActuator*> actuators;
public:
  TSmartThing(std::string _name, std::vector<ISensor*> _sensors, std::vector<IActuator*> _actuators);
  TSmartThing(const TSmartThing& thing);

  virtual std::vector<ISensor*> GetSensors();
  virtual std::vector<IActuator*> GetActuators();

  virtual void AddObject(TObjectOfObservation& object);
  virtual void ExcludeObject(TObjectOfObservation& object);
  virtual void ExcludeObject(std::string _name);

  /// Создание клона объекта
  virtual TSmartThing* Clone();
};