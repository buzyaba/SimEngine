#pragma once

#include <string>
#include <vector>

#include "BasicExamples/Sensor.h"
#include "BasicExamples/Actuator.h"
#include "BasicExamples/Object.h"
#include "BasicExamples/ObjectOfObservation.h"

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
  virtual TSmartThing* Clone() = 0;
};

///Тип функции-фабрики, которая экспортируется подключаемой библиотекой с умными вещами
typedef std::vector <TSmartThing*> CreateSmartThing();
///Тип функции-деструктора, которая экспортируется подключаемой библиотекой с умными вещами
typedef void DestroySmartThing(std::vector <TSmartThing*>);

///Префикс для фуккций, экспортируемых подключаемой библиотекой
#ifdef WIN32
#define LIB_EXPORT_API __declspec(dllexport)
#else
#define LIB_EXPORT_API
#endif