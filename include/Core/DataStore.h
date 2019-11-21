#pragma once

#include <string>
#include <vector>

#include "Core/Sensor.h"
#include "Core/Actuator.h"
#include "Core/Object.h"
#include "Core/ObjectOfObservation.h"

/// Класс реализующий базовое хранение данных об объектах в базе данных
/// Пока заглушка
class TDataStore
{
protected:
  /// Имя базы данных
  std::string name;
  /// 
  std::vector<IProperties*> properties;

public:
  TDataStore()
  {};
  virtual void AddPropertyForObject(const IProperties& property, unsigned long time)
  {}
  virtual std::vector<IProperties*> GddPropertyForObject(unsigned long time)
  {
    return properties;
  }
};