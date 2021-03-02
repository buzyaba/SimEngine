#pragma once

#include <string>
#include <vector>
#include <map>


#include "SimEngine/Object.h"
#include "SimEngine/Properties.h"


/**
Класс описание периода определенной работы объекта
имя свойства, время начала, время конца, значения
**/
class TPropertyInterval
{
public:
  std::string nameProperty;
  // Что это?
  bool isSet;

  std::vector<std::size_t> timePoint;
  std::vector <std::map<std::string, double>> value;

  void SetProperty(IProperties& prop, int intervalCount, std::vector<std::size_t>& _timePoint)
  {
    nameProperty = prop.GetName();
    isSet = false;
    value.resize(intervalCount);
    timePoint = _timePoint;
    for (int i = 0; i < intervalCount; i++)
    {
      value[i] = prop.GetValues();
    }
  }

  std::map<std::string, double>& GetValue(std::size_t time)
  {
    for (int i = 0; i < timePoint.size(); i++)
    {
      if (time == timePoint[i])
        return value[i];
    }
    throw - 1;
  }

};

/// Базовый класс обработчика скрипта возвращающего по времени свойства объекта
class TExternalActionSchedule
{
protected:
  /// Управляемые объекты
  std::vector<IObject*> objects;
  /// Имя(полный путь) скрипта
  std::string xmlName;
  
  /// Интервалы содержащие время и соответствующее значение для свойств объектов
  std::vector<std::map<std::string, TPropertyInterval>> objectPropertyIntervals;


  /// Меняем свойство найденного объекта в соответствии со скриптом
  std::map<std::string, IProperties*>& ChangeProperties(int objectIndex, 
        std::map<std::string, IProperties*>& properties, std::size_t time);
  
  /// Случайное заполнение расписания
  void LoadXML();

public:
  TExternalActionSchedule(std::vector<IObject*> _objects, std::string xmlName);

  virtual std::map<std::string, IProperties*>& GetObjectProperties(std::string name, std::size_t time);
  virtual std::map<std::string, IProperties*>& GetObjectProperties(IObject& object, std::size_t time);

  virtual void UpdateObjectsProperties(std::size_t time);
};
