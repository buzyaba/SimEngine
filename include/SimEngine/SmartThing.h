#pragma once

#include <string>
#include <vector>

#include "SimEngine/Sensor.h"
#include "SimEngine/Actuator.h"
#include "SimEngine/Object.h"
#include "SimEngine/ObjectOfObservation.h"

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

  virtual void AddObject(TObjectOfObservation* object);
  virtual void ExcludeObject(TObjectOfObservation* object);
  virtual void ExcludeObject(std::string _name);

  /// Создание клона объекта
  virtual TSmartThing* Clone() = 0;

  virtual bool isDrawable() { return false; }
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с умными вещами
typedef TSmartThing* CreateSmartThing();

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif